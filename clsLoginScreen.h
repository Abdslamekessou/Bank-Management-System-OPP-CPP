#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:
    
    static bool _Login() 
    {
        bool LoginFailed = false;
        short FailedLoginCount = 0;

        string UserName , Password;

        do {

            if (LoginFailed) 
            { 
                FailedLoginCount++;

               cout << "\nInvalid Username/Password!\n\n";
               cout << "you Have " << (3 - FailedLoginCount) << " Trial(s) to login.\n\n";
            }

            if (FailedLoginCount == 3) 
            {
               cout << "\nYour are Locked after 3 failed trails \n\n";
               return false;
            }

            cout << "Enter UserName? ";
            cin >> UserName;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(UserName , Password);

            LoginFailed = CurrentUser.IsEmpty();

        }while(LoginFailed);

            CurrentUser.RegisterLogIn();
            clsMainScreen::ShowMainMenue();
            return true;
    }

public:
     
    static bool ShowLoginScreen() 
    {

            system("cls");
            _DrawScreenHeader("\t  Login Screen");
            return _Login();


    }
};

