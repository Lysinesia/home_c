using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Samorukov.Models;
using Samorukov.Services;

namespace Samorukov
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
            if (MessageBox.Show("Очистить корзину?", "Подтверждение", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
            {
                db.ClearCart(currentUserId);
                LoadCart();
            }
        }

        private void BtnCheckout_Click(object sender, RoutedEventArgs e)
        {
            if (db.CreateOrder(currentUserId, out string error))
                MessageBox.Show("Заказ оформлен!", "Успех", MessageBoxButton.OK, MessageBoxImage.Information);
            else
                MessageBox.Show(error, "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
        }

        private void ApplyTheme()
        {
            // Основной цвет для всех элементов
            string mainColor = MainWindow.IsDarkTheme ? "#fc8181" : "#19493f";
            // Фон окна (белый в основной, розовый в альтернативной)
            string bgColor = MainWindow.IsDarkTheme ? "#fc8181" : "White";

            // Применяем фон окна
            Background = GetBrush(bgColor);

            // Применяем цвет шапки
            var headerBorder = FindName("CartHeaderBorder") as Border;
            if (headerBorder != null)
                headerBorder.Background = GetBrush(mainColor);

            // Применяем цвет кнопок
            btnCheckout.Background = GetBrush(mainColor);
            btnClear.Background = GetBrush(mainColor);
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
                var removeItem = new MenuItem { Header = "❌ Удалить из корзины" };
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