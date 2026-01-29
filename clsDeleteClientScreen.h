#pragma once

#include<iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"


class clsDeleteClientScreen : protected clsScreen
{ 

private:

    static void _PrintClient(clsBankClient Client) {

        cout << "\nInfo : ";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFullName    : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber;
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________";

    }
 
public:

    static void DeleteClient() {

        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
            return;
        }


        _DrawScreenHeader("\t  Delete Client Screen");
        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nAccount number is not found , choose another one: ";
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\n\nAre You sure you want to delete this client y/n? : ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {

            if (Client1.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client1);
            }
            else {
                cout << "\nError Client Was not Deleted\n";
            }
        }

    }
};

