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
            SetupKinect();
        }

        Runtime nui;
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
              
        }

        private void SetupKinect()
        {
            //Lets a user know if a kinect has not been connected
            if (Runtime.Kinects.Count == 0) //note how to check # of kinects available
            {
                //do something to show that the kinect is not kinected.
                //printf("No Kinect connected");
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

        void nui_VideoFrameReady(object sender, ImageFrameReadyEventArgs e)
        {
            //Just shows what the camera is capturing
            PlanarImage image = e.ImageFrame.Image;
            image1.Source = BitmapSource.Create(image.Width, image.Height, 96, 96, PixelFormats.Bgr32, null, image.Bits, image.Width * image.BytesPerPixel);
            //Can also use this from coding for fun
            //image1.Source = e.ImageFrame.ToBitmapSource();
        }
       

        //fires when we have a tracked skeleton
        void nui_SkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {
            SkeletonFrame allSkeletons = e.SkeletonFrame;

            //Get just the first skeleton
            //get the first tracked skeleton
            SkeletonData skeleton = (from s in allSkeletons.Skeletons
                                     where s.TrackingState == SkeletonTrackingState.Tracked
                                     select s).FirstOrDefault();


            //Makes Ellipse follow knee, ankle and hip on right side!
            //The SetEllipsePosition scales the joint data, so don't do it here!
            SetEllipsePosition(kneeEllipse, skeleton.Joints[JointID.KneeRight]);
            SetEllipsePosition(ankleEllipse, skeleton.Joints[JointID.AnkleRight]);
            SetEllipsePosition(thighEllipse, skeleton.Joints[JointID.HipRight]);
            SetEllipsePosition(rightHandEllipse, skeleton.Joints[JointID.HandRight]);

            SetEllipsePosition(LkneeEllipse, skeleton.Joints[JointID.KneeLeft]);
            SetEllipsePosition(LankleEllipse, skeleton.Joints[JointID.AnkleLeft]);
            SetEllipsePosition(LthighEllipse, skeleton.Joints[JointID.HipLeft]);
            SetEllipsePosition(leftHandEllipse, skeleton.Joints[JointID.HandLeft]);
            SetEllipsePosition(LElbowEllipse, skeleton.Joints[JointID.ElbowLeft]);
            SetEllipsePosition(RElbowEllipse, skeleton.Joints[JointID.ElbowRight]);
            SetEllipsePosition(headEllipse, skeleton.Joints[JointID.Head]);
            SetEllipsePosition(neckEllipse, skeleton.Joints[JointID.ShoulderCenter]);
            SetEllipsePosition(LShoulderEllipse, skeleton.Joints[JointID.ShoulderLeft]);
            SetEllipsePosition(RShoulderEllipse, skeleton.Joints[JointID.ShoulderRight]);
            SetEllipsePosition(hipEllipse, skeleton.Joints[JointID.HipCenter]);
            SetEllipsePosition(spineEllipse, skeleton.Joints[JointID.Spine]);

            SetLinePosition(Neck, skeleton.Joints[JointID.Head], skeleton.Joints[JointID.ShoulderCenter]);
            SetLinePosition(ClavicleLeft, skeleton.Joints[JointID.ShoulderLeft], skeleton.Joints[JointID.ShoulderCenter]);
            SetLinePosition(ClavicleRight, skeleton.Joints[JointID.ShoulderRight], skeleton.Joints[JointID.ShoulderCenter]);
            SetLinePosition(Spine, skeleton.Joints[JointID.Spine], skeleton.Joints[JointID.ShoulderCenter]);
            SetLinePosition(HumerusLeft, skeleton.Joints[JointID.ShoulderLeft], skeleton.Joints[JointID.ElbowLeft]);
            SetLinePosition(HumerusRight, skeleton.Joints[JointID.ShoulderRight], skeleton.Joints[JointID.ElbowRight]);
            SetLinePosition(RadiusLeft, skeleton.Joints[JointID.ElbowLeft], skeleton.Joints[JointID.WristLeft]);
            SetLinePosition(RadiusRight, skeleton.Joints[JointID.ElbowRight], skeleton.Joints[JointID.WristRight]);
            SetLinePosition(PelvisLeft, skeleton.Joints[JointID.HipLeft], skeleton.Joints[JointID.HipCenter]);
            SetLinePosition(PelvisRight, skeleton.Joints[JointID.HipRight], skeleton.Joints[JointID.HipCenter]);
            SetLinePosition(Spine, skeleton.Joints[JointID.Spine], skeleton.Joints[JointID.HipCenter]);
            SetLinePosition(FemurLeft, skeleton.Joints[JointID.HipLeft], skeleton.Joints[JointID.KneeLeft]);
            SetLinePosition(TibiaLeft, skeleton.Joints[JointID.KneeLeft], skeleton.Joints[JointID.AnkleLeft]);

            SetLinePosition(femur, skeleton.Joints[JointID.HipRight], skeleton.Joints[JointID.KneeRight]);
            SetLinePosition(tibia, skeleton.Joints[JointID.KneeRight], skeleton.Joints[JointID.AnkleRight]);

            ShowAngle(skeleton.Joints[JointID.HipRight], skeleton.Joints[JointID.KneeRight], skeleton.Joints[JointID.AnkleRight]);

            if (!CheckButton(kinectButton, rightHandEllipse))
            {
                kinectButton_Released();
            }

        }

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

        public void ShowAngle(Joint alpha, Joint beta, Joint gamma)
        {
            double angle = 0.0;
            /*
            double a = System.Math.Abs(System.Math.Sqrt((beta.Position.X-gamma.Position.X)*(beta.Position.X-gamma.Position.X)+((beta.Position.Y-gamma.Position.Y)*(beta.Position.Y-gamma.Position.Y))));
            double b = System.Math.Abs(System.Math.Sqrt((alpha.Position.X-gamma.Position.X)*(alpha.Position.X-gamma.Position.X)+((alpha.Position.Y-gamma.Position.Y)*(alpha.Position.Y-gamma.Position.Y))));
            double c = System.Math.Abs(System.Math.Sqrt((alpha.Position.X-beta.Position.X)*(alpha.Position.X-beta.Position.X)+((alpha.Position.Y-beta.Position.Y)*(alpha.Position.Y-beta.Position.Y))));
            angle = Math.Abs(System.Math.Acos((a * a + c * c - b * b)/(2*a)));

            */
            double[] alphabeta = { alpha.Position.X - beta.Position.X, alpha.Position.Y - beta.Position.Y, alpha.Position.Z - beta.Position.Z };
            double[] gammabeta = { gamma.Position.X - beta.Position.X, gamma.Position.Y - beta.Position.Y, gamma.Position.Z - beta.Position.Z };

            double sumofproducts = 0.0;
            for (int i = 0; i < 3; i++)
            {
                sumofproducts += alphabeta[i] * gammabeta[i];
            }

            double alphabeta_magitude = System.Math.Sqrt(alphabeta[0] * alphabeta[0] + alphabeta[1] * alphabeta[1] + alphabeta[2] * alphabeta[2]);
            double gammabeta_magitude = System.Math.Sqrt(gammabeta[0] * gammabeta[0] + gammabeta[1] * gammabeta[1] + gammabeta[2] * gammabeta[2]);

            angle = System.Math.Acos(sumofproducts / (alphabeta_magitude * gammabeta_magitude));

            angle = (angle * (180 / Math.PI));
            AngleText.Content = ((int)angle).ToString();
            AngleText.FontSize = 30;
            //AngleText.Canvas.Left = beta.Position.X+10;
            //AngleText.Canvas.Top = beta.Position.Y;
        }
        private void Window_Closed(object sender, EventArgs e)
        {
            nui.Uninitialize();
        }
    }
}
