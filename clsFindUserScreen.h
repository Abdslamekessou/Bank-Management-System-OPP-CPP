#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsFindUserScreen : protected clsScreen
{
private:
   
    static void _PrintUser(clsUser User) {

        cout << "\nUser Card : ";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFullName    : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________";

    }

public:
    
    static void ShowFindUserScreen() {

        _DrawScreenHeader("\t Find User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";

        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "UserName is not found , Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty()) {

           cout << "\nUser Found :-)\n";

        }
        else 
        {
            cout << "\nUser was not Found :-(\n";
        }

        _PrintUser(User1);
    }

};

