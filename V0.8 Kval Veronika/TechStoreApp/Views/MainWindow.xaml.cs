using Microsoft.Data.Sqlite;
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using TechStoreApp.Data;
using TechStoreApp.Models;

namespace TechStoreApp.Views
{
    public partial class MainWindow : Window
    {
        private int currentUserId;
        private List<Product> allProducts = new List<Product>();
        private int cartItemsCount = 0;

        public MainWindow(int userId)
        {
            InitializeComponent();
            currentUserId = userId;
            LoadProducts();
            UpdateCartCount();
        }

        private void btnTheme_Click(object sender, RoutedEventArgs e)
        {
            ThemeManager.ToggleTheme();
        }

        private void btnSearch_Click(object sender, RoutedEventArgs e)
        {
            LoadProducts();
        }

        private void btnCart_Click(object sender, RoutedEventArgs e)
        {
            CartWindow cartWindow = new CartWindow(currentUserId);
            cartWindow.ShowDialog();
            UpdateCartCount();
        }

        private void LoadProducts()
        {
            allProducts = DatabaseHelper.GetAllProducts();
            productsList.Items.Clear();

            string searchText = txtSearch.Text;
            string sortType = (cmbSort.SelectedItem as ComboBoxItem)?.Content?.ToString() ?? "Без сортировки";

            var filtered = allProducts;
            if (!string.IsNullOrEmpty(searchText))
            {
                filtered = allProducts.FindAll(p =>
                    p.Name.ToLower().Contains(searchText.ToLower()) ||
                    p.Description.ToLower().Contains(searchText.ToLower())
                );
            }

            if (sortType != "Без сортировки")
            {
                if (sortType == "от 0% до 14.99%")
                    filtered = filtered.FindAll(p => p.DiscountPercent >= 0 && p.DiscountPercent <= 14.99);
                else if (sortType == "от 15% до 24.99%")
                    filtered = filtered.FindAll(p => p.DiscountPercent >= 15 && p.DiscountPercent <= 24.99);
                else if (sortType == "более 25%")
                    filtered = filtered.FindAll(p => p.DiscountPercent >= 25);
            }

            txtCounter.Text = $"Показано: {filtered.Count} из {allProducts.Count}";

            foreach (var product in filtered)
            {
                Border card = new Border();
                card.Margin = new Thickness(10);
                card.Padding = new Thickness(10);
                card.BorderBrush = System.Windows.Media.Brushes.LightGray;
                card.BorderThickness = new Thickness(1);
                card.CornerRadius = new CornerRadius(8);
                card.Width = 380;
                card.Background = System.Windows.Media.Brushes.White;

                Grid grid = new Grid();
                grid.ColumnDefinitions.Add(new ColumnDefinition { Width = System.Windows.GridLength.Auto });
                grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new System.Windows.GridLength(1, System.Windows.GridUnitType.Star) });
                grid.ColumnDefinitions.Add(new ColumnDefinition { Width = System.Windows.GridLength.Auto });

                System.Windows.Controls.Image img = new System.Windows.Controls.Image();
                img.Width = 70;
                img.Height = 70;
                img.Margin = new Thickness(5);
                img.Stretch = System.Windows.Media.Stretch.Uniform;

                string imgPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Images", product.ImagePath ?? "default.png");  // посмотрим в окно вывода
                if (System.IO.File.Exists(imgPath))
                {
                    img.Source = new System.Windows.Media.Imaging.BitmapImage(new Uri(imgPath));
                }
                else
                {
                    string defaultPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Images", "default.png");
                    if (System.IO.File.Exists(defaultPath))
                        img.Source = new System.Windows.Media.Imaging.BitmapImage(new Uri(defaultPath));
                }
                Grid.SetColumn(img, 0);

                StackPanel textPanel = new StackPanel();
                textPanel.Margin = new Thickness(10, 0, 10, 0);
                textPanel.VerticalAlignment = VerticalAlignment.Center;

                TextBlock nameBlock = new TextBlock();
                nameBlock.Text = product.Name;
                nameBlock.FontSize = 14;
                nameBlock.FontWeight = FontWeights.Bold;
                nameBlock.TextWrapping = System.Windows.TextWrapping.Wrap;

                TextBlock descBlock = new TextBlock();
                descBlock.Text = product.Description;
                descBlock.FontSize = 11;
                descBlock.Foreground = System.Windows.Media.Brushes.Gray;
                descBlock.TextWrapping = System.Windows.TextWrapping.Wrap;

                textPanel.Children.Add(nameBlock);
                textPanel.Children.Add(descBlock);
                Grid.SetColumn(textPanel, 1);

                StackPanel pricePanel = new StackPanel();
                pricePanel.HorizontalAlignment = HorizontalAlignment.Right;
                pricePanel.VerticalAlignment = VerticalAlignment.Center;

                TextBlock finalPrice = new TextBlock();
                finalPrice.Text = $"{product.FinalPrice:F2} ₽";
                finalPrice.FontSize = 16;
                finalPrice.FontWeight = FontWeights.Bold;
                finalPrice.Foreground = new System.Windows.Media.SolidColorBrush(
                    System.Windows.Media.Color.FromRgb(53, 154, 133));

                pricePanel.Children.Add(finalPrice);

                if (product.HasDiscount)
                {
                    TextBlock oldPrice = new TextBlock();
                    oldPrice.Text = $"{product.Price:F2} ₽";
                    oldPrice.FontSize = 11;
                    oldPrice.TextDecorations = TextDecorations.Strikethrough;
                    oldPrice.Foreground = System.Windows.Media.Brushes.Gray;
                    oldPrice.HorizontalAlignment = HorizontalAlignment.Right;
                    pricePanel.Children.Add(oldPrice);
                }

                Grid.SetColumn(pricePanel, 2);

                grid.Children.Add(img);
                grid.Children.Add(textPanel);
                grid.Children.Add(pricePanel);
                card.Child = grid;

                ContextMenu contextMenu = new ContextMenu();
                MenuItem refreshItem = new MenuItem();
                refreshItem.Header = "🔄 Обновить";
                refreshItem.Click += (s, e) => LoadProducts();
                MenuItem addToCartItem = new MenuItem();
                addToCartItem.Header = "➕ Добавить в корзину";
                addToCartItem.Click += (s, e) => AddToCart(product.Id);
                contextMenu.Items.Add(refreshItem);
                contextMenu.Items.Add(addToCartItem);
                card.ContextMenu = contextMenu;

                productsList.Items.Add(card);
            }
        }

        private void AddToCart(int productId)
        {
            using (var connection = DatabaseHelper.GetConnection())
            {
                connection.Open();
                string sql = "INSERT INTO Cart (UserId, ProductId) VALUES (@userId, @productId)";
                using (var cmd = new SqliteCommand(sql, connection))
                {
                    cmd.Parameters.AddWithValue("@userId", currentUserId);
                    cmd.Parameters.AddWithValue("@productId", productId);
                    cmd.ExecuteNonQuery();
                }
            }
            UpdateCartCount();
            MessageBox.Show("Товар добавлен в корзину!", "Успех", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void UpdateCartCount()
        {
            using (var connection = DatabaseHelper.GetConnection())
            {
                connection.Open();
                string sql = "SELECT COUNT(*) FROM Cart WHERE UserId = @userId";
                using (var cmd = new SqliteCommand(sql, connection))
                {
                    cmd.Parameters.AddWithValue("@userId", currentUserId);
                    cartItemsCount = Convert.ToInt32(cmd.ExecuteScalar());
                    btnCart.Content = $"🛒 Корзина ({cartItemsCount})";
                }
            }
        }
    }
}