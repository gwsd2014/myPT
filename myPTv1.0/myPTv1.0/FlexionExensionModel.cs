using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace myPTv1._0
{
    class FlexionExensionModel : ObservableObject
    {
        #region Fields

        private int _flexion;
        private int _extension;

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

        #endregion  //Properties
    }
}
