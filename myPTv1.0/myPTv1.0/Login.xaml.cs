﻿using System;
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
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : UserControl
    {
        Runtime nui;
        public Login()
        {
            InitializeComponent();
            SetupKinect();
        }
      
        private void SetupKinect()
        {
            //Lets a user know if a kinect has not been connected
            if (Runtime.Kinects.Count == 0) //note how to check # of kinects available
            {
                //do something to show that the kinect is not kinected.
                Console.WriteLine("No Kinect detected");
            }
            else
            {
                //use first kinect it finds and initialize the runtime
                nui = Runtime.Kinects[0];

                nui.Initialize(RuntimeOptions.UseColor | RuntimeOptions.UseDepthAndPlayerIndex | RuntimeOptions.UseSkeletalTracking | RuntimeOptions.UseDepth);

                //VIDEO FRAME INITS to see what the kinect see's.
                nui.VideoFrameReady += new EventHandler<ImageFrameReadyEventArgs>(nui_VideoFrameReady);

                nui.VideoStream.Open(ImageStreamType.Video, 2, ImageResolution.Resolution640x480, ImageType.Color);
                //nui.DepthStream.Open(ImageStreamType.Depth, 2, ImageResolution.Resolution320x240, ImageType.Depth);

                //Initialize the Skeleton Engine in order to get joint data
                nui.SkeletonEngine.TransformSmooth = true;
                var parameters = new TransformSmoothParameters
                {
                    Smoothing = 1.0f,
                    Correction = 0.1f,
                    Prediction = 0.1f,
                    JitterRadius = 0.05f,
                    MaxDeviationRadius = 0.05f
                };
                nui.SkeletonEngine.SmoothParameters = parameters;

                nui.SkeletonFrameReady += new EventHandler<SkeletonFrameReadyEventArgs>(nui_SkeletonFrameReady);

                //Tilt the camera to say hi!
                nui.NuiCamera.ElevationAngle = Camera.ElevationMaximum;
                nui.NuiCamera.ElevationAngle = 2;


                kinectButton.Click += new RoutedEventHandler(kinectButton_Clicked);
                //kinectButton.Release += new RoutedEventHandler(kinectButton_whatever);
            }
        }

        private void nui_SkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {
            //Console.Write("skeletonFrameready?\n");
            SkeletonFrame allSkeletons = e.SkeletonFrame;

            //Get just the first skeleton
            //get the first tracked skeleton
            SkeletonData skeleton = (from s in allSkeletons.Skeletons
                                     where s.TrackingState == SkeletonTrackingState.Tracked
                                     select s).FirstOrDefault();

            SetEllipsePosition(rightHandEllipse, skeleton.Joints[JointID.HandRight]);

            if (!CheckButton(kinectButton, rightHandEllipse))
            {
                //create action on release maybe?
            }
        }


        private void kinectButton_Clicked(object sender, RoutedEventArgs e)
        {
            //Does something when the button has been clicked
            Console.WriteLine("Button has been clicked");
            //Move to main menu page
            //MainWindow.SetPage(new FlexionExtension());
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
            var scaledJoint = joint.ScaleTo(scaleWidth, scaleHeight, .5f, .5f);

            Canvas.SetLeft(ellipse, scaledJoint.Position.X);
            Canvas.SetTop(ellipse, scaledJoint.Position.Y);
        }

        private void nui_VideoFrameReady(object sender, ImageFrameReadyEventArgs e)
        {
            Console.Write("VIDEO FRAME READY \n");
            PlanarImage image = e.ImageFrame.Image;
            imageVideoStream.Source = BitmapSource.Create(image.Width, image.Height, 96, 96, PixelFormats.Bgr32, null, image.Bits, image.Width * image.BytesPerPixel);
            //Can also use this from coding for fun
            //imageVideoStream.Source = e.ImageFrame.ToBitmapSource();
        }
    }
}
