using System.Windows;
using ElectroWorld.Services;

namespace ElectroWorld
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
            var user = db.LoginUser(txtLogin.Text.Trim(), txtPassword.Password, out string error);
            if (user != null)
            {
                new MainWindow(user.Id).Show();
                Close();
            }
            else txtError.Text = error;
        }

        private void BtnRegister_Click(object sender, RoutedEventArgs e)
        {
            if (db.RegisterUser(txtLogin.Text.Trim(), txtPassword.Password, out string error))
                MessageBox.Show("Регистрация успешна!");
            else txtError.Text = error;
        }
    }
}