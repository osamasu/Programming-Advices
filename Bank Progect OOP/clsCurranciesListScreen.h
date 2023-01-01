#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurranciesListScreen : protected clsScreen
{
private:

    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country;
        cout << "| " << setw(8) << left << Currency.CurrencyCode;
        cout << "| " << setw(45) << left << Currency.CurrencyName;
        cout << "| " << setw(10) << left << Currency.CurrencyRate;

    }



public:

    static void ShowCurrancieslistScreen() {

        system("cls");

        vector <clsCurrency> vCurranciesList = clsCurrency::GetCurranciesList();

        string Title = "\tCurrencies List Screen";
        string SubTitle = "\t  (" + to_string(vCurranciesList.size()) + ") Currancies.";
        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        if (vCurranciesList.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else

            for (clsCurrency& Currency : vCurranciesList)
            {

                _PrintCurrencyRecordLine(Currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

    }
};

