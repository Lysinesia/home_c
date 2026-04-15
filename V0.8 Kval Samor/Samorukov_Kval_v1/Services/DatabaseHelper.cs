using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SQLite;
using System.IO;
using System.Security.Cryptography;
using Samorukov.Models;

namespace Samorukov.Services
{
    public class DatabaseHelper
    {
        private string connectionString;

        public DatabaseHelper()
        {
            string dbPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "database.db");
            connectionString = $"Data Source={dbPath};Version=3;";
            InitializeDatabase();
        }

        private SQLiteConnection GetConnection() => new SQLiteConnection(connectionString);

        private void InitializeDatabase()
        {
            using (var connection = GetConnection())
            {
                connection.Open();

                using (var cmd = new SQLiteCommand(@"CREATE TABLE IF NOT EXISTS Users (
                    Id INTEGER PRIMARY KEY AUTOINCREMENT,
                    Login TEXT UNIQUE NOT NULL,
                    PasswordHash TEXT NOT NULL,
                    FailedAttempts INTEGER DEFAULT 0,
                    LockedUntil TEXT)", connection))
                    cmd.ExecuteNonQuery();

                using (var cmd = new SQLiteCommand(@"CREATE TABLE IF NOT EXISTS Products (
                    Id INTEGER PRIMARY KEY AUTOINCREMENT,
                    Name TEXT NOT NULL,
                    Description TEXT,
                    Price REAL NOT NULL,
                    DiscountPercent REAL DEFAULT 0,
                    ImagePath TEXT)", connection))
                    cmd.ExecuteNonQuery();

                using (var cmd = new SQLiteCommand(@"CREATE TABLE IF NOT EXISTS Cart (
                    Id INTEGER PRIMARY KEY AUTOINCREMENT,
                    UserId INTEGER NOT NULL,
                    ProductId INTEGER NOT NULL,
                    Quantity INTEGER DEFAULT 1,
                    PriceAtAdd REAL NOT NULL,
                    FOREIGN KEY (UserId) REFERENCES Users(Id),
                    FOREIGN KEY (ProductId) REFERENCES Products(Id))", connection))
                    cmd.ExecuteNonQuery();

                using (var cmd = new SQLiteCommand(@"CREATE TABLE IF NOT EXISTS Orders (
                    Id INTEGER PRIMARY KEY AUTOINCREMENT,
                    UserId INTEGER NOT NULL,
                    OrderDate TEXT NOT NULL,
                    TotalAmount REAL NOT NULL,
                    FOREIGN KEY (UserId) REFERENCES Users(Id))", connection))
                    cmd.ExecuteNonQuery();

                using (var cmd = new SQLiteCommand(@"CREATE TABLE IF NOT EXISTS OrderItems (
                    Id INTEGER PRIMARY KEY AUTOINCREMENT,
                    OrderId INTEGER NOT NULL,
                    ProductId INTEGER NOT NULL,
                    ProductName TEXT NOT NULL,
                    PriceAtOrder REAL NOT NULL,
                    Quantity INTEGER NOT NULL,
                    FOREIGN KEY (OrderId) REFERENCES Orders(Id))", connection))
                    cmd.ExecuteNonQuery();

                AddTestData(connection);
            }
        }

        private void AddTestData(SQLiteConnection connection)
        {

            using (var cmd = new SQLiteCommand("SELECT COUNT(*) FROM Products", connection))
            {
                if (Convert.ToInt32(cmd.ExecuteScalar()) > 0) return;
            }

            var products = new[]
            {
                new { Name = "Микроконтроллер ElectroSTM-F4", Description = "ARM Cortex-M4, 512KB Flash", Price = 1250m, Discount = 2m },
                new { Name = "Набор резисторов ElectroRes Pack", Description = "1206, 100шт, 10 значений", Price = 320m, Discount = 5m },
                new { Name = "Конденсатор электролитический 1000мкФ", Description = "50В, низкий ESR, 105°C", Price = 85m, Discount = 45m },
                new { Name = "Транзистор MOSFET IRFZ44N", Description = "55V, 49A, TO-220", Price = 140m, Discount = 10m },
                new { Name = "Модуль Bluetooth HC-05", Description = "UART, мастер/ведомый", Price = 550m, Discount = 3m },
                new { Name = "Дисплей OLED 0.96\"", Description = "128x64, I2C, белый", Price = 390m, Discount = 5m },
                new { Name = "Плата Arduino Nano V3", Description = "CH340, ATmega328P", Price = 680m, Discount = 10m },
                new { Name = "Датчик температуры DHT22", Description = "влажность+температура, цифровой", Price = 420m, Discount = 123m },
                new { Name = "Тактовая кнопка 6x6x5", Description = "10шт, высота 5мм", Price = 90m, Discount = 15m },
                new { Name = "Светодиод 5мм красный", Description = "20шт, 1.8-2.2V", Price = 70m, Discount = 6m },
                new { Name = "Зуммер пассивный", Description = "5V, генерация тонов", Price = 110m, Discount = 7m },
                new { Name = "Потенциометр 10кОм", Description = "WH148, ручка, линейный", Price = 190m, Discount = 5m },
                new { Name = "Стабилизатор LM2596", Description = "понижающий DC-DC, до 3A", Price = 280m, Discount = 56m },
                new { Name = "ESP8266 NodeMCU v3", Description = "WiFi, CH340, microUSB", Price = 790m, Discount = 12m },
                new { Name = "Реле 5V 1 канал", Description = "оптопара, активный низкий", Price = 230m, Discount = 4m },
                new { Name = "Индикатор 7-сегментный 0.56\"", Description = "4 разряда, общий катод", Price = 310m, Discount = 67m },
                new { Name = "Тактовый генератор 16MHz", Description = "HC-49S, 50ppm", Price = 45m, Discount = 10m },
                new { Name = "Фоторезистор GL5528", Description = "5-10кОм, 5мм", Price = 60m, Discount = 8m },
                new { Name = "Драйвер моторов L298N", Description = "до 46V, 2A на канал", Price = 520m, Discount = 8m },
                new { Name = "Набор перемычек Dupont", Description = "120шт, 20см, мама-папа", Price = 240m, Discount = 5m }
            };

            foreach (var p in products)
            {
                using (var cmd = new SQLiteCommand(@"INSERT INTO Products (Name, Description, Price, DiscountPercent, ImagePath) 
                    VALUES (@name, @desc, @price, @discount, 'default.png')", connection))
                {
                    cmd.Parameters.AddWithValue("@name", p.Name);
                    cmd.Parameters.AddWithValue("@desc", p.Description);
                    cmd.Parameters.AddWithValue("@price", p.Price);
                    cmd.Parameters.AddWithValue("@discount", p.Discount);
                    cmd.ExecuteNonQuery();
                }
            }

            var users = new[]
            {
                new { Login = "admin", Password = "admin" },

            };

            foreach (var u in users)
            {
                using (var cmd = new SQLiteCommand("INSERT INTO Users (Login, PasswordHash, FailedAttempts) VALUES (@login, @hash, 0)", connection))
                {
                    cmd.Parameters.AddWithValue("@login", u.Login);
                    cmd.Parameters.AddWithValue("@hash", HashPassword(u.Password));
                    cmd.ExecuteNonQuery();
                }
            }
        }

        private string HashPassword(string password)
        {
            using (SHA256 sha256 = SHA256.Create())
                return Convert.ToBase64String(sha256.ComputeHash(Encoding.UTF8.GetBytes(password)));
        }

        public bool RegisterUser(string login, string password, out string error)
        {
            error = "";
            if (string.IsNullOrWhiteSpace(login) || string.IsNullOrWhiteSpace(password))
            {
                error = "Логин и пароль не могут быть пустыми";
                return false;
            }

            using (var connection = GetConnection())
            {
                connection.Open();
                try
                {
                    using (var cmd = new SQLiteCommand("INSERT INTO Users (Login, PasswordHash, FailedAttempts) VALUES (@login, @hash, 0)", connection))
                    {
                        cmd.Parameters.AddWithValue("@login", login);
                        cmd.Parameters.AddWithValue("@hash", HashPassword(password));
                        cmd.ExecuteNonQuery();
                    }
                    return true;
                }
                catch
                {
                    error = "Пользователь уже существует";
                    return false;
                }
            }
        }

        public User? LoginUser(string login, string password, out string error)
        {
            error = "";
            using (var connection = GetConnection())
            {
                connection.Open();
                User? user = null;

                using (var cmd = new SQLiteCommand("SELECT * FROM Users WHERE Login = @login", connection))
                {
                    cmd.Parameters.AddWithValue("@login", login);
                    using (var reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            user = new User
                            {
                                Id = reader.GetInt32(0),
                                Login = reader.GetString(1),
                                PasswordHash = reader.GetString(2),
                                FailedAttempts = reader.GetInt32(3),
                                LockedUntil = reader.IsDBNull(4) ? null : DateTime.Parse(reader.GetString(4))
                            };
                        }
                    }
                }

                if (user == null)
                {
                    error = "Неверный логин или пароль";
                    return null;
                }

                if (user.LockedUntil.HasValue && user.LockedUntil.Value > DateTime.Now)
                {
                    error = $"Аккаунт заблокирован до {user.LockedUntil.Value.ToShortTimeString()}";
                    return null;
                }

                if (user.PasswordHash == HashPassword(password))
                {
                    using (var cmd = new SQLiteCommand("UPDATE Users SET FailedAttempts = 0, LockedUntil = NULL WHERE Id = @id", connection))
                    {
                        cmd.Parameters.AddWithValue("@id", user.Id);
                        cmd.ExecuteNonQuery();
                    }
                    return user;
                }

                int newAttempts = user.FailedAttempts + 1;
                if (newAttempts >= 3)
                {
                    DateTime lockUntil = DateTime.Now.AddMinutes(5);
                    using (var cmd = new SQLiteCommand("UPDATE Users SET FailedAttempts = @attempts, LockedUntil = @lockUntil WHERE Id = @id", connection))
                    {
                        cmd.Parameters.AddWithValue("@attempts", newAttempts);
                        cmd.Parameters.AddWithValue("@lockUntil", lockUntil.ToString("yyyy-MM-dd HH:mm:ss"));
                        cmd.Parameters.AddWithValue("@id", user.Id);
                        cmd.ExecuteNonQuery();
                    }
                    error = "Превышено количество попыток. Аккаунт заблокирован на 5 минут";
                }
                else
                {
                    using (var cmd = new SQLiteCommand("UPDATE Users SET FailedAttempts = @attempts WHERE Id = @id", connection))
                    {
                        cmd.Parameters.AddWithValue("@attempts", newAttempts);
                        cmd.Parameters.AddWithValue("@id", user.Id);
                        cmd.ExecuteNonQuery();
                    }
                    error = $"Неверный пароль. Осталось попыток: {3 - newAttempts}";
                }
                return null;
            }
        }

        public List<Product> GetAllProducts()
        {
            var products = new List<Product>();
            using (var connection = GetConnection())
            {
                connection.Open();
                using (var cmd = new SQLiteCommand("SELECT * FROM Products", connection))
                using (var reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        products.Add(new Product
                        {
                            Id = reader.GetInt32(0),
                            Name = reader.GetString(1),
                            Description = reader.IsDBNull(2) ? "" : reader.GetString(2),
                            Price = (decimal)reader.GetDouble(3),
                            DiscountPercent = (decimal)reader.GetDouble(4),
                            ImagePath = reader.IsDBNull(5) ? "default.png" : reader.GetString(5)
                        });
                    }
                }
            }
            return products;
        }

        public List<Product> SearchProducts(string searchText)
        {
            var products = new List<Product>();
            using (var connection = GetConnection())
            {
                connection.Open();
                using (var cmd = new SQLiteCommand("SELECT * FROM Products WHERE Name LIKE @search OR Description LIKE @search", connection))
                {
                    cmd.Parameters.AddWithValue("@search", $"%{searchText}%");
                    using (var reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            products.Add(new Product
                            {
                                Id = reader.GetInt32(0),
                                Name = reader.GetString(1),
                                Description = reader.IsDBNull(2) ? "" : reader.GetString(2),
                                Price = (decimal)reader.GetDouble(3),
                                DiscountPercent = (decimal)reader.GetDouble(4),
                                ImagePath = reader.IsDBNull(5) ? "default.png" : reader.GetString(5)
                            });
                        }
                    }
                }
            }
            return products;
        }

        public void AddToCart(int userId, int productId, decimal price)
        {
            using (var connection = GetConnection())
            {
                connection.Open();
                using (var cmd = new SQLiteCommand("INSERT INTO Cart (UserId, ProductId, Quantity, PriceAtAdd) VALUES (@userId, @productId, 1, @price)", connection))
                {
                    cmd.Parameters.AddWithValue("@userId", userId);
                    cmd.Parameters.AddWithValue("@productId", productId);
                    cmd.Parameters.AddWithValue("@price", price);
                    cmd.ExecuteNonQuery();
                }
            }
        }

        public List<CartItem> GetCart(int userId)
        {
            var cart = new List<CartItem>();
            using (var connection = GetConnection())
            {
                connection.Open();
                using (var cmd = new SQLiteCommand(@"SELECT p.Id, p.Name, p.Description, c.PriceAtAdd, c.Quantity 
                    FROM Cart c JOIN Products p ON c.ProductId = p.Id WHERE c.UserId = @userId", connection))
                {
                    cmd.Parameters.AddWithValue("@userId", userId);
                    using (var reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            cart.Add(new CartItem
                            {
                                Id = reader.GetInt32(0),
                                Name = reader.GetString(1),
                                Description = reader.IsDBNull(2) ? "" : reader.GetString(2),
                                Price = (decimal)reader.GetDouble(3),
                                Quantity = reader.GetInt32(4)
                            });
                        }
                    }
                }
            }
            return cart;
        }

        public decimal GetCartTotal(int userId)
        {
            using (var connection = GetConnection())
            {
                connection.Open();
                using (var cmd = new SQLiteCommand("SELECT SUM(PriceAtAdd * Quantity) FROM Cart WHERE UserId = @userId", connection))
                {
                    cmd.Parameters.AddWithValue("@userId", userId);
                    var result = cmd.ExecuteScalar();
                    if (result == null || result == DBNull.Value)
                        return 0;
                    return Convert.ToDecimal(result);
                }
            }
        }

        public void RemoveFromCart(int userId, int productId)
        {
            using (var connection = GetConnection())
            {
                connection.Open();
                using (var cmd = new SQLiteCommand("DELETE FROM Cart WHERE UserId = @userId AND ProductId = @productId", connection))
                {
                    cmd.Parameters.AddWithValue("@userId", userId);
                    cmd.Parameters.AddWithValue("@productId", productId);
                    cmd.ExecuteNonQuery();
                }
            }
        }

        public void ClearCart(int userId)
        {
            using (var connection = GetConnection())
            {
                connection.Open();
                using (var cmd = new SQLiteCommand("DELETE FROM Cart WHERE UserId = @userId", connection))
                {
                    cmd.Parameters.AddWithValue("@userId", userId);
                    cmd.ExecuteNonQuery();
                }
            }
        }

        public bool CreateOrder(int userId, out string error)
        {
            error = "";
            var cart = GetCart(userId);
            if (cart.Count == 0)
            {
                error = "Корзина пуста";
                return false;
            }

            using (var connection = GetConnection())
            {
                connection.Open();
                using (var transaction = connection.BeginTransaction())
                {
                    try
                    {
                        int orderId;
                        using (var cmd = new SQLiteCommand(@"INSERT INTO Orders (UserId, OrderDate, TotalAmount) 
                            VALUES (@userId, @date, @total); SELECT last_insert_rowid();", connection, transaction))
                        {
                            cmd.Parameters.AddWithValue("@userId", userId);
                            cmd.Parameters.AddWithValue("@date", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
                            cmd.Parameters.AddWithValue("@total", GetCartTotal(userId));
                            orderId = Convert.ToInt32(cmd.ExecuteScalar());
                        }

                        foreach (var item in cart)
                        {
                            using (var cmd = new SQLiteCommand(@"INSERT INTO OrderItems (OrderId, ProductId, ProductName, PriceAtOrder, Quantity) 
                                VALUES (@orderId, @productId, @productName, @price, @quantity)", connection, transaction))
                            {
                                cmd.Parameters.AddWithValue("@orderId", orderId);
                                cmd.Parameters.AddWithValue("@productId", item.Id);
                                cmd.Parameters.AddWithValue("@productName", item.Name);
                                cmd.Parameters.AddWithValue("@price", item.Price);
                                cmd.Parameters.AddWithValue("@quantity", item.Quantity);
                                cmd.ExecuteNonQuery();
                            }
                        }

                        using (var cmd = new SQLiteCommand("DELETE FROM Cart WHERE UserId = @userId", connection, transaction))
                        {
                            cmd.Parameters.AddWithValue("@userId", userId);
                            cmd.ExecuteNonQuery();
                        }

                        transaction.Commit();
                        return true;
                    }
                    catch
                    {
                        transaction.Rollback();
                        error = "Ошибка при оформлении заказа";
                        return false;
                    }
                }
            }
        }
    }
}