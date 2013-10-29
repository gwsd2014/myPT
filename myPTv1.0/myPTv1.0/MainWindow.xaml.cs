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
        }

        Runtime nui;
        private void Window_Loaded_1(object sender, RoutedEventArgs e)
        {
            SetupKinect();
        }

        private void Grid_IsEnabledChanged_1(object sender, DependencyPropertyChangedEventArgs e)
        {

        }

        private void SetupKinect()
        {
            //Lets a user know if a kinect has not been connected
            if (Runtime.Kinects.Count == 0) //note how to check # of kinects available
            {
                this.Title = "No Kinect connected";
            }
            else
            {
                //use first kinect it finds and initialize the runtime
                nui = Runtime.Kinects[0];

                nui.Initialize(RuntimeOptions.UseColor | RuntimeOptions.UseDepthAndPlayerIndex | RuntimeOptions.UseSkeletalTracking | RuntimeOptions.UseDepth);

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

                nui.VideoFrameReady += new EventHandler<ImageFrameReadyEventArgs>(nui_VideoFrameReady);
                nui.SkeletonFrameReady += new EventHandler<SkeletonFrameReadyEventArgs>(nui_SkeletonFrameReady);

                nui.VideoStream.Open(ImageStreamType.Video, 2, ImageResolution.Resolution640x480, ImageType.Color);
                //nui.DepthStream.Open(ImageStreamType.Depth, 2, ImageResolution.Resolution320x240, ImageType.Depth);
                
                //Tilt the camera to say hi!
                nui.NuiCamera.ElevationAngle = Camera.ElevationMaximum;
                nui.NuiCamera.ElevationAngle = 2;
              }
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

            SetLinePosition(femur, skeleton.Joints[JointID.HipRight], skeleton.Joints[JointID.KneeRight]);
            SetLinePosition(tibia, skeleton.Joints[JointID.KneeRight], skeleton.Joints[JointID.AnkleRight]);

            ShowAngle(skeleton.Joints[JointID.HipRight], skeleton.Joints[JointID.KneeRight], skeleton.Joints[JointID.AnkleRight]);
        }

        private static int GetPlayerIndex(byte firstFrame)
        {
            //returns 0 = no player, 1 = 1st player, 2 = 2nd player...
            //Consider using this data to decide if camera needs to change azimuth?
            return (int)firstFrame & 7;
        }

        private int GetDistanceWithPlayerIndex(byte firstFrame, byte secondFrame)
        {
            //offset by 3 in first byte to get value after player index
            //then bitshift by 5 to get depth data
            int distance = (int)(firstFrame >> 3 | secondFrame << 5);
            return distance;
        }

         public int scaleWidth = 640;
        public int scaleHeight = 480; 

        private void SetEllipsePosition(FrameworkElement ellipse, Joint joint)
        {
            var scaledJoint = joint.ScaleTo(scaleWidth, scaleHeight, .5f, .5f);

            Canvas.SetLeft(ellipse, scaledJoint.Position.X);
            Canvas.SetTop(ellipse, scaledJoint.Position.Y);
        }

        public void SetLinePosition(Line line, Joint joint1, Joint joint2)
        {
            var scaledJoint1 = joint1.ScaleTo(scaleWidth, scaleHeight, .5f, .5f);
            var scaledJoint2 = joint2.ScaleTo(scaleWidth, scaleHeight, .5f, .5f);

            line.X1 = scaledJoint1.Position.X;
            line.X2 = scaledJoint2.Position.X;
            line.Y1 = scaledJoint1.Position.Y;
            line.Y2 = scaledJoint2.Position.Y;
        }

        public void ShowAngle(Joint alpha, Joint beta, Joint gamma)
        {
            double angle = 0.0;
            double a = System.Math.Abs(System.Math.Sqrt((beta.Position.X-gamma.Position.X)*(beta.Position.X-gamma.Position.X)+((beta.Position.Y-gamma.Position.Y)*(beta.Position.Y-gamma.Position.Y))));
            double b = System.Math.Abs(System.Math.Sqrt((alpha.Position.X-gamma.Position.X)*(alpha.Position.X-gamma.Position.X)+((alpha.Position.Y-gamma.Position.Y)*(alpha.Position.Y-gamma.Position.Y))));
            double c = System.Math.Abs(System.Math.Sqrt((alpha.Position.X-beta.Position.X)*(alpha.Position.X-beta.Position.X)+((alpha.Position.Y-beta.Position.Y)*(alpha.Position.Y-beta.Position.Y))));
            angle = Math.Abs(System.Math.Acos((a * a + c * c - b * b)/(2*a)));


            angle =  (angle * (180 / Math.PI));
            AngleText.Content = ((int)angle).ToString();
            AngleText.FontSize = 30;
            //AngleText.Canvas.Left = beta.Position.X+10;
            //AngleText.Canvas.Top = beta.Position.Y;
        }     
       
        void nui_VideoFrameReady(object sender, ImageFrameReadyEventArgs e)
        {

            //Just shows what the camera is capturing
            PlanarImage image = e.ImageFrame.Image;
            image1.Source = BitmapSource.Create(image.Width, image.Height,
            96, 96, PixelFormats.Bgr32, null, image.Bits, image.Width * image.BytesPerPixel);
            //Can also use this from coding for fun
            //image1.Source = e.ImageFrame.ToBitmapSource();
        }

        private void Grid_Unloaded_1(object sender, EventArgs e)
        {

        }

        private void Window_Unloaded_1(object sender, RoutedEventArgs e)
        {
            nui.Uninitialize();
            nui.NuiCamera.ElevationAngle = 0;

        }
    }
}
