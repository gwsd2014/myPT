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

namespace myPTv1._0
{
    /// <summary>
    /// Interaction logic for FlexionExtensionView.xaml
    /// </summary>
    public partial class FlexionExtensionView : UserControl
    {
        public FlexionExtensionView()
        {
            InitializeComponent();
        }

        //fires when we have a tracked skeleton
/*
        private void kinectButton_Clicked(object sender, RoutedEventArgs e)
        {
            //Does something when the button has been clicked
            ButtonStatus.Text = "Button has been triggered";
            //MainWindow.SetPage(Pages.First);
        }

        private void kinectButton_Released()
        {
            //Does something when the button is released
            ButtonStatus.Text = "Button has been released";

        }

        public static double _itemTop, _topBoundary, _bottomBoundary, _itemLeft, _leftBoundary, _rightBoundary;


        //http://jellybean.codeplex.com/
        //taken from jellybean

        //taken from jellybean
        private static void FindValues(FrameworkElement container, FrameworkElement target)
        {
            var containerTopLeft = container.PointToScreen(new Point());
            var itemTopLeft = target.PointToScreen(new Point());

            _topBoundary = containerTopLeft.Y;
            _bottomBoundary = _topBoundary + container.ActualHeight;
            _leftBoundary = containerTopLeft.X;
            _rightBoundary = _leftBoundary + container.ActualWidth;

            //use midpoint of item (width or height divided by 2)
            _itemLeft = itemTopLeft.X + (target.ActualWidth / 2);
            _itemTop = itemTopLeft.Y + (target.ActualHeight / 2);
        }

        public static bool IsItemMidpointInContainer(FrameworkElement container, FrameworkElement target)
        {
            FindValues(container, target);

            if (_itemTop < _topBoundary || _bottomBoundary < _itemTop)
            {
                //Midpoint of target is outside of top or bottom
                return false;
            }

            if (_itemLeft < _leftBoundary || _rightBoundary < _itemLeft)
            {
                //Midpoint of target is outside of left or right
                return false;
            }
            return true;
        }

        private static bool CheckButton(HoverButton button, Ellipse thumbStick)
        {
            if (IsItemMidpointInContainer(button, thumbStick))
            {
                button.Hovering();
                return true;
            }
            else
            {
                button.Release();
                return false;
            }
        }

        
        public int scaleWidth = 640;
        public int scaleHeight = 480;

        private void SetEllipsePosition(FrameworkElement ellipse, Joint joint)
        {
           var scaledJoint = joint.ScaleTo(scaleWidth, scaleHeight);

            Canvas.SetLeft(ellipse, scaledJoint.Position.X);
            Canvas.SetTop(ellipse, scaledJoint.Position.Y);
        }

        public void SetLinePosition(Line line, Joint joint1, Joint joint2)
        {
       
            var scaledJoint1 = joint1.ScaleTo(scaleWidth, scaleHeight);
            var scaledJoint2 = joint2.ScaleTo(scaleWidth, scaleHeight);

            line.X1 = scaledJoint1.Position.X;
            line.X2 = scaledJoint2.Position.X;
            line.Y1 = scaledJoint1.Position.Y;
            line.Y2 = scaledJoint2.Position.Y;
        }
     */

    }
}
