using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Evex.Authentication;

namespace Evex.ContentView
{
    public partial class UserLogin : Window
    {
        public UserLogin() => InitializeComponent();

        private void OnLoad(object sender, RoutedEventArgs e)
        {
            /*
             * Check Is User Banned
             * Validate Version
             * Handle AutoJoin Setting
             */
        }

        private void MouseHandler(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
                this.DragMove();
        }
    }
}
