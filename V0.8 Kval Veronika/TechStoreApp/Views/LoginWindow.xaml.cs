using System;
using System.Windows;
using Microsoft.Data.Sqlite;
using BCrypt.Net;

namespace TechStoreApp.Views
{
    public partial class LoginWindow : Window
    {
        public LoginWindow()
        {
            InitializeComponent();

            // Подписываем кнопки на события прямо в коде
            btnLogin.Click += BtnLogin_Click;
            btnRegister.Click += BtnRegister_Click;

            // Создаем базу данных при запуске
            Data.DatabaseHelper.InitializeDatabase();
        }

        private void BtnLogin_Click(object sender, RoutedEventArgs e)
        {
            string login = txtLogin.Text.Trim();
            string password = txtPassword.Password;

            if (string.IsNullOrEmpty(login) || string.IsNullOrEmpty(password))
            {
                txtError.Text = "Введите логин и пароль";
                return;
            }

            using (var connection = Data.DatabaseHelper.GetConnection())
            {
                connection.Open();
                string sql = "SELECT Id, PasswordHash, FailedAttempts, LockoutEnd FROM Users WHERE Login = @login";
                using (var cmd = new SqliteCommand(sql, connection))
                {
                    cmd.Parameters.AddWithValue("@login", login);
                    using (var reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            int userId = reader.GetInt32(0);
                            string hash = reader.GetString(1);
                            int attempts = reader.GetInt32(2);
                            string? lockoutEnd = reader.IsDBNull(3) ? null : reader.GetString(3);

                            if (!string.IsNullOrEmpty(lockoutEnd) && DateTime.Parse(lockoutEnd) > DateTime.Now)
                            {
                                txtError.Text = "Аккаунт заблокирован. Попробуйте позже.";
                                return;
                            }

                            if (BCrypt.Net.BCrypt.Verify(password, hash))
                            {
                                string resetSql = "UPDATE Users SET FailedAttempts = 0, LockoutEnd = NULL WHERE Login = @login";
                                using (var resetCmd = new SqliteCommand(resetSql, connection))
                                {
                                    resetCmd.Parameters.AddWithValue("@login", login);
                                    resetCmd.ExecuteNonQuery();
                                }

                                MessageBox.Show("Вход выполнен!", "Успех", MessageBoxButton.OK, MessageBoxImage.Information);

                                MainWindow mainWindow = new MainWindow(userId);
                                mainWindow.Show();
                                this.Close();
                            }
                            else
                            {
                                attempts++;
                                if (attempts >= 3)
                                {
                                    DateTime lockUntil = DateTime.Now.AddMinutes(5);
                                    string lockSql = "UPDATE Users SET FailedAttempts = @attempts, LockoutEnd = @lockout WHERE Login = @login";
                                    using (var lockCmd = new SqliteCommand(lockSql, connection))
                                    {
                                        lockCmd.Parameters.AddWithValue("@attempts", attempts);
                                        lockCmd.Parameters.AddWithValue("@lockout", lockUntil.ToString("o"));
                                        lockCmd.Parameters.AddWithValue("@login", login);
                                        lockCmd.ExecuteNonQuery();
                                    }
                                    txtError.Text = "3 неудачные попытки! Доступ заблокирован на 5 минут.";
                                }
                                else
                                {
                                    string failSql = "UPDATE Users SET FailedAttempts = @attempts WHERE Login = @login";
                                    using (var failCmd = new SqliteCommand(failSql, connection))
                                    {
                                        failCmd.Parameters.AddWithValue("@attempts", attempts);
                                        failCmd.Parameters.AddWithValue("@login", login);
                                        failCmd.ExecuteNonQuery();
                                    }
                                    txtError.Text = $"Неверный пароль! Осталось попыток: {3 - attempts}";
                                }
                            }
                        }
                        else
                        {
                            txtError.Text = "Пользователь не найден";
                        }
                    }
                }
            }
        }

        private void BtnRegister_Click(object sender, RoutedEventArgs e)
        {
            string login = txtLogin.Text.Trim();
            string password = txtPassword.Password;

            if (string.IsNullOrEmpty(login) || string.IsNullOrEmpty(password))
            {
                txtError.Text = "Введите логин и пароль";
                return;
            }

            if (password.Length < 3)
            {
                txtError.Text = "Пароль должен быть не менее 3 символов";
                return;
            }

            using (var connection = Data.DatabaseHelper.GetConnection())
            {
                connection.Open();

                string checkSql = "SELECT COUNT(*) FROM Users WHERE Login = @login";
                using (var checkCmd = new SqliteCommand(checkSql, connection))
                {
                    checkCmd.Parameters.AddWithValue("@login", login);
                    long count = Convert.ToInt64(checkCmd.ExecuteScalar() ?? 0L);
                    if (count > 0)
                    {
                        txtError.Text = "Логин уже занят";
                        return;
                    }
                }

                string hashedPassword = BCrypt.Net.BCrypt.HashPassword(password);
                string insertSql = "INSERT INTO Users (Login, PasswordHash, FailedAttempts, LockoutEnd) VALUES (@login, @hash, 0, NULL)";
                using (var insertCmd = new SqliteCommand(insertSql, connection))
                {
                    insertCmd.Parameters.AddWithValue("@login", login);
                    insertCmd.Parameters.AddWithValue("@hash", hashedPassword);
                    insertCmd.ExecuteNonQuery();
                }

                MessageBox.Show("Регистрация успешна! Теперь войдите.", "Успех", MessageBoxButton.OK, MessageBoxImage.Information);
                txtError.Text = "";
            }
        }
    }
}
