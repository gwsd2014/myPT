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
using System.Windows.Navigation;
using System.Windows.Shapes;


using Microsoft.Research.Kinect.Nui;
using Microsoft.Research.Kinect.Audio;
using Coding4Fun.Kinect.Wpf;
using Coding4Fun.Kinect.Wpf.Controls;

//Buttons from http://opengameart.org/content/gui-buttons-activehover

namespace myPTv1._0
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            
            //Set the window view to the start point
            Console.Write("I am in the window loaded method");
            mainContentArea.Content = new FlexionExtensionView();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
           
        }

        private void Grid_IsEnabledChanged_1(object sender, DependencyPropertyChangedEventArgs e)
        {

        }        

        // ...
        public void SetPage(UserControl view)
        {
            mainContentArea.Content = view;
        }

        private void Grid_Unloaded_1(object sender, EventArgs e)
        {

        }

        private void Window_Unloaded_1(object sender, RoutedEventArgs e)
        {
        }
    }
}
