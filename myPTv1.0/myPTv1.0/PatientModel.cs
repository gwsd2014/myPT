using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace myPTv1._0
{
    class PatientModel : ObservableObject
    {
        #region Fields
        private string _userName;
        private DateTime _dateOfLastSession;

        #endregion

        #region Properites

        public string UserName
        {
            get { return _userName; }
            set
            {
                if (value.Equals(_userName, StringComparison.Ordinal))
                {
                    _userName = value;
                    //ALSO UPDATE DB!
                    OnPropertyChanged("UserName");
                }
            }
        }

        public DateTime DateOfLastSession
        {
            get { return _dateOfLastSession; }
            set
            {
                if (value.Equals(_dateOfLastSession))
                {
                    _dateOfLastSession = value;
                    OnPropertyChanged("DateOfLastSession");
                }
            }
        }

        #endregion  //Properties
    }
}
