using Coding4Fun.Kinect.Wpf.Controls;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Shapes;

namespace myPTv1._0
{
    class ButtonModel : ObservableObject
    {

        #region Fields

        private String _imageSource;
        private String _activeImageSource;
        private int _timeInterval;
        private Ellipse _thumbStick;
        private HoverButton _button;

        //Used to be static
        //Used in FindValues
        private double _itemTop, _topBoundary, _bottomBoundary, _itemLeft, _leftBoundary, _rightBoundary;

        #endregion

        #region Properties

        public String ImageSource
        {
            get { return _imageSource; }
            set {
                if (!value.Equals(_imageSource, StringComparison.Ordinal))
                {
                    _imageSource = value;
                    OnPropertyChanged("ImageSource");
                }
            }
        }


        public String ActiveImageSource
        {
            get { return _activeImageSource; }
            set
            {
                if (!value.Equals(_activeImageSource, StringComparison.Ordinal))
                {
                    _imageSource = value;
                    OnPropertyChanged("ActiveImageSource");
                }
            }
        }

        private double ItemTop
        {
            get { return _itemTop; }
            set
            {
                if (value != _itemTop)
                {
                    _itemTop = value;
                    OnPropertyChanged("ItemTop");
                }
            }
        }

        private double TopBoundary
        {
            get { return _topBoundary; }
            set
            {
                if (value != _topBoundary)
                {
                    _topBoundary = value;
                    OnPropertyChanged("TopBoundary");
                }
            }
        }

        private double BottomBoundary
        {
            get { return _bottomBoundary; }
            set
            {
                if (value != _bottomBoundary)
                {
                    _bottomBoundary = value;
                    OnPropertyChanged("BottomBoundary");
                }
            }
        }

        private double ItemLeft
        {
            get { return _itemLeft; }
            set
            {
                if (value != _itemLeft)
                {
                    _itemLeft = value;
                    OnPropertyChanged("ItemLeft");
                }
            }
        }

        private double LeftBoundary
        {
            get { return _leftBoundary; }
            set
            {
                if (value != _leftBoundary)
                {
                    _leftBoundary = value;
                    OnPropertyChanged("LeftBoundary");
                }
            }
        }

        private double RightBoundary
        {
            get { return _rightBoundary; }
            set
            {
                if (value != _rightBoundary)
                {
                    _rightBoundary = value;
                    OnPropertyChanged("RightBoundary");
                }
            }
        }

        private Ellipse ThumbStick
        {
            get { return _thumbStick; }
            set
            {
                if (value != _thumbStick)
                {
                    _thumbStick = value;
                    OnPropertyChanged("ThumbStick");
                }
            }
        }

        private HoverButton Button
        {
            get { return _button; }
            set
            {
                if (value != _button)
                {
                    _button = value;
                    OnPropertyChanged("Button");
                }
            }
        }

        #endregion //Properties
    }
}
