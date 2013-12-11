using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Microsoft.Research.Kinect.Nui;
using Microsoft.Research.Kinect.Audio;
using Coding4Fun.Kinect.Wpf;
using Coding4Fun.Kinect.Wpf.Controls;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Shapes;

namespace myPTv1._0
{
    public enum MyJointID: int{HipCenter, Spine, ShoulderCenter, Head, ShoulderLeft, ElbowLeft, WristLeft, HandLeft, ElbowRight, WristRight, HandRight, HipLeft, KneeLeft, AnkleLeft, FootLeft, HipRight, KneeRight, AnkleRight, FootRight};

    class KinectRuntime : IkinectService
    {
        Runtime nui;
        public SkeletonData skeleton;

        //Create global Skeleton Parts
        /*
        public KinectRuntime(Canvas canvas, int canvasWidth, int canvasHeight, Image image)
        {
            SetupKinect();
            this.canvas = canvas;
            this.canvasWidth = canvasWidth;
            this.canvasHeight = canvasHeight;
            this.videoFrame = image;
        }
         */

        public void Initialize()
        {
            SetupKinect();
        }

        public void SetupKinect()
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

            }
        }


        //Could these be implemented elsewhere?
        private void nui_SkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {
            SkeletonFrame allSkeletons = e.SkeletonFrame;

            //Get just the first skeleton
            //get the first tracked skeleton
            skeleton = (from s in allSkeletons.Skeletons
                                     where s.TrackingState == SkeletonTrackingState.Tracked
                                     select s).FirstOrDefault();
            if (skeleton == null)
            {
                return;
            }

            //Create an temporary array to store where the joints are now!
            Joint[] jointPositions = new Joint[20];
            for (int i = 0; i < 20; i++)
            {
                jointPositions[i] = skeleton.Joints[(JointID)i];
            }

                if (this.SkeletonUpdated != null)
                {
                    //UPDATE Joints in SkeletonEventArgs
                    this.SkeletonUpdated(this, new SkeletonEventArgs() { Joints = jointPositions });
                }
        }

        private void nui_VideoFrameReady(object sender, ImageFrameReadyEventArgs e)
        {
            //Just shows what the camera is capturing
            PlanarImage image = e.ImageFrame.Image;
           // videoFrame.Source = BitmapSource.Create(image.Width, image.Height, 96, 96, PixelFormats.Bgr32, null, image.Bits, image.Width * image.BytesPerPixel);
            //Can also use this from coding for fun
            //videoFrame.Source = e.ImageFrame.ToBitmapSource();
        }

       public void Cleanup()
        {
            if (nui != null)
            {
                nui.Uninitialize();
            }
        }

        public event EventHandler<SkeletonEventArgs> SkeletonUpdated;
    }
}
