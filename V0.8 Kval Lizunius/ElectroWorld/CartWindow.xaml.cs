using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using ElectroWorld.Models;
using ElectroWorld.Services;

namespace ElectroWorld
{
    public partial class CartWindow : Window
    {
        private int currentUserId;
        private DatabaseHelper db = new DatabaseHelper();

        public CartWindow(int userId)
        {
            InitializeComponent();
            currentUserId = userId;
            ApplyTheme();
            LoadCart();
            cartGrid.MouseRightButtonDown += CartGrid_MouseRightButtonDown;
        }

        private void LoadCart()
        {
            cartGrid.ItemsSource = db.GetCart(currentUserId);
            txtTotal.Text = $"{db.GetCartTotal(currentUserId):0} ₽";
        }

        private void BtnClear_Click(object sender, RoutedEventArgs e)
        {
            if (MessageBox.Show("Очистить корзину?", "", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
            {
                db.ClearCart(currentUserId);
                LoadCart();
            }
        }

        private void BtnCheckout_Click(object sender, RoutedEventArgs e)
        {
            if (db.CreateOrder(currentUserId, out string error))
                MessageBox.Show("Заказ оформлен!");
            else
                MessageBox.Show(error);
        }

        private void ApplyTheme()
        {
            string headerColor = MainWindow.IsDarkTheme ? "#fc8181" : "#19493f";
            string buttonColor = MainWindow.IsDarkTheme ? "#fc8181" : "#359A85";
            string clearColor = MainWindow.IsDarkTheme ? "#359A85" : "#fc8181";
            string bgColor = MainWindow.IsDarkTheme ? "#fce4e4" : "White";

            Background = GetBrush(bgColor);

            var headerBorder = FindName("CartHeaderBorder") as Border;
            if (headerBorder != null)
                headerBorder.Background = GetBrush(headerColor);

            btnCheckout.Background = GetBrush(buttonColor);
            btnClear.Background = GetBrush(clearColor);
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

        private void CartGrid_MouseRightButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            if (cartGrid.SelectedItem is CartItem item)
            {
                var menu = new ContextMenu();
                var removeItem = new MenuItem { Header = "❌ Удалить" };
                removeItem.Click += (s, args) =>
                {
                    db.RemoveFromCart(currentUserId, item.Id);
                    LoadCart();
                };
                menu.Items.Add(removeItem);
                menu.IsOpen = true;
            }
        }
    }
}