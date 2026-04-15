using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using Microsoft.Data.Sqlite;
using TechStoreApp.Data;

namespace TechStoreApp.Views
{
    public partial class CartWindow : Window
    {
        private int currentUserId;
        private List<CartItem> cartItems = new List<CartItem>();

        public CartWindow(int userId)
        {
            InitializeComponent();
            currentUserId = userId;
            LoadCart();

            // Подписываем кнопку темы
            btnTheme.Click += btnTheme_Click;
        }

        private void LoadCart()
        {
            cartItems = new List<CartItem>();
            double total = 0;

            using (var connection = DatabaseHelper.GetConnection())
            {
                connection.Open();
                string sql = "SELECT p.Name, p.Description, p.Price, p.DiscountPercent FROM Cart c JOIN Products p ON c.ProductId = p.Id WHERE c.UserId = @userId";
                using (var cmd = new SqliteCommand(sql, connection))
                {
                    cmd.Parameters.AddWithValue("@userId", currentUserId);
                    using (var reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            string name = reader.GetString(0);
                            string desc = reader.GetString(1);
                            double price = reader.GetDouble(2);
                            double discount = reader.GetDouble(3);
                            double finalPrice = price * (1 - discount / 100.0);

                            CartItem item = new CartItem();
                            item.Name = name;
                            item.Description = desc;
                            item.Price = finalPrice;

                            cartItems.Add(item);
                            total = total + finalPrice;
                        }
                    }
                }
            }

            dgCart.ItemsSource = cartItems;
            txtTotal.Text = total.ToString("F2") + " ₽";
        }

        private void btnClearCart_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult result = MessageBox.Show("Очистить корзину?", "Подтверждение", MessageBoxButton.YesNo);
            if (result == MessageBoxResult.Yes)
            {
                using (var connection = DatabaseHelper.GetConnection())
                {
                    connection.Open();
                    string sql = "DELETE FROM Cart WHERE UserId = @userId";
                    using (var cmd = new SqliteCommand(sql, connection))
                    {
                        cmd.Parameters.AddWithValue("@userId", currentUserId);
                        cmd.ExecuteNonQuery();
                    }
                }
                LoadCart();
            }
        }

        private void btnCheckout_Click(object sender, RoutedEventArgs e)
        {
            if (cartItems.Count == 0)
            {
                MessageBox.Show("Корзина пуста!");
                return;
            }

            MessageBoxResult result = MessageBox.Show("Оформить заказ?", "Подтверждение", MessageBoxButton.YesNo);
            if (result == MessageBoxResult.Yes)
            {
                double total = 0;
                foreach (var item in cartItems) total = total + item.Price;

                using (var connection = DatabaseHelper.GetConnection())
                {
                    connection.Open();
                    string sql = "INSERT INTO Orders (UserId, OrderDate, TotalAmount) VALUES (@userId, @date, @total)";
                    using (var cmd = new SqliteCommand(sql, connection))
                    {
                        cmd.Parameters.AddWithValue("@userId", currentUserId);
                        cmd.Parameters.AddWithValue("@date", DateTime.Now.ToString("o"));
                        cmd.Parameters.AddWithValue("@total", total);
                        cmd.ExecuteNonQuery();
                    }

                    string clearSql = "DELETE FROM Cart WHERE UserId = @userId";
                    using (var clearCmd = new SqliteCommand(clearSql, connection))
                    {
                        clearCmd.Parameters.AddWithValue("@userId", currentUserId);
                        clearCmd.ExecuteNonQuery();
                    }
                }

                MessageBox.Show("Заказ оформлен!");
                LoadCart();
            }
        }

        private void btnTheme_Click(object sender, RoutedEventArgs e)
        {
            ThemeManager.ToggleTheme();
        }
    }

    public class CartItem
    {
        public string Name { get; set; } = "";
        public string Description { get; set; } = "";
        public double Price { get; set; }
    }
}