using System.Windows;

namespace ElectroWorld
{
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            // Запускаем окно авторизации
            LoginWindow loginWindow = new LoginWindow();
            loginWindow.Show();
        }
    }
}