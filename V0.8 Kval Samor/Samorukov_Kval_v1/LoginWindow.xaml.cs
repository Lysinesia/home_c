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

using Samorukov.Services;

namespace Samorukov
{
    public partial class LoginWindow : Window
    {
        private DatabaseHelper db = new DatabaseHelper();

        public LoginWindow()
        {
            InitializeComponent();
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

            var user = db.LoginUser(login, password, out string error);

            if (user != null)
            {
                // Успешный вход - открываем главное окно
                MainWindow mainWindow = new MainWindow(user.Id);
                mainWindow.Show();
                this.Close();
            }
            else
            {
                txtError.Text = error;
            }
        }

        private void BtnRegister_Click(object sender, RoutedEventArgs e)
        {
            string login = txtLogin.Text.Trim();
            string password = txtPassword.Password;

            if (string.IsNullOrEmpty(login) || string.IsNullOrEmpty(password))
            {
                txtError.Text = "Введите логин и пароль для регистрации";
                return;
            }

            if (db.RegisterUser(login, password, out string error))
            {
                MessageBox.Show("Регистрация успешна! Теперь вы можете войти.",
                                "Успех", MessageBoxButton.OK, MessageBoxImage.Information);
                txtError.Text = "";
            }
            else
            {
                txtError.Text = error;
            }
        }
    }
}