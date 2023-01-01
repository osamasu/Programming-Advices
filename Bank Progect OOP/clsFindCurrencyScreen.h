#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsFindCurrecyScreen : protected clsScreen
{

private:

	enum enFindCurrencyBy { CurrencyCode = 1, CurrencyCountry };

	static short _ReadUserFindCurrencyByOption() {

		return clsInputValidate::ReadNumber_InRange <short>("Find By: [1] Code  Or  [2] Country ? |  ", 1, 2);
	}

	static clsCurrency _PerformFindCurrencyOption(enFindCurrencyBy UserOption) {

		string CurrencyCodeToFind;
		 

		switch (UserOption) {

		case clsFindCurrecyScreen::CurrencyCode:
			CurrencyCodeToFind = clsInputValidate::ReadString("Please Enter The Currency Code : |  ");
			return clsCurrency::FindByCode(CurrencyCodeToFind);

		case clsFindCurrecyScreen::CurrencyCountry:
			string CurrencyCountryToFind = clsInputValidate::ReadString("Please Enter The Currency Country Name : |  ");
			return clsCurrency::FindByCountry(CurrencyCountryToFind);
		}
	}

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country;
		cout << "\nCode       : " << Currency.CurrencyCode;
		cout << "\nName       : " << Currency.CurrencyName;
		cout << "\nRate(1$) = : " << Currency.CurrencyRate;
		cout << "\n_____________________________\n";

	}

	static void _ShowResult(clsCurrency Currency) {

		if (!Currency.isEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
			cout << "\nSorry !!  , Currency Was Not Found !!\n\n";
	}

public:

	static void ShowFindCurrencyScreen() {

		system("cls");

		string Title = "\t Find Currency Screen";
		clsScreen::_DrawScreenHeader(Title);

		clsCurrency Currency = _PerformFindCurrencyOption((enFindCurrencyBy)_ReadUserFindCurrencyByOption());

		_ShowResult(Currency);
	}
};

