#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateCurrancyScreen.h"
#include "clsCurrancyCalculatorScreen.h"
#include <iomanip>

class clsCurrencyExchangeScreen : protected clsScreen
{  

private:
   
    enum enCurrencyExchangeOptions {
        eListCurrencies = 1, eFindCurrency = 2,
        eUpdateCurrencyRate = 3, eCurrencyCalculator = 4, eShowMainMenue = 5
    };

    static short _ReadCurrencyExchangeOption() {

        cout << setw(37) << left << "" << "Choose what do you want to do ? [1 to 5]? ";

        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5 ?");

        return Choice;

    }

    static void _ShowListCurrenciesScreen()
    {
        clsListCurrenciesScreen::ShowCurrenciesListScreen();

    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();

    }
    
    static void _ShowUpdateRateCurrencyScreen()
    {
        clsUpdateRateCurrancyScreen::ShowUpdateRateCurrencyScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
       clsCurrancyCalculatorScreen::ShowCurrancyCalculatorScreen();
    }

    static void _GoBackToCurrencyExchange() {

        cout << "\n\nPress any key to go back to Transactions Menue...\n";

        system("pause>0");

        ShowCurrencyExchangeMenue();

    }
    

    static void _PerformCurrencyExchangeOption(enCurrencyExchangeOptions CurrencyExchange) {

        switch (CurrencyExchange) {

            case enCurrencyExchangeOptions::eListCurrencies:
            {
                system("cls");
                _ShowListCurrenciesScreen();
                _GoBackToCurrencyExchange();
                break;
            }

            case enCurrencyExchangeOptions::eFindCurrency:
            {
                system("cls");
                _ShowFindCurrencyScreen();
                _GoBackToCurrencyExchange();
                break;
            }

            case enCurrencyExchangeOptions::eUpdateCurrencyRate:
            {
                system("cls");
                _ShowUpdateRateCurrencyScreen();
                _GoBackToCurrencyExchange();
                break;
            }


            case enCurrencyExchangeOptions::eCurrencyCalculator:
            {
                system("cls");
                _ShowCurrencyCalculatorScreen();
                _GoBackToCurrencyExchange();
                break;
            }

            case enCurrencyExchangeOptions::eShowMainMenue:
            {
                //do nothing here the main screen will handle it :-) ;
            }


        }
    }

public:

    static void ShowCurrencyExchangeMenue() {

        if (!CheckAccessRights(clsUser::enPermissions::pCurrencyExchange)) {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t Currency Exchange Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t Currency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";

        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyExchangeOption((enCurrencyExchangeOptions)_ReadCurrencyExchangeOption());

    }

};

