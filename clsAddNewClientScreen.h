#pragma once

#include<iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"


class clsAddNewClientScreen : protected clsScreen
{

private:

    static void _ReadClientInfo(clsBankClient& Client) {

        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

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

    static void AddNewClient() {

        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
            return;
        }

        
        _DrawScreenHeader("\t  Add New Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nAccount number is already in use , Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);


        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult) {

        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Added Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }

        case clsBankClient::enSaveResults::svFailedEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty\n";
            break;

        }

        case clsBankClient::enSaveResults::svFailedAccountNumberExists:
        {
            cout << "\nError , account was not saved because account number is in used! \n";
            break;
        }

        }
    }
     
};

