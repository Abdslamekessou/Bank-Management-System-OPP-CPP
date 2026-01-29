#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsListCurrenciesScreen : protected clsScreen
{ 

private:
    
    static void _PrintCurrencyRecordLine(clsCurrency Currency) {

        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate();

    }

public:

    static void ShowCurrenciesListScreen() {

        vector <clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();

        string Title = "\t Currencies List Screen";
        string SubTitle = "\t      (" + to_string(vCurrencys.size()) + ") Currencies ";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_____________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << setw(30) << left << "Currency";
        cout << "| " << setw(8) << left << "Code";
        cout << "| " << setw(45) << left << "Name";
        cout << "| " << setw(10) << left << "Rate/(1$)";

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_____________________________________________\n" << endl;

        if (vCurrencys.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else

            for (clsCurrency& Currency : vCurrencys) {

                _PrintCurrencyRecordLine(Currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_____________________________________________\n" << endl;

    }
};

