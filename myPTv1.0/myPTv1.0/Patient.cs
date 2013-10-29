using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace myPTv1._0
{
    class Patient : User
    {
        bool ptSession;        //if yes, session has been created by trainer
        char* dbKey;
        DateTime timeOfLastSession;

        void login(){

        }

        void mainMenu()
        {
            //Pulls the main menu
        }

        private void createSession()
        {
            //Put algorithm here to create a PT session
            //Set ptSession to 1
        }

        void completeSession()
        {
            //Pulls up a window to prompt user to play games
        }

        void viewStatus()
        {
            //Pulls up a window to show visualizations
        }

        void openDatabase(){
            //Opens database for specific user
            //returns way to reference?
        }

        void updateProfile()
        {
            //in case the user needs to update their personal information
        }

    }
}
