using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using ElectroWorld.Models;
using ElectroWorld.Services;

namespace ElectroWorld
{
    public partial class MainWindow : Window
    {
        private int currentUserId;
        private DatabaseHelper db = new DatabaseHelper();
        private List<Product> allProducts = new List<Product>();
        private List<Product> displayedProducts = new List<Product>();
        public static bool IsDarkTheme { get; set; } = false;

        public MainWindow() => InitializeComponent();

        public MainWindow(int userId) : this()
        {
            currentUserId = userId;
            LoadProducts();
            UpdateCartCount();
            productsList.MouseRightButtonDown += ProductsList_MouseRightButtonDown;
        }

        private void LoadProducts()
        {
            allProducts = db.GetAllProducts();
            displayedProducts = new List<Product>(allProducts);
            RefreshProductList();
        }

        private void RefreshProductList()
        {
            productsList.ItemsSource = null;
            productsList.ItemsSource = displayedProducts;
            txtCounter.Text = $"Показано: {displayedProducts.Count} из {allProducts.Count}";
        }

        private void UpdateCartCount()
        {
            int count = db.GetCart(currentUserId).Sum(c => c.Quantity);
            if (count > 0)
            {
                cartCount.Text = count.ToString();
                cartBadge.Visibility = Visibility.Visible;
                cartBadge.Background = IsDarkTheme ? GetBrush("#359A85") : GetBrush("#fc8181");
            }
            else cartBadge.Visibility = Visibility.Collapsed;
        }

        private void BtnSearch_Click(object sender, RoutedEventArgs e)
        {
            string searchText = txtSearch.Text.Trim().ToLower();
            string selectedSort = (cmbSort.SelectedItem as ComboBoxItem)?.Content?.ToString() ?? "Без сортировки";

            var filtered = allProducts.ToList();

            if (!string.IsNullOrEmpty(searchText))
                filtered = filtered.Where(p => p.Name.ToLower().Contains(searchText) || p.Description.ToLower().Contains(searchText)).ToList();

            if (selectedSort == "от 0% до 14.99%")
                filtered = filtered.Where(p => p.DiscountPercent >= 0 && p.DiscountPercent < 15).ToList();
            else if (selectedSort == "от 15% до 24.99%")
                filtered = filtered.Where(p => p.DiscountPercent >= 15 && p.DiscountPercent < 25).ToList();
            else if (selectedSort == "более 25%")
                filtered = filtered.Where(p => p.DiscountPercent >= 25).ToList();

            displayedProducts = filtered;
            RefreshProductList();
        }

        private void BtnTheme_Click(object sender, RoutedEventArgs e)
        {
            IsDarkTheme = !IsDarkTheme;
            string buttonColor = IsDarkTheme ? "#fc8181" : "#359A85";
            string headerColor = IsDarkTheme ? "#fc8181" : "#19493f";

            var headerBorder = FindName("HeaderBorder") as Border;
            if (headerBorder != null)
                headerBorder.Background = GetBrush(headerColor);

            btnSearch.Background = GetBrush(buttonColor);
            UpdateCartCount();
        }

        private SolidColorBrush GetBrush(string colorCode)
        {
            try
            {
                var converter = new BrushConverter();
                var brush = converter.ConvertFrom(colorCode) as SolidColorBrush;
                return brush ?? new SolidColorBrush(Colors.Gray);
            }
            catch
            {
                return new SolidColorBrush(Colors.Gray);
            }
        }

        private void BtnCart_Click(object sender, RoutedEventArgs e)
        {
            var cartWindow = new CartWindow(currentUserId);
            cartWindow.Closed += (s, args) =>
            {
                UpdateCartCount();
                LoadProducts();
            };
            cartWindow.ShowDialog();
        }

        private void ProductsList_MouseRightButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            var position = e.GetPosition(productsList);
            var result = System.Windows.Media.VisualTreeHelper.HitTest(productsList, position);
            var element = result?.VisualHit;

            while (element != null && !(element is Border))
                element = System.Windows.Media.VisualTreeHelper.GetParent(element);

            if (element is Border border && border.DataContext is Product product)
            {
                var menu = new ContextMenu();
                var addItem = new MenuItem { Header = "➕ Добавить в корзину" };
                addItem.Click += (s, args) =>
                {
                    db.AddToCart(currentUserId, product.Id, product.FinalPrice);
                    UpdateCartCount();
                    MessageBox.Show($"Товар \"{product.Name}\" добавлен в корзину");
                };
                menu.Items.Add(addItem);
                menu.IsOpen = true;
            }
        }
    }
}