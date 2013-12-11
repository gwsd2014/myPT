using Coding4Fun.Kinect.Wpf.Controls;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Shapes;

namespace myPTv1._0
{
    class ButtonViewModel : ObservableObject
    {
        #region Fields
        private string _imageSource;
        private string _activeImageSource;
        private Ellipse _thumbStick;
        private HoverButton _button;
        private double _itemTop, _topBoundary, _bottomBoundary, _itemLeft, _leftBoundary, _rightBoundary;

        private ButtonModel _currentButton;

        //private ICommand _getButtonCommand;
        private ICommand _buttonClickedCommand;


        #endregion

        #region Properties/Commands

        public ButtonModel CurrentButton
        {
            get { return _currentButton; }
            set
            {
                if (value != _currentButton)
                {
                    _currentButton = value;
                    OnPropertyChanged("CurrentButton");
                }
            }
        }

        /*
        public ICommand GetButtonCommand
        {
            get
            {
                if (_getButtonCommand == null)
                {
                    _getButtonCommand = new RelayCommand(
                        param => GetButton(),
                        param => (_getButtonCommand != null)
                        );
                }
            }
        }
        */
        
        public ICommand ButtonClickedCommand
        {
            get
            {
                if (_buttonClickedCommand == null)
                {
                    _buttonClickedCommand = new RelayCommand(
                        param => CheckButton(_button, _thumbStick),
                        param => (CurrentButton != null)
                        );
                }
                return _buttonClickedCommand;
            }
        }

        public String ImageSource
        {
            get { return _imageSource; }
            set
            {
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


        #endregion //Properties/Commands

        #region Private Helpers

        //http://jellybean.codeplex.com/
        //taken from jellybean

        //taken from jellybean
        private void FindValues(FrameworkElement container, FrameworkElement target)
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

        public bool IsItemMidpointInContainer(FrameworkElement container, FrameworkElement target)
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

        private bool CheckButton(HoverButton button, Ellipse thumbStick)
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

        //Put this in another class?
        private void ButtonClicked(object sender, RoutedEventArgs e)
        {
            //Does something when the button has been clicked
            
        }

        private void ButtonReleased()
        {
            //Does something when the button is released
        }

        #endregion //Private Helpers
    }
}
