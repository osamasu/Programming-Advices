#pragma once
#include "clsShowClientsList.h"
#include "clsAddClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsMenuScreen.h"
#include "clsManageUsersMenuScreen.h"
#include "clsLoginResgistersScreen.h"
#include "clsShowCurrencyExchangeMenu.h"

class clsMainScreen : protected clsScreen 
{
	enum enMainMenuOptions { eShowClients = 1, eAddNewClient, eDeleteClient, eUpdateClient, eFindClient, eTransactions, eManageUsers , eLoginRegisters,eCurrencyExchanges, eLogout };
	
	static enMainMenuOptions _ReadMainMenuOption() {

		return (enMainMenuOptions)clsInputValidate::ReadNumber_InRange <short> ("\t\t\t\tEnter Your Option [ 1 To 10 ] ?  | ",1,10);
	}

	static void _ShowClientsListScreen() {

		clsClientsListScreen::ShowClientsListScreen();
	}

	static void _ShowAddClientScreen() {

		clsAddClientScreen::ShowAddClientScreen();
	}

	static void _ShowDeleteClientScreen() {

		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen() {

		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen() {

		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenuScreen() {

		clsTransactionsMenuScreen::ShowTransactionsMenuScreen();
	}

	static void _ShowManageUsersMenuScreen() {

		clsManageUsersMenuScreen::ShowManageUsersMenuScreen();
	}

	static void _ShowLoginRegistersScreen() {

		clsLoginResgistersScreen::ShowLoginRegistersScreen();
	}

	static void _ShowCurrenciesExchangeMenu() {

		clsShowCurrencyExchangeMenu::ShowCurrenciesExchangesMainMenu();
	}

	static void _Logout() {

		system("cls");
		CurrentUser = clsBankUser::Find("", "");
	}

	static void _GoBackToMainMenuScreen(short NumberOfTabs = 0) {

		cout << clsUtili::Tabs(NumberOfTabs) << "Press Any Key To Back To Main Menu...";
		system("pause>0");

		ShowMainMenuScreen();
	}

	static void _PerformMainMenuOptions(enMainMenuOptions UserOption) {

		switch (UserOption)
		{
		case clsMainScreen::eShowClients:
			_ShowClientsListScreen();
			_GoBackToMainMenuScreen(1);
			break;

		case clsMainScreen::eAddNewClient:
			_ShowAddClientScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::eDeleteClient:
			_ShowDeleteClientScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::eUpdateClient:
			_ShowUpdateClientScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::eFindClient:
			_ShowFindClientScreen();
			_GoBackToMainMenuScreen(1);
			break;

		case clsMainScreen::eTransactions:
			_ShowTransactionsMenuScreen();
			_GoBackToMainMenuScreen(4);
			break;

		case clsMainScreen::eManageUsers:
			_ShowManageUsersMenuScreen();
			_GoBackToMainMenuScreen(4);
			break;

		case clsMainScreen::eLoginRegisters:
			_ShowLoginRegistersScreen();
			_GoBackToMainMenuScreen();
			break;

		case clsMainScreen::eCurrencyExchanges:
			_ShowCurrenciesExchangeMenu();
			_GoBackToMainMenuScreen(4);

		case clsMainScreen::eLogout:
			_Logout();
			break;
		}
	}

public:

	static void ShowMainMenuScreen() {

		system("cls");

		clsScreen::_DrawScreenHeader("\t  \033[5;92m Main Menu Screen\033[0m");

		printf("\t\t\t\t________________________________________________________\n\n");
		printf("\t\t\t\t\033[36m         [1]  Show Clients List. \033[0m\n");
		printf("\t\t\t\t\033[36m         [2]  Add New Client. \033[0m\n");
		printf("\t\t\t\t\033[36m         [3]  Delete Client. \033[0m\n");
		printf("\t\t\t\t\033[36m         [4]  Update Client Info. \033[0m\n");
		printf("\t\t\t\t\033[36m         [5]  Find Client. \033[0m\n");
		printf("\t\t\t\t\033[36m         [6]  Transactions. \033[0m\n");
		printf("\t\t\t\t\033[36m         [7]  Manage Users. \033[0m\n");
		printf("\t\t\t\t\033[36m         [8]  Login Register. \033[0m\n");
		printf("\t\t\t\t\033[36m         [9]  Currancy Exchange. \033[0m\n");
		printf("\t\t\t\t\033[31m         [10]  Logout. \033[0m\n");
		printf("\t\t\t\t__________________________________________________________\n\n");
	
		_PerformMainMenuOptions(_ReadMainMenuOption());
	}
};

