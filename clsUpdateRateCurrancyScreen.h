#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsUpdateRateCurrancyScreen : clsScreen
{

private:
    
    static float _ReadRate() 
    {
        cout << "\n\nEnter New Rate : ";
        float NewRate = 0;

        NewRate = clsInputValidate::ReadFloatNumber();

        return NewRate;
    }

    static void _PrintCurrency(clsCurrency Currency) {

        cout << "\n\nCurrency Card: ";
        cout << "\n___________________";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n___________________";

    }

public: 

    static void ShowUpdateRateCurrencyScreen()
    {

           _DrawScreenHeader("\tUpdate Currency Screen");
        
           string CurrencyCode = "";

            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();

            while (!clsCurrency::IsCurrencyExist(CurrencyCode)) 
            {
                cout << "\nCurrency is not found , choose another one: ";
                CurrencyCode = clsInputValidate::ReadString();
            }

            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            
            _PrintCurrency(Currency);

            cout << "\n\nAre you want to update the rate of this Currency y/n? ";

            char Answer = 'n';

            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y') 
            {
                cout << "\n\nUpdate Currency Rate : ";
                cout << "\n___________________";



                Currency.UpdateRate(_ReadRate());

                cout << "\n\nCurrency Rate Updated Successfully :-)";
                
                _PrintCurrency(Currency);

            }



   
    }
};

