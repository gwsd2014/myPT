using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Diagnostics;

namespace myPTv1._0
{
    public abstract class ObservableObject : INotifyPropertyChanged
    {
        #region Debugging Aides
        //Warns the developer if object does not have 
        //public property with specified name
        [Conditional("DEBUG")]
        [DebuggerStepThrough]
        public virtual void VerifyPropertyName(string propertyName)
        {
            if (TypeDescriptor.GetProperties(this)[propertyName] == null)
            {
                string msg = "Invalid Property name: " + propertyName;
                if (this.ThrowOnInvalidPropertyName)
                {
                    throw new Exception(msg);
                }
                else
                {
                    Debug.Fail(msg);
                }
            }
        }

        /// Returns whether an exception is thrown, or if a Debug.Fail() is used
        /// when an invalid property name is passed to the VerifyPropertyName method.
        /// The default value is false, but subclasses used by unit tests might
        /// override this property's getter to return true.
        protected virtual bool ThrowOnInvalidPropertyName { get; private set; }

        #endregion //Debugging Aides

        #region INotifyPropertyChanged Members
        //Rasised when a property of the object has been changed
        public event PropertyChangedEventHandler PropertyChanged;

        //Saises this objects PropertyChanged event
        protected virtual void OnPropertyChanged(string propertyName)
        {
            this.VerifyPropertyName(propertyName);

            PropertyChangedEventHandler handler = this.PropertyChanged;
            if (handler != null)
            {
                var e = new PropertyChangedEventArgs(propertyName);
                handler(this, e);
            }
        }

        #endregion //INotifyPropertyChanged Members
    }

}
