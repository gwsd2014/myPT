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
        private int _currentAngle;
        private String _angleText;

        private int canvasWidth;
        private int canvasHeight;
        public Microsoft.Research.Kinect.Nui.Vector[] joints;
        public Microsoft.Research.Kinect.Nui.Vector[] bones;
     
        private ICommand _saveFlexionCommand;
        private ICommand _saveExtensionCommand;
        /*
        private ICommand _getAngleTextCommand;
        private ICommand _saveAngleTextCommand;
         */
        
        #endregion //Fields

        #region Public Properties/Commands

        public FlexionExtensionViewModel()
        {
            _flexion = 0;
            _extension = 0;
            joints = new Microsoft.Research.Kinect.Nui.Vector[20];
            bones = new Microsoft.Research.Kinect.Nui.Vector[19];
            canvasWidth = 640;
            canvasHeight = 480;
            _angleText = "Reading Unavailable";

            //this.canvas = canvas1;

            this.kinectRuntime = new KinectRuntime();
            this.kinectRuntime.Initialize();
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
                joints[i] = SetEllipsePosition(e.Joints[i]);
            }
          

            //Draws bones (series of connecting lines)
            int j = 0;
            for (int i = 0; i < 19; i++)
            {
                if (i != 3 && i != 7 && i != 11 && i != 15)
                {
                    if (j > 18)
                        Console.WriteLine("J is " + j);
                    else{
                        bones[j] = SetLinePosition(e.Joints[i], e.Joints[i + 1]);
                        j++;
                    }
                }
            }

            bones[15] = SetLinePosition(e.Joints[2], e.Joints[4]);
            bones[16] = SetLinePosition(e.Joints[2], e.Joints[8]);
            bones[17] = SetLinePosition(e.Joints[0], e.Joints[12]);
            bones[18] = SetLinePosition(e.Joints[0], e.Joints[16]);

            UpdateShapes();

            ShowAngle(e.Joints[(int) MyJointID.HipRight], e.Joints[(int) MyJointID.KneeRight], e.Joints[(int)MyJointID.AnkleRight]);
        }

        public ICommand SaveFlexionCommand
        {
            get
            {
                if (_saveFlexionCommand == null)
                {
                    _saveFlexionCommand = new RelayCommand(
                        param => SaveFlexion(),
                        param => (Flexion != null)
                        );
                }
                return _saveFlexionCommand;
            }
        }

        private void SaveFlexion()
        {
            Flexion = CurrentAngle;
            Console.WriteLine("Flexion saved as " + Flexion);
            //Now save TO DB
        }

        public ICommand SaveExtensionCommand
        {
            get
            {
                if (_saveExtensionCommand == null)
                {
                    _saveExtensionCommand = new RelayCommand(
                        param => SaveExtension(),
                        param => (Extension != null)
                       );
                }
                return _saveExtensionCommand;
            }
        }

        private void SaveExtension()
        {
            Extension = CurrentAngle;
            Console.WriteLine("Extension saved as" + Extension);
            //Save to DB
        }

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

        public int CurrentAngle {
            get { return _currentAngle; }
            set
            {
                if (value != _currentAngle)
                {
                    _currentAngle = value;
                    AngleText = value.ToString();
                    OnPropertyChanged("CurrentAngle");
                }
            }
       }

        public String AngleText
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

        #region Skeleton Bindings

        public Microsoft.Research.Kinect.Nui.Vector[] Joints
        {
            get { return joints; }
            set
            {
                if (value != null)
                {
                    joints = value;
                    OnPropertyChanged("Joints");
                }
            }
        }

        public float X0
        {
            get { return joints[0].X; }
            set
            {
                joints[0].X = value;
                OnPropertyChanged("X0");
            }
        }
        public float X1
        {
            get { return joints[1].X; }
            set
            {
                joints[1].X = value;
                OnPropertyChanged("X1");
            }
        }
        public float X2
        {
            get { return joints[2].X; }
            set
            {
                joints[2].X = value;
                OnPropertyChanged("X2");
            }
        }
        public float X3
        {
            get { return joints[3].X; }
            set
            {
                joints[3].X = value;
                OnPropertyChanged("X3");
            }
        }
        public float X4
        {
            get { return joints[4].X; }
            set
            {
                joints[4].X = value;
                OnPropertyChanged("X4");
            }
        }
        public float X5
        {
            get { return joints[5].X; }
            set
            {
                joints[5].X = value;
                OnPropertyChanged("X5");
            }
        }
        public float X6
        {
            get { return joints[6].X; }
            set
            {
                joints[6].X = value;
                OnPropertyChanged("X6");
            }
        }
        public float X7
        {
            get { return joints[7].X; }
            set
            {
                joints[7].X = value;
                OnPropertyChanged("X7");
            }
        }
        public float X8
        {
            get { return joints[8].X; }
            set
            {
                joints[8].X = value;
                OnPropertyChanged("X8");
            }
        }
        public float X9
        {
            get { return joints[9].X; }
            set
            {
                joints[9].X = value;
                OnPropertyChanged("X9");
            }
        }
        public float X10
        {
            get { return joints[10].X; }
            set
            {
                joints[10].X = value;
                OnPropertyChanged("X10");
            }
        }
        public float X11
        {
            get { return joints[11].X; }
            set
            {
                joints[11].X = value;
                OnPropertyChanged("X11");
            }
        }
        public float X12
        {
            get { return joints[12].X; }
            set
            {
                joints[12].X = value;
                OnPropertyChanged("X12");
            }
        }
        public float X13
        {
            get { return joints[13].X; }
            set
            {
                joints[13].X = value;
                OnPropertyChanged("X13");
            }
        }
        public float X14
        {
            get { return joints[14].X; }
            set
            {
                joints[14].X = value;
                OnPropertyChanged("X14");
            }
        }
        public float X15
        {
            get { return joints[15].X; }
            set
            {
                joints[15].X = value;
                OnPropertyChanged("X15");
            }
        }
        public float X16
        {
            get { return joints[16].X; }
            set
            {
                joints[16].X = value;
                OnPropertyChanged("X16");
            }
        }
        public float X17
        {
            get { return joints[17].X; }
            set
            {
                joints[17].X = value;
                OnPropertyChanged("X17");
            }
        }
        public float X18
        {
            get { return joints[18].X; }
            set
            {
                joints[18].X = value;
                OnPropertyChanged("X18");
            }
        }
        public float X19
        {
            get { return joints[19].X; }
            set
            {
                joints[19].X = value;
                OnPropertyChanged("X19");
            }
        }
        //------------------------------------------------------------------------//
        public float Y0
        {
            get { return joints[0].Y; }
            set
            {
                joints[0].Y = value;
                OnPropertyChanged("Y0");
            }
        }
        public float Y1
        {
            get { return joints[1].Y; }
            set
            {
                joints[1].Y = value;
                OnPropertyChanged("Y1");
            }
        }
        public float Y2
        {
            get { return joints[2].Y; }
            set
            {
                joints[2].Y = value;
                OnPropertyChanged("Y2");
            }
        }
        public float Y3
        {
            get { return joints[3].Y; }
            set
            {
                joints[3].Y = value;
                OnPropertyChanged("Y3");
            }
        }
        public float Y4
        {
            get { return joints[4].Y; }
            set
            {
                joints[4].Y = value;
                OnPropertyChanged("Y4");
            }
        }
        public float Y5
        {
            get { return joints[5].Y; }
            set
            {
                joints[5].Y = value;
                OnPropertyChanged("Y5");
            }
        }
        public float Y6
        {
            get { return joints[6].Y; }
            set
            {
                joints[6].Y = value;
                OnPropertyChanged("Y6");
            }
        }
        public float Y7
        {
            get { return joints[7].Y; }
            set
            {
                joints[7].Y = value;
                OnPropertyChanged("Y7");
            }
        }
        public float Y8
        {
            get { return joints[8].Y; }
            set
            {
                joints[8].Y = value;
                OnPropertyChanged("Y8");
            }
        }
        public float Y9
        {
            get { return joints[9].Y; }
            set
            {
                joints[9].Y = value;
                OnPropertyChanged("Y9");
            }
        }
        public float Y10
        {
            get { return joints[10].Y; }
            set
            {
                joints[10].Y = value;
                OnPropertyChanged("Y10");
            }
        }
        public float Y11
        {
            get { return joints[11].Y; }
            set
            {
                joints[11].Y = value;
                OnPropertyChanged("Y11");
            }
        }
        public float Y12
        {
            get { return joints[12].Y; }
            set
            {
                joints[12].Y = value;
                OnPropertyChanged("Y12");
            }
        }
        public float Y13
        {
            get { return joints[13].Y; }
            set
            {
                joints[13].Y = value;
                OnPropertyChanged("Y13");
            }
        }
        public float Y14
        {
            get { return joints[14].Y; }
            set
            {
                joints[14].Y = value;
                OnPropertyChanged("Y14");
            }
        }
        public float Y15
        {
            get { return joints[15].Y; }
            set
            {
                joints[15].Y = value;
                OnPropertyChanged("Y15");
            }
        }
        public float Y16
        {
            get { return joints[16].Y; }
            set
            {
                joints[16].Y = value;
                OnPropertyChanged("Y16");
            }
        }
        public float Y17
        {
            get { return joints[17].Y; }
            set
            {
                joints[17].Y = value;
                OnPropertyChanged("Y17");
            }
        }
        public float Y18
        {
            get { return joints[18].Y; }
            set
            {
                joints[18].Y = value;
                OnPropertyChanged("Y18");
            }
        }
        public float Y19
        {
            get { return joints[19].Y; }
            set
            {
                joints[19].Y = value;
                OnPropertyChanged("Y19");
            }
        }
        
        //----------------------------------------------------------------------------------------//
        //----------------------------bones------------------------------------------------------//
        public float Xa
        {
            get { return bones[0].X; }
            set
            {
                bones[0].X = value;
                OnPropertyChanged("Xa");
            }
        }
        public float Xb
        {
            get { return bones[1].X; }
            set
            {
                bones[1].X = value;
                OnPropertyChanged("Xb");
            }
        }
        public float Xc
        {
            get { return bones[2].X; }
            set
            {
                bones[2].X = value;
                OnPropertyChanged("Xc");
            }
        }
        public float Xd
        {
            get { return bones[3].X; }
            set
            {
                bones[3].X = value;
                OnPropertyChanged("Xd");
            }
        }
        public float Xe
        {
            get { return bones[4].X; }
            set
            {
                bones[4].X = value;
                OnPropertyChanged("Xe");
            }
        }
        public float Xf
        {
            get { return bones[5].X; }
            set
            {
                bones[5].X = value;
                OnPropertyChanged("Xf");
            }
        }
        public float Xg
        {
            get { return bones[6].X; }
            set
            {
                bones[6].X = value;
                OnPropertyChanged("Xg");
            }
        }
        public float Xh
        {
            get { return bones[7].X; }
            set
            {
                bones[7].X = value;
                OnPropertyChanged("Xh");
            }
        }
        public float Xi
        {
            get { return bones[8].X; }
            set
            {
                bones[8].X = value;
                OnPropertyChanged("Xi");
            }
        }
        public float Xj
        {
            get { return bones[9].X; }
            set
            {
                bones[9].X = value;
                OnPropertyChanged("Xj");
            }
        }
        public float Xk
        {
            get { return bones[10].X; }
            set
            {
                bones[10].X = value;
                OnPropertyChanged("Xk");
            }
        }
        public float Xl
        {
            get { return bones[11].X; }
            set
            {
                bones[11].X = value;
                OnPropertyChanged("Xl");
            }
        }
        public float Xm
        {
            get { return bones[12].X; }
            set
            {
                bones[12].X = value;
                OnPropertyChanged("Xm");
            }
        }
        public float Xn
        {
            get { return bones[13].X; }
            set
            {
                bones[13].X = value;
                OnPropertyChanged("Xn");
            }
        }
        public float Xo
        {
            get { return bones[14].X; }
            set
            {
                bones[14].X = value;
                OnPropertyChanged("Xo");
            }
        }
        public float Xp
        {
            get { return bones[15].X; }
            set
            {
                bones[15].X = value;
                OnPropertyChanged("Xp");
            }
        }
        public float Xq
        {
            get { return bones[16].X; }
            set
            {
                bones[16].X = value;
                OnPropertyChanged("Xs");
            }
        }
        public float Xr
        {
            get { return bones[17].X; }
            set
            {
                bones[17].X = value;
                OnPropertyChanged("Xr");
            }
        }
        public float Xs
        {
            get { return bones[18].X; }
            set
            {
                bones[18].X = value;
                OnPropertyChanged("Xs");
            }
        }
        //----------------------------------------------------------------------------------------//
        public float Ya
        {
            get { return bones[0].Y; }
            set
            {
                bones[0].Y = value;
                OnPropertyChanged("Ya");
            }
        }
        public float Yb
        {
            get { return bones[1].Y; }
            set
            {
                bones[1].Y = value;
                OnPropertyChanged("Yb");
            }
        }
        public float Yc
        {
            get { return bones[2].Y; }
            set
            {
                bones[2].Y = value;
                OnPropertyChanged("Yc");
            }
        }
        public float Yd
        {
            get { return bones[3].Y; }
            set
            {
                bones[3].Y = value;
                OnPropertyChanged("Yd");
            }
        }
        public float Ye
        {
            get { return bones[4].Y; }
            set
            {
                bones[4].Y = value;
                OnPropertyChanged("Ye");
            }
        }
        public float Yf
        {
            get { return bones[5].Y; }
            set
            {
                bones[5].Y = value;
                OnPropertyChanged("Yf");
            }
        }
        public float Yg
        {
            get { return bones[6].Y; }
            set
            {
                bones[6].Y = value;
                OnPropertyChanged("Yg");
            }
        }
        public float Yh
        {
            get { return bones[7].Y; }
            set
            {
                bones[7].Y = value;
                OnPropertyChanged("Yh");
            }
        }
        public float Yi
        {
            get { return bones[8].Y; }
            set
            {
                bones[8].Y = value;
                OnPropertyChanged("Yi");
            }
        }
        public float Yj
        {
            get { return bones[9].Y; }
            set
            {
                bones[9].Y = value;
                OnPropertyChanged("Yj");
            }
        }
        public float Yk
        {
            get { return bones[10].Y; }
            set
            {
                bones[10].Y = value;
                OnPropertyChanged("Yk");
            }
        }
        public float Yl
        {
            get { return bones[11].Y; }
            set
            {
                bones[11].Y = value;
                OnPropertyChanged("Yl");
            }
        }
        public float Ym
        {
            get { return bones[12].Y; }
            set
            {
                bones[12].Y = value;
                OnPropertyChanged("Ym");
            }
        }
        public float Yn
        {
            get { return bones[13].Y; }
            set
            {
                bones[13].Y = value;
                OnPropertyChanged("Yn");
            }
        }
        public float Yo
        {
            get { return bones[14].Y; }
            set
            {
                bones[14].Y = value;
                OnPropertyChanged("Yo");
            }
        }
        public float Yp
        {
            get { return bones[15].Y; }
            set
            {
                bones[15].Y = value;
                OnPropertyChanged("Yp");
            }
        }
        public float Yq
        {
            get { return bones[16].Y; }
            set
            {
                bones[16].Y = value;
                OnPropertyChanged("Ys");
            }
        }
        public float Yr
        {
            get { return bones[17].Y; }
            set
            {
                bones[17].Y = value;
                OnPropertyChanged("Yr");
            }
        }
        public float Ys
        {
            get { return bones[18].Y; }
            set
            {
                bones[18].Y = value;
                OnPropertyChanged("Ys");
            }
        }

        //-------------------------------------------------------------------------//
        public float Za
        {
            get { return bones[0].Z; }
            set
            {
                bones[0].Z = value;
                OnPropertyChanged("Za");
            }
        }
        public float Zb
        {
            get { return bones[1].Z; }
            set
            {
                bones[1].Z = value;
                OnPropertyChanged("Zb");
            }
        }
        public float Zc
        {
            get { return bones[2].Z; }
            set
            {
                bones[2].Z = value;
                OnPropertyChanged("Zc");
            }
        }
        public float Zd
        {
            get { return bones[3].Z; }
            set
            {
                bones[3].Z = value;
                OnPropertyChanged("Zd");
            }
        }
        public float Ze
        {
            get { return bones[4].Z; }
            set
            {
                bones[4].Z = value;
                OnPropertyChanged("Ze");
            }
        }
        public float Zf
        {
            get { return bones[5].Z; }
            set
            {
                bones[5].Z = value;
                OnPropertyChanged("Zf");
            }
        }
        public float Zg
        {
            get { return bones[6].Z; }
            set
            {
                bones[6].Z = value;
                OnPropertyChanged("Zg");
            }
        }
        public float Zh
        {
            get { return bones[7].Z; }
            set
            {
                bones[7].Z = value;
                OnPropertyChanged("Zh");
            }
        }
        public float Zi
        {
            get { return bones[8].Z; }
            set
            {
                bones[8].Z = value;
                OnPropertyChanged("Zi");
            }
        }
        public float Zj
        {
            get { return bones[9].Z; }
            set
            {
                bones[9].Z = value;
                OnPropertyChanged("Zj");
            }
        }
        public float Zk
        {
            get { return bones[10].Z; }
            set
            {
                bones[10].Z = value;
                OnPropertyChanged("Zk");
            }
        }
        public float Zl
        {
            get { return bones[11].Z; }
            set
            {
                bones[11].Z = value;
                OnPropertyChanged("Zl");
            }
        }
        public float Zm
        {
            get { return bones[12].Z; }
            set
            {
                bones[12].Z = value;
                OnPropertyChanged("Zm");
            }
        }
        public float Zn
        {
            get { return bones[13].Z; }
            set
            {
                bones[13].Z = value;
                OnPropertyChanged("Zn");
            }
        }
        public float Zo
        {
            get { return bones[14].Z; }
            set
            {
                bones[14].Z = value;
                OnPropertyChanged("Zo");
            }
        }
        public float Zp
        {
            get { return bones[15].Z; }
            set
            {
                bones[15].Z = value;
                OnPropertyChanged("Zp");
            }
        }
        public float Zq
        {
            get { return bones[16].Z; }
            set
            {
                bones[16].Z = value;
                OnPropertyChanged("Zs");
            }
        }
        public float Zr
        {
            get { return bones[17].Z; }
            set
            {
                bones[17].Z = value;
                OnPropertyChanged("Zr");
            }
        }
        public float Zs
        {
            get { return bones[18].Z; }
            set
            {
                bones[18].Z = value;
                OnPropertyChanged("Zs");
            }
        }

        //-------------------------------------------------------------------------//
        public float Wa
        {
            get { return bones[0].W; }
            set
            {
                bones[0].W = value;
                OnPropertyChanged("Wa");
            }
        }
        public float Wb
        {
            get { return bones[1].W; }
            set
            {
                bones[1].W = value;
                OnPropertyChanged("Wb");
            }
        }
        public float Wc
        {
            get { return bones[2].W; }
            set
            {
                bones[2].W = value;
                OnPropertyChanged("Wc");
            }
        }
        public float Wd
        {
            get { return bones[3].W; }
            set
            {
                bones[3].W = value;
                OnPropertyChanged("Wd");
            }
        }
        public float We
        {
            get { return bones[4].W; }
            set
            {
                bones[4].W = value;
                OnPropertyChanged("We");
            }
        }
        public float Wf
        {
            get { return bones[5].W; }
            set
            {
                bones[5].W = value;
                OnPropertyChanged("Wf");
            }
        }
        public float Wg
        {
            get { return bones[6].W; }
            set
            {
                bones[6].W = value;
                OnPropertyChanged("Wg");
            }
        }
        public float Wh
        {
            get { return bones[7].W; }
            set
            {
                bones[7].W = value;
                OnPropertyChanged("Wh");
            }
        }
        public float Wi
        {
            get { return bones[8].W; }
            set
            {
                bones[8].W = value;
                OnPropertyChanged("Wi");
            }
        }
        public float Wj
        {
            get { return bones[9].W; }
            set
            {
                bones[9].W = value;
                OnPropertyChanged("Wj");
            }
        }
        public float Wk
        {
            get { return bones[10].W; }
            set
            {
                bones[10].W = value;
                OnPropertyChanged("Wk");
            }
        }
        public float Wl
        {
            get { return bones[11].W; }
            set
            {
                bones[11].W = value;
                OnPropertyChanged("Wl");
            }
        }
        public float Wm
        {
            get { return bones[12].W; }
            set
            {
                bones[12].W = value;
                OnPropertyChanged("Wm");
            }
        }
        public float Wn
        {
            get { return bones[13].W; }
            set
            {
                bones[13].W = value;
                OnPropertyChanged("Wn");
            }
        }
        public float Wo
        {
            get { return bones[14].W; }
            set
            {
                bones[14].W = value;
                OnPropertyChanged("Wo");
            }
        }
        public float Wp
        {
            get { return bones[15].W; }
            set
            {
                bones[15].W = value;
                OnPropertyChanged("Wp");
            }
        }
        public float Wq
        {
            get { return bones[16].W; }
            set
            {
                bones[16].W = value;
                OnPropertyChanged("Ws");
            }
        }
        public float Wr
        {
            get { return bones[17].W; }
            set
            {
                bones[17].W = value;
                OnPropertyChanged("Wr");
            }
        }
        public float Ws
        {
            get { return bones[18].W; }
            set
            {
                bones[18].W = value;
                OnPropertyChanged("Ws");
            }
        }

        //-------------------------------------------------------------------------//

        #endregion

        #endregion  //Properties

        #region Private Helpers

        private void UpdateShapes()
        {
            //Joints
            X0 = joints[0].X; Y0 = joints[0].Y;
            X1 = joints[1].X; Y1 = joints[1].Y;
            X2 = joints[2].X; Y2 = joints[2].Y;
            X3 = joints[3].X; Y3 = joints[3].Y;
            X4 = joints[4].X; Y4 = joints[4].Y;
            X5 = joints[5].X; Y5 = joints[5].Y;
            X6 = joints[6].X; Y6 = joints[6].Y;
            X7 = joints[7].X; Y7 = joints[7].Y;
            X8 = joints[8].X; Y8 = joints[8].Y;
            X9 = joints[9].X; Y9 = joints[9].Y;
            X10 = joints[10].X; Y10 = joints[10].Y;
            X11 = joints[11].X; Y11 = joints[11].Y;
            X12 = joints[12].X; Y12 = joints[12].Y;
            X13 = joints[13].X; Y13 = joints[13].Y;
            X14 = joints[14].X; Y14 = joints[14].Y;
            X15 = joints[15].X; Y15 = joints[15].Y;
            X16 = joints[16].X; Y16 = joints[16].Y;
            X17 = joints[17].X; Y17 = joints[17].Y;
            X18 = joints[18].X; Y18 = joints[18].Y;
            X19 = joints[19].X; Y19 = joints[19].Y;

            //Bones
            Xa = bones[0].X; Ya = bones[0].Y; Za = bones[0].Z; Wa = bones[0].W;
            Xb = bones[1].X; Yb = bones[1].Y; Zb = bones[1].Z; Wb = bones[1].W;
            Xc = bones[2].X; Yc = bones[2].Y; Zc = bones[2].Z; Wc = bones[2].W;
            Xd = bones[3].X; Yd = bones[3].Y; Zd = bones[3].Z; Wd = bones[3].W;
            Xe = bones[4].X; Ye = bones[4].Y; Ze = bones[4].Z; We = bones[4].W;
            Xf = bones[5].X; Yf = bones[5].Y; Zf = bones[5].Z; Wf = bones[5].W;
            Xg = bones[6].X; Yg = bones[6].Y; Zg = bones[6].Z; Wg = bones[6].W;
            Xh = bones[7].X; Yh = bones[7].Y; Zh = bones[7].Z; Wh = bones[7].W;
            Xi = bones[8].X; Yi = bones[8].Y; Zi = bones[8].Z; Wi = bones[8].W;
            Xj = bones[9].X; Yj = bones[9].Y; Zj = bones[9].Z; Wj = bones[9].W;
            Xk = bones[10].X; Yk = bones[10].Y; Zk = bones[10].Z; Wk = bones[10].W;
            Xl = bones[11].X; Yl = bones[11].Y; Zl = bones[11].Z; Wl = bones[11].W;
            Xm = bones[12].X; Ym = bones[12].Y; Zm = bones[12].Z; Wm = bones[12].W;
            Xn = bones[13].X; Yn = bones[13].Y; Zn = bones[13].Z; Wn = bones[13].W;
            Xo = bones[14].X; Yo = bones[14].Y; Zo = bones[14].Z; Wo = bones[14].W;
            Xo = bones[1].X; Yp = bones[15].Y; Zp = bones[15].Z; Wp = bones[15].W;
            Xq = bones[16].X; Yq = bones[16].Y; Zq = bones[16].Z; Wq = bones[16].W;
            Xr = bones[17].X; Yr = bones[17].Y; Zr = bones[17].Z; Wr = bones[17].W;
            Xs = bones[18].X; Ys = bones[18].Y; Zs = bones[18].Z; Ws = bones[18].W;


        }

        int scale = 400;
        private Microsoft.Research.Kinect.Nui.Vector SetEllipsePosition(Joint joint)
        {

            var midPointX = 640/2;
            var midPointY = 480/2;
            var scaledJoint = joint.ScaleTo(canvasWidth, canvasHeight);
            Microsoft.Research.Kinect.Nui.Vector circle = scaledJoint.Position;
            //circle.X = midPointX + scaledJoint.Position.X;
            //circle.Y = midPointY - scaledJoint.Position.X;
            circle.X = midPointX + (joint.Position.X * scale);
            circle.Y = midPointY - (joint.Position.Y * scale);
            return circle;
        }

        public Microsoft.Research.Kinect.Nui.Vector SetLinePosition(Joint joint1, Joint joint2)
        {
            var midPointX = 640 / 2;
            var midPointY = 480 / 2;
            var scaledJoint1 = joint1.ScaleTo(canvasWidth, canvasHeight);
            var scaledJoint2 = joint2.ScaleTo(canvasWidth, canvasHeight);
            Microsoft.Research.Kinect.Nui.Vector line = scaledJoint2.Position;
            //line.X = scaledJoint1.Position.X;
            //line.Y = scaledJoint2.Position.X;
            //line.Z = scaledJoint1.Position.Y;
            //line.W = scaledJoint2.Position.Y;

            line.X = midPointX + (joint1.Position.X * scale);
            line.Y = midPointX + (joint2.Position.X * scale);
            line.Z = midPointY - (joint1.Position.Y * scale);
            line.W = midPointY - (joint2.Position.Y * scale);
            return line;
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
           //_angleText.Content = ((int)angle).ToString();
           //_angleText.FontSize = 30;
            CurrentAngle = (int)angle;
            //AngleText.Canvas.Left = beta.Position.X+10;
            //AngleText.Canvas.Top = beta.Position.Y;
        }


        public void Cleanup()
        {
            kinectRuntime.Cleanup();
            this.kinectRuntime.SkeletonUpdated -= kinectRuntime_SkeletonUpdated;
        }
        #endregion
    }
}
