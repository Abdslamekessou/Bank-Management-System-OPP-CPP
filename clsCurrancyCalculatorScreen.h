#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>

using namespace std;

class clsCurrancyCalculatorScreen : clsScreen
{

private:

    static void _PrintCurrencyCard(clsCurrency Currency , string Title = "Currency Card:") {

        cout << "\n" << Title << "\n";
        cout << "\n___________________";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n___________________";

    }

    static clsCurrency _GetCurrency(string Message) 
    {
        string CurrencyCode;
        cout << Message <<endl;

        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found , choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        return Currency;

    }

    static float _ReadAmount()
    {
        cout << "\n\nEnter Amount to Exchange : ";
        float Amount = 0;

        Amount = clsInputValidate::ReadFloatNumber();

        return Amount;
    }

    static void _PrintCalculationsResuls(float Amount , clsCurrency Currency1 , clsCurrency Currency2)
    {
        _PrintCurrencyCard(Currency1 , "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout <<"\n\n" << Amount << " " << Currency1.CurrencyCode() << " = "
        << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD") 
        {
            return;
        }

        cout << "\nConverting from USD to: \n";

        _PrintCurrencyCard(Currency2 , "To :");

        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount , Currency2);

        cout <<"\n\n" << Amount << " " << Currency1.CurrencyCode() << " = "
            << AmountInCurrency2 << " " << Currency2.CurrencyCode();

      
    }

public:

    static void ShowCurrancyCalculatorScreen()
    {

      char Continue = 'Y';

      while (Continue == 'Y' || Continue == 'y') {

          system("cls");
           
          _DrawScreenHeader("\tCurrancy Calculator Screen");

          clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency 1 Code : ");
          clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency 2 Code : ");

          float Amount = _ReadAmount();

          _PrintCalculationsResuls(Amount , CurrencyFrom , CurrencyTo);


          cout << "\n\nAre you want to perform another calculation y/n? ";

          cin >> Continue;

      }

    }
};

