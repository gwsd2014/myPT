using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace myPTv1._0
{
    class PatientViewModel : ObservableObject, IPageViewModel
    {
        #region Fields
        private string _userName;
        private DateTime _dateOfLastSession;
        private PatientModel _currentPatient;
        private ICommand _getPatientCommand;
        private ICommand _savePatientCommand;
        private ICommand _openPatientCommand;

        #endregion //Fields

        #region Public Properties/Commands

        public string Name
        {
            get { return "Patients"; }
        }

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

        public ICommand GetPatientCommand
        {
            get
            {
                if (_getPatientCommand == null)
                {
                    _getPatientCommand = new RelayCommand(
                       param => GetPatient(),
                       param => (UserName != null)
                    );
                }
                return _getPatientCommand;
            }
        }

        public ICommand OpenPatientCommand
        {
            get
            {
                if (_openPatientCommand == null)
                {
                    _openPatientCommand = new RelayCommand(
                        param => OpenPatient(),
                        param => (CurrentPatient != null)
                    );
                }
                return _openPatientCommand;
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

        public DateTime DateOfLastSession
        {
            get { return _dateOfLastSession; }
            set
            {
                if (!value.Equals(_dateOfLastSession))
                {
                    _dateOfLastSession = value;
                    OnPropertyChanged("DateOfLastSession");
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
            p.DateOfLastSession = DateTime.Now.AddHours(-12.00).ToString();
            Console.WriteLine("In GetPatient");
            Console.WriteLine(p.DateOfLastSession);
            CurrentPatient = p;
        }

        private void SavePatient()
        {
            //Save to Database here!
            Console.WriteLine("In Save Patient");
        }

        private void OpenPatient()
        {
            //if Date of last session > 12 hrs ago
            //open up that patient's homepage!

        }
        #endregion 

    }
}
