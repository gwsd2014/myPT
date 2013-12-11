using Microsoft.Research.Kinect.Nui;
using Coding4Fun.Kinect.Wpf;
using Coding4Fun.Kinect.Wpf.Controls;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Shapes;

namespace myPTv1._0
{
    public class FlexionExtensionViewModel : ObservableObject, IPageViewModel
    {

        IkinectService kinectRuntime;
        #region Fields
        private int _flexion;
        private int _extension;
        private System.Windows.Forms.Label _angleText;

        public Canvas canvas;
        public Image videoFrame;
        public int canvasWidth;
        public int canvasHeight;
        public Ellipse[] joints;
        public Line[] bones;

        private FlexionExtensionModel _currentFlexionExtension;

        private ICommand _getFlexionExtensionCommand;
        private ICommand _saveFlexionExtensionCommand;
        private ICommand _openFlexionExtensionCommand;

        
        private ICommand _saveFlexionCommand;
        private ICommand _saveExtensionCommand;
        /*
        private ICommand _getAngleTextCommand;
        private ICommand _saveAngleTextCommand;
         */
        
        #endregion //Fields

        #region Public Properties/Commands

        public FlexionExtensionViewModel(IkinectService kinectRuntime)
        {
            _flexion = 0;
            _extension = 0;
            this.kinectRuntime = kinectRuntime;
            this.kinectRuntime.SkeletonUpdated += new System.EventHandler<SkeletonEventArgs>(kinectRuntime_SkeletonUpdated);
        }

        public string Name
        {
            get { return "Test Flexion/Extension"; }
        }

        void kinectRuntime_SkeletonUpdated(object sender, SkeletonEventArgs e)
        {
            //SHOULD check that there is a window...
            //Draws Joints (20 ellipses)
            for (int i = 0; i < 20; i++)
            {
                SetEllipsePosition(joints[i], e.Joints[i]);
            }

            //Draws bones (series of connecting lines)
            int j = 0;
            for (int i = 0; i < 19; i++)
            {
                if (i != 3 || i != 7 || i != 11 || i != 15)
                {
                    j++;
                    SetLinePosition(bones[j], e.Joints[i], e.Joints[i + 1]);
                }
            }

            ShowAngle(e.Joints[(int) MyJointID.HipRight], e.Joints[(int) MyJointID.KneeRight], e.Joints[(int)MyJointID.AnkleRight]);
        }

        public FlexionExtensionModel CurrentFlexionExtension
        {
            get { return _currentFlexionExtension; }

            set
            {
                if (value != _currentFlexionExtension) 
                {
                    _currentFlexionExtension = value;
                    OnPropertyChanged("FlexionExensionModel");
                }
            }
        }

        public ICommand SaveFlexionExtensionCommand
        {
            get
            {
                if (_saveFlexionExtensionCommand == null)
                {
                    _saveFlexionExtensionCommand = new RelayCommand(
                        param => SaveFlexionExtension(),
                        param => (CurrentFlexionExtension != null)
                    );
                }
                return _saveFlexionExtensionCommand;
            }
        }

        public ICommand GetFlexionExtensionCommand
        {
            get
            {
                if (_getFlexionExtensionCommand == null)
                {
                    _getFlexionExtensionCommand = new RelayCommand(
                       param => GetFlexionExtension(),
                       param => (CurrentFlexionExtension != null)
                    );
                }
                return _getFlexionExtensionCommand;
            }
        }

        public ICommand OpenFlexionExtensionCommand
        {
            get
            {
                if (_openFlexionExtensionCommand == null)
                {
                    _openFlexionExtensionCommand = new RelayCommand(
                        param => OpenFlexionExtension(),
                        param => (CurrentFlexionExtension != null)
                    );
                }
                return _openFlexionExtensionCommand;
            }
        }

        public ICommand SaveFlexionCommand
        {
            get 
            {
                if (_saveFlexionCommand == null)
                {
                    _saveFlexionCommand = new RelayCommand(
                        param => SaveFlexion(),
                        param => (CurrentFlexionExtension != null));
                }
                return _saveFlexionCommand;
            }
        }

        public ICommand SaveExtensionCommand 
        {
            get 
            {
                if (_saveExtensionCommand == null)
                {
                    _saveExtensionCommand = new RelayCommand(
                        param => SaveExtension(),
                        param => (CurrentFlexionExtension != null));
                }
                return _saveExtensionCommand;
            }
        }
        /*
        public ICommand GetAngleTextCommand
        {
            get
            {
                if (_getAngleTextCommand == null)
                {
                    _getAngleTextCommand = new RelayCommand(
                        param => GetAngleTextCommand(),
                        param => (CurrentFlexionExtension != null));
                }
                return GetAngleTextCommand;
            }
        }

        public ICommand SaveAngleTextCommand
        {
            get
            {
                if (_saveAngleTextCommand == null)
                {
                    _saveAngleTextCommand = new RelayCommand(
                        param => SaveAngleText(),
                        param => (CurrentFlexionExtension != null));
                }
                return SaveAngleTextCommand;
            }
        }
        */
        public int Flexion
        {
            get { return _flexion; }
            set {
                if (value != _flexion)
                {
                    _flexion = value;
                    OnPropertyChanged("Flexion");
                }
            }

        }

        public int Extension
        {
            get { return _extension; }
            set
            {
                if (value != _extension)
                {
                    _extension = value;
                    OnPropertyChanged("Extension");
                }
            }
        }

        public System.Windows.Forms.Label AngleText
        {
            get { return _angleText; }
            set
            {
                if (_angleText != null)
                {
                    _angleText = value;
                    OnPropertyChanged("AngleText");
                }
            }
        }


        #endregion  //Properties

        #region Private Helpers

        private void SaveFlexionExtension()
        {
            //Save?
        }

        private void GetFlexionExtension()
        {
            //Get?
        }

        private void OpenFlexionExtension()
        {
            //Kinect = new KinectRuntime(Canvas, CanvasWidth, CanvasHeight, Image);
        }

        private void SaveFlexion()
        {
            //Save to Database here!
            Console.WriteLine("In Save Flexion");

        }

        private void SaveExtension()
        {
            //Save to Database here!
            Console.WriteLine("In Save Extension");
        }

        private void SetEllipsePosition(FrameworkElement ellipse, Joint joint)
        {
            var scaledJoint = joint.ScaleTo(canvasWidth, canvasHeight);

            Canvas.SetLeft(ellipse, scaledJoint.Position.X);
            Canvas.SetTop(ellipse, scaledJoint.Position.Y);
        }

        public void SetLinePosition(Line line, Joint joint1, Joint joint2)
        {

            var scaledJoint1 = joint1.ScaleTo(canvasWidth, canvasHeight);
            var scaledJoint2 = joint2.ScaleTo(canvasWidth, canvasHeight);

            line.X1 = scaledJoint1.Position.X;
            line.X2 = scaledJoint2.Position.X;
            line.Y1 = scaledJoint1.Position.Y;
            line.Y2 = scaledJoint2.Position.Y;
        }

        public int ShowAngle(Joint alpha, Joint beta, Joint gamma)
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
           // _angleText.Content = ((int)angle).ToString();
            //_angleText.FontSize = 30;
            return (int)angle;
            //AngleText.Canvas.Left = beta.Position.X+10;
            //AngleText.Canvas.Top = beta.Position.Y;
        }
        #endregion

        public void Cleanup()
        {
            this.kinectRuntime.SkeletonUpdated -= kinectRuntime_SkeletonUpdated;
        }
    }
}
