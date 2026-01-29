#pragma once

#include<iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:

    static void PrintClientRecordBalanceLine(clsBankClient Client) {

        cout << "|  " << left << setw(15) << Client.GetAccountNumber();
        cout << "|  " << left << setw(40) << Client.FullName();
        cout << "|  " << left << setw(12) << Client.GetAccountBalance();

    }

public:
    
    static void ShowTotalBalances() {

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        cout << "\n\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";

        cout << "\n_________________________________________________________________";
        cout << "_____________________________________________\n" << endl;

        cout << "|  " << left << setw(15) << "Account Number";
        cout << "|  " << left << setw(40) << "Client Name";
        cout << "|  " << left << setw(12) << "Balance";

        cout << "\n_________________________________________________________________";
        cout << "_____________________________________________\n" << endl;

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)

            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient& Client : vClients)
            {
                PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << "\n_________________________________________________________________";
        cout << "_____________________________________________\n" << endl;

        cout << "\t\t\t\t\t  Total Balances = " << TotalBalances << endl;

        cout << "\t\t\t\t    ( " << clsUtil::NumberToText(TotalBalances) << ")";

    }
};

