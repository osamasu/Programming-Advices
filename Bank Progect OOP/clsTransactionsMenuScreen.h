#pragma once

#include "clsInputValidate.h"
#include "clsUtili.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferTransactionsLogScreen.h"

class clsTransactionsMenuScreen : protected clsScreen
{
private:

	enum enTransctionsMenuOptions { eDeposit = 1, eWithdraw, eTotalBalances, eTransfer, eTransferLog, eGoBackToMainMenuScreen };

	static short _ReadTransactionsMenuOption() {

		return clsInputValidate::ReadNumber_InRange<short>("\t\t\t\tEnter Your Option [ 1 To 6 ] ?  | ", 1, 6);
	}
	static void _ShowDepositScreen() {

		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen() {

		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen() {

		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}
	static void _ShowTransferScreen() {

		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferTransactionsLogScreen() {

		clsTransferTransactionsLogScreen::ShowTransfersTransactionsLogScreen();
	}
	static void _GoBackToTransactionsMenuScreen(short NumberOfTabs = 0) {

		cout << clsUtili::Tabs(NumberOfTabs) << "Press Any Key To Go Back To Transactions Menu...";
		system("pause>0");

		ShowTransactionsMenuScreen();
	}



	static void _PerformTransactionsMenuOptions(enTransctionsMenuOptions UserOption) {

		switch (UserOption)
		{
		case clsTransactionsMenuScreen::eDeposit:

			_ShowDepositScreen();
			_GoBackToTransactionsMenuScreen();
			break;

		case clsTransactionsMenuScreen::eWithdraw:

			_ShowWithdrawScreen();
			_GoBackToTransactionsMenuScreen();
			break;

		case clsTransactionsMenuScreen::eTotalBalances:

			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenuScreen(2);
			break;

		case clsTransactionsMenuScreen::eTransfer:

			_ShowTransferScreen();
			_GoBackToTransactionsMenuScreen();
			break;

		case clsTransactionsMenuScreen::eTransferLog:

			_ShowTransferTransactionsLogScreen();
			_GoBackToTransactionsMenuScreen(1);
			break;

		case clsTransactionsMenuScreen::eGoBackToMainMenuScreen:
			break;
		}
	}

public:

	static void ShowTransactionsMenuScreen() {

		system("cls");

		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pTranactions))
			return;

		string Title = "\t  Transactions Menu";
		clsScreen::_DrawScreenHeader(Title);

		printf("\t\t\t\t________________________________________________________\n\n");
		printf("\t\t\t\t\033[36m         [1]  Deposit. \n");
		printf("\t\t\t\t\033[36m         [2]  Withdraw. \n");
		printf("\t\t\t\t\033[36m         [3]  Total Balances. \n");
		printf("\t\t\t\t\033[36m         [4]  Transfer. \n");
		printf("\t\t\t\t\033[36m         [5]  Transfers Log. \n");
		printf("\t\t\t\t\033[5;93m         [6]  Main Menu. \033[0m\n");
		printf("\t\t\t\t__________________________________________________________\n\n");

		_PerformTransactionsMenuOptions((enTransctionsMenuOptions)_ReadTransactionsMenuOption());
	}
};

