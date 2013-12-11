using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Shapes;

namespace myPTv1._0
{
    class FlexionExtensionModel : ObservableObject
    {
        #region Fields

        private int _flexion;
        private int _extension;
        private Label _angleText;
        private KinectRuntime _kinect;
        private ButtonModel _button;

        #endregion 

        #region Properties

        public int Flexion
        {
            get { return _flexion; }
            set
            {
                if (_flexion != value)
                {
                    _flexion = value;
                    //Save it to Current Patient
                    OnPropertyChanged("Flexion");
                }
            }
        }

        public int Extension
        {
            get { return _extension; }
            set
            {
                if (_extension != value)
                {
                    _extension = value;
                    //Update Current Patient
                    OnPropertyChanged("Extension");
                }
            }
        }

        public Label AngleText
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

        public KinectRuntime Kinect
        {
            get { return _kinect; }
            set
            {
                if (_kinect != null)
                {
                    _kinect = value;
                    OnPropertyChanged("Kinect");
                }
            }
        }

        private ButtonModel Button
        {
            get { return _button; }
            set
            {
                if (_button != null)
                {
                    _button = value;
                    OnPropertyChanged("Button");
                }
            }
        }


        #endregion  //Properties
    }
}
