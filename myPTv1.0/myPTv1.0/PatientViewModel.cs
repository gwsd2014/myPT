using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace myPTv1._0
{
    class PatientViewModel : ObservableObject
    {
        #region Fields
        private string _userName;
        private DateTime _dateOfLastSession;
        private PatientModel _currentPatient;
        private ICommand _getPatientCommand;
        private ICommand _savePatientCommand;

        #endregion //Fields

        #region Public Properties/Commands

        public PatientModel CurrentPatient
        {
            get { return _currentPatient; }
            set
            {
                if (value != _currentPatient)
                {
                    _currentPatient = value;
                    OnPropertyChanged("CurrentPatient");
                }
            }
        }

        public ICommand SavePatientCommand
        {
            get
            {
                if (_savePatientCommand == null)
                {
                    _savePatientCommand = new RelayCommand(
                        param => SavePatient(), 
                        param => (CurrentPatient != null)
                    );
                }
                return _savePatientCommand;
            }
        }

        public ICommand GetProductCommand
        {
            get
            {
                if (_getPatientCommand == null)
                {
                    _getPatientCommand = new RelayCommand(
                       param => GetPatient(),
                       param => UserName != null
                    );
                }
                return _getPatientCommand;
            }
        }
        
        public string UserName
        {
            get { return _userName; }
            set
            {
                if(!value.Equals(_userName, StringComparison.Ordinal)){
                    _userName = value;
                    OnPropertyChanged("UserName");
                }
            }

        }

        #endregion //Properties

        #region Private Helpers

        private void GetPatient()
        {
            //Get patient from database
            //For now return new user
            PatientModel p = new PatientModel();
            p.UserName = UserName;
            p.DateOfLastSession = DateTime.Now;
            CurrentPatient = p;
        }

        private void SavePatient()
        {
            //Save to Database here!
            Console.WriteLine("In Save Patient");
        }
        #endregion 

    }
}
