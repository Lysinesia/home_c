using Microsoft.Data.Sqlite;
using System;
using System.Collections.Generic;
using System.IO;
using TechStoreApp.Models;

namespace TechStoreApp.Data
{
    public static class DatabaseHelper
    {
        private static string dbFile = "shop.db";
        private static string connectionString = "Data Source=" + dbFile;

        public static void InitializeDatabase()
        {
            if (!File.Exists(dbFile))
            {
                CreateTables();
                InsertTestProducts();
                CreateTestUser();
            }
        }

        private static void CreateTables()
        {
            using (var connection = new SqliteConnection(connectionString))
            {
                connection.Open();

                string usersTable = @"
                    CREATE TABLE IF NOT EXISTS Users (
                        Id INTEGER PRIMARY KEY AUTOINCREMENT,
                        Login TEXT UNIQUE NOT NULL,
                        PasswordHash TEXT NOT NULL,
                        FailedAttempts INTEGER NOT NULL DEFAULT 0,
                        LockoutEnd TEXT
                    )";

                string productsTable = @"
                    CREATE TABLE IF NOT EXISTS Products (
                        Id INTEGER PRIMARY KEY AUTOINCREMENT,
                        Name TEXT NOT NULL,
                        Description TEXT,
                        Price REAL NOT NULL,
                        DiscountPercent REAL NOT NULL DEFAULT 0,
                        ImagePath TEXT
                    )";

                string cartTable = @"
                    CREATE TABLE IF NOT EXISTS Cart (
                        Id INTEGER PRIMARY KEY AUTOINCREMENT,
                        UserId INTEGER NOT NULL,
                        ProductId INTEGER NOT NULL,
                        FOREIGN KEY(UserId) REFERENCES Users(Id),
                        FOREIGN KEY(ProductId) REFERENCES Products(Id)
                    )";

                string ordersTable = @"
                    CREATE TABLE IF NOT EXISTS Orders (
                        Id INTEGER PRIMARY KEY AUTOINCREMENT,
                        UserId INTEGER NOT NULL,
                        OrderDate TEXT NOT NULL,
                        TotalAmount REAL NOT NULL,
                        FOREIGN KEY(UserId) REFERENCES Users(Id)
                    )";

                using (var cmd = new SqliteCommand(usersTable, connection))
                    cmd.ExecuteNonQuery();
                using (var cmd = new SqliteCommand(productsTable, connection))
                    cmd.ExecuteNonQuery();
                using (var cmd = new SqliteCommand(cartTable, connection))
                    cmd.ExecuteNonQuery();
                using (var cmd = new SqliteCommand(ordersTable, connection))
                    cmd.ExecuteNonQuery();
            }
        }

        private static void InsertTestProducts()
        {
            using (var connection = new SqliteConnection(connectionString))
            {
                connection.Open();

                string[] names = { "Ноутбук игровой", "Беспроводная мышь", "Механическая клавиатура", "Монитор 27 дюймов", "Игровые наушники" };
                string[] descs = { "Мощный ноутбук с RTX 4060", "Тихая и удобная мышь", "С подсветкой и красными свитчами", "4K IPS матрица", "Объемный звук 7.1" };
                double[] prices = { 110000, 25234, 1201, 5000, 8999 };
                double[] discounts = { 15, 0, 15, 20, 5 };
                string[] images = { "laptop.png", "mouse.png", "keyboard.png", "monitor.png", "headphones.png" };

                for (int i = 0; i < names.Length; i++)
                {
                    string sql = "INSERT INTO Products (Name, Description, Price, DiscountPercent, ImagePath) VALUES (@name, @desc, @price, @discount, @image)";
                    using (var cmd = new SqliteCommand(sql, connection))
                    {
                        cmd.Parameters.AddWithValue("@name", names[i]);
                        cmd.Parameters.AddWithValue("@desc", descs[i]);
                        cmd.Parameters.AddWithValue("@price", prices[i]);
                        cmd.Parameters.AddWithValue("@discount", discounts[i]);
                        cmd.Parameters.AddWithValue("@image", images[i]);
                        cmd.ExecuteNonQuery();
                    }
                }
            }
        }

        private static void CreateTestUser()
        {
            using (var connection = new SqliteConnection(connectionString))
            {
                connection.Open();

                string checkSql = "SELECT COUNT(*) FROM Users WHERE Login = 'test'";
                using (var checkCmd = new SqliteCommand(checkSql, connection))
                {
                    long count = checkCmd.ExecuteScalar() as long? ?? 0;
                    if (count > 0) return;
                }

                string hashedPassword = BCrypt.Net.BCrypt.HashPassword("123");
                string sql = "INSERT INTO Users (Login, PasswordHash, FailedAttempts, LockoutEnd) VALUES ('test', @hash, 0, NULL)";
                using (var cmd = new SqliteCommand(sql, connection))
                {
                    cmd.Parameters.AddWithValue("@hash", hashedPassword);
                    cmd.ExecuteNonQuery();
                }
            }
        }

        public static List<Product> GetAllProducts()
        {
            var products = new List<Product>();
            using (var connection = new SqliteConnection(connectionString))
            {
                connection.Open();
                string sql = "SELECT Id, Name, Description, Price, DiscountPercent, ImagePath FROM Products";
                using (var cmd = new SqliteCommand(sql, connection))
                using (var reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        Product prod = new Product();
                        prod.Id = reader.GetInt32(0);
                        prod.Name = reader.GetString(1) ?? "";
                        prod.Description = reader.GetString(2) ?? "";
                        prod.Price = reader.GetDouble(3);
                        prod.DiscountPercent = reader.GetDouble(4);
                        prod.ImagePath = reader.GetString(5) ?? "";
                        products.Add(prod);
                    }
                }
            }
            return products;
        }

        public static SqliteConnection GetConnection()
        {
            return new SqliteConnection(connectionString);
        }
    }
}
