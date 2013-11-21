using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace myPTv1._0
{
    class FlexionExtensionViewModel : ObservableObject, IPageViewModel
    {

        #region Fields
        private int _flexion;
        private int _extension;
        private FlexionExtensionModel _currentFlexionExtension;

        private ICommand _saveFlexionCommand;
        private ICommand _saveExtensionCommand;
        #endregion //Fields

        #region Public Properties/Commands

        public string Name
        {
            get { return "Test Flexion/Extension"; }
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

        #endregion  //Properties

        #region Private Helpers
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
        #endregion
    }
}
