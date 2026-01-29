#pragma once

#include<iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "Global.h"
#include <iomanip>

class clsTransferScreen : clsScreen
{
private:

    static void _PrintClient(clsBankClient Client) {

        cout << "\nClient Card : ";
        cout << "\n___________________";
        cout << "\nFullName    : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________";

    }

    static string _ReadAccountNumber(string Text) {

        string AccountNumber = "";
        cout << "\n" << Text;

        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nAccount Number is not found , choose another one: \n";
            
            AccountNumber = clsInputValidate::ReadString();
        }

        return AccountNumber;
    }

    static float ReadAmount(clsBankClient SourceClient) 
    {
         float Amount;

         cout << "\nEnter Transfer Amount? ";

         Amount = clsInputValidate::ReadFloatNumber();

         while (Amount > SourceClient.AccountBalance) 
         {
            cout << "Amount Execceds the available Balance , Enter another amount ? ";

            Amount = clsInputValidate::ReadFloatNumber();
         }

         return Amount;
    }

public:

    static void ShowTransferScreen() 
    {

        _DrawScreenHeader("\t Transfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("Please Enter Account Number to Transfer From : "));

        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("Please Enter Account Number to Transfer To : "));

        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);

        char Answer = 'n';

        cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount , DestinationClient , CurrentUser.UserName))
            {
                cout << "\nTransfer done Successfully.\n";
                
            }
            else
            {
                cout << "\nTransfer Faild \n";

            }


        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);


    }

   
};

