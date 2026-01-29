#pragma once

#include<iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

class clsFindClientScreen : protected clsScreen
{
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

public :

    static void ShowFindClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pFindClient) ){
            return;
        }

        _DrawScreenHeader("\t  Find Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nAccount number is not found , choose another one: ";
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty()) {

            cout << "\nClient Found :-(\n";

        }
        else {

            cout << "\nClient Was not Found :-(\n";

        }

        _PrintClient(Client1);

    }
};

