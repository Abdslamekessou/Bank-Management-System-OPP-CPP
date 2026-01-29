#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include <iomanip>

class clsFindCurrencyScreen : clsScreen
{

private:
    
    static void _PrintCurrency(clsCurrency Currency) {

        cout << "\nCurrency Card: ";
        cout << "\n___________________";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n___________________";

    }
    
    static void _ShowResults(clsCurrency Currency) 
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";

            _PrintCurrency(Currency);
        }
        else {
            cout << "\nCurrency Not Found :-)\n";
        }
    }

public:

    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\tFind Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = 1;

        cin >> Answer;

        if (Answer == 1) 
        {
             cout << "\nPlease Enter CurrencyCode: ";
             string CurrencyCode = clsInputValidate::ReadString();
             clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
             _ShowResults(Currency);
            
        }
        else {
             
            cout << "\nPlease Enter Country Name: ";
            string CurrencyCode = clsInputValidate::ReadString();

            clsCurrency Currency = clsCurrency::FindByCountry(CurrencyCode);
            
            _ShowResults(Currency);

        }
    }

};

