#pragma once
#include "clsCurrency.h"
#include "clsScreen.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{

private:

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

	static void _ReadCurrencyRate(clsCurrency& Currency) {

		cout << "\nUpdate Currency Rate:\n";
		cout << "_________________________\n";

		Currency.CurrencyRate = clsInputValidate::ReadPositiveNumber<double>("\n Enter The New Rate: ");

		cout << "_________________________\n";
	}


public:

	static void ShowUpdateCurrencyRateScreen() {

		system("cls");

		clsScreen::_DrawScreenHeader("\tUpdate Currency Screen");

		string CurrencyCode = clsInputValidate::ReadString("Please Enter Currency Code: | ");

		while (!clsCurrency::isCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one: \n";
			CurrencyCode = clsInputValidate::ReadString();
		}


		clsCurrency CurrencyToUpdate = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(CurrencyToUpdate);
		char SureToUpdateCurrency = clsInputValidate::ReadChar("\nAre You Sure To Update Currency Rate Of This Currency: | ");

		if (toupper(SureToUpdateCurrency) == 'Y')
		{
			_ReadCurrencyRate(CurrencyToUpdate);
			CurrencyToUpdate.UpdateRate();

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(CurrencyToUpdate);
		}
		
	}

};

