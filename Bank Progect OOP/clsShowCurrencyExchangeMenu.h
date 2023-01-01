#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurranciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsString.h"

class clsShowCurrencyExchangeMenu : protected clsScreen
{	
	private:

		enum enCurrenciesMainMenuOption { eListCurrencies = 1, eFindCurrency, eUpdateCurrencyRate, CurrencyCalculator , GoBackToMainMenu };


		static short _ReadCurrencyMenuOption() {

			return clsInputValidate::ReadNumber_InRange <short>("\t\t\t\tEnter Your Choice { 1 to 4 } ? |  ", 1, 5);
		}


		static void _ShowCurrenciesListScreen() {

			clsCurranciesListScreen::ShowCurrancieslistScreen();
		}

		static void _ShowFindCurrencyScreen() {

			clsFindCurrecyScreen::ShowFindCurrencyScreen();
		}


		static void _ShowUpdateCurrencyRateScreen() {

			clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
		}

		static void _ShowCurrencyCalaculatorScreen() {

			cout << "Currencies Calaculator Screen , Will Be Here .....";
		}

		static void _GoBackToCurrancyMainMenu(short NumberOfTabs = 0) {

			cout << clsUtili::Tabs(NumberOfTabs) << "Press Any Key To Go Back To Currency Main Menu Screen..."; system("pause>0");

			ShowCurrenciesExchangesMainMenu();
		}

		static void _PerformCurrenciesMainMenuOptions(enCurrenciesMainMenuOption UserOption) {

			switch (UserOption)
			{
			case clsShowCurrencyExchangeMenu::eListCurrencies:

				_ShowCurrenciesListScreen();
				_GoBackToCurrancyMainMenu(1);
				break;

			case clsShowCurrencyExchangeMenu::eFindCurrency:

				_ShowFindCurrencyScreen();
				_GoBackToCurrancyMainMenu();
				break;

			case clsShowCurrencyExchangeMenu::eUpdateCurrencyRate:

				_ShowUpdateCurrencyRateScreen();
				_GoBackToCurrancyMainMenu();
				break;

			case clsShowCurrencyExchangeMenu::CurrencyCalculator:

				_ShowCurrencyCalaculatorScreen();
				_GoBackToCurrancyMainMenu();
				break;

			case clsShowCurrencyExchangeMenu::GoBackToMainMenu:{}

			}
		}

	public:

		static void ShowCurrenciesExchangesMainMenu() {

			system("cls");
			clsScreen::_DrawScreenHeader("\033[5;94m   Currency Exchange Main Screen\033[0m");

			printf("\t\t\t\t________________________________________________________\n\n");
			printf("\t\t\t\t\033[5;94m         [1]  List Currencies. \n");
			printf("\t\t\t\t         [2]  Find Currency. \n");
			printf("\t\t\t\t         [3]  Update Rate. \n");
			printf("\t\t\t\t         [4]  Currency Calculator. \033[0m\n");
			printf("\t\t\t\t\033[5;93m         [5]  Main Menu. \033[0m\n");
			printf("\t\t\t\t__________________________________________________________\n\n");

			_PerformCurrenciesMainMenuOptions((enCurrenciesMainMenuOption)_ReadCurrencyMenuOption());
		}


};

