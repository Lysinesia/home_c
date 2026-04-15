using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace TechStoreApp
{
    public static class ThemeManager
    {
        private static bool isGreenTheme = true;

        public static void ToggleTheme()
        {
            isGreenTheme = !isGreenTheme;
            ApplyTheme();
        }

        private static void ApplyTheme()
        {
            SolidColorBrush accentBrush;
            SolidColorBrush darkAccentBrush;

            if (isGreenTheme)
            {
                accentBrush = new SolidColorBrush(Color.FromRgb(53, 154, 133));
                darkAccentBrush = new SolidColorBrush(Color.FromRgb(25, 73, 63));
            }
            else
            {
                accentBrush = new SolidColorBrush(Color.FromRgb(252, 178, 178));
                darkAccentBrush = new SolidColorBrush(Color.FromRgb(252, 129, 129));
            }

            foreach (Window window in Application.Current.Windows)
            {
                ChangeWindowColors(window, accentBrush, darkAccentBrush);
            }
        }

        private static void ChangeWindowColors(Window window, SolidColorBrush accentBrush, SolidColorBrush darkAccentBrush)
        {
            var borders = FindVisualChildren<Border>(window);
            foreach (var border in borders)
            {
                if (border.Background is SolidColorBrush brush)
                {
                    string colorHex = brush.Color.ToString();
                    if (colorHex == "#FF19493F" || colorHex == "#FF19493f")
                        border.Background = darkAccentBrush;
                    else if (colorHex == "#FF359A85")
                        border.Background = accentBrush;
                }
            }

            var buttons = FindVisualChildren<Button>(window);
            foreach (var button in buttons)
            {
                if (button.Background is SolidColorBrush btnBrush)
                {
                    string colorHex = btnBrush.Color.ToString();
                    if (colorHex == "#FF359A85")
                        button.Background = accentBrush;
                    else if (colorHex == "#FF19493F" || colorHex == "#FF19493f")
                        button.Background = darkAccentBrush;
                }
            }

            var textBlocks = FindVisualChildren<TextBlock>(window);
            foreach (var text in textBlocks)
            {
                if (text.Foreground is SolidColorBrush textBrush && textBrush.Color.ToString() == "#FF359A85")
                    text.Foreground = accentBrush;
            }
        }

        private static IEnumerable<T> FindVisualChildren<T>(DependencyObject depObj) where T : DependencyObject
        {
            if (depObj == null) yield break;

            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(depObj); i++)
            {
                DependencyObject child = VisualTreeHelper.GetChild(depObj, i);
                if (child is T tChild)
                    yield return tChild;

                foreach (T childOfChild in FindVisualChildren<T>(child))
                    yield return childOfChild;
            }
        }
    }
}