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

        private String _userName;
        private DateTime _dateOfLastSession;

        #endregion

        #region Properites

        public String UserName
        {
            get { return _userName; }
            set
            {
                if (!value.Equals(_userName, StringComparison.Ordinal))
                {
                    _userName = value;
                    //ALSO UPDATE DB!
                    OnPropertyChanged("UserName");
                }
            }
        }

        public String DateOfLastSession
        {
            get {
                Console.Write("Getter of DateofLastSession: ");
                Console.WriteLine(_dateOfLastSession.ToString());    
                return _dateOfLastSession.ToString(); 
            }
            set
            {
                if (DateTime.Compare(DateTime.Parse(value), _dateOfLastSession) != 0)
                {
                    _dateOfLastSession = DateTime.Parse(value);
                    OnPropertyChanged("DateOfLastSession");
                }
            }
        }

        #endregion  //Properties
    }
}
