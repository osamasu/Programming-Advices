#pragma once

#include "clsBankUser.h"
#include <iostream>
using namespace std;

clsBankUser CurrentUser = clsBankUser::Find("", "");


/*	static void ShowMainMenu()
	{
		vector<short> UserOptions;
		short OptonsNumber = 1;
		system("cls");
		_DrawScreenHeader("Main Menu Screen", "", UserCurent.FullName());
		cout << setw(37) << left << "" << "==========================================\n";
		cout << setw(37) << left << "" << "\t\t     Main Menu\n";
		cout << setw(37) << left << "" << "==========================================\n";
		if (Is_AccessRight(clsBankUser::enPermissions::pShowClientsList))
		{
			cout << setw(37) << left << "" << " [" << OptonsNumber << "] Show Clients List.\n";
			UserOptions.push_back(1);
			OptonsNumber++;
		}
		if (Is_AccessRight(clsBankUser::enPermissions::pAddNewClient))
		{
			cout << setw(37) << left << "" << " [" << OptonsNumber << "] Add New Client.\n";
			UserOptions.push_back(2);
			OptonsNumber++;
		}
		if (Is_AccessRight(clsBankUser::enPermissions::pDeleteClient))
		{
			cout << setw(37) << left << "" << " [" << OptonsNumber << "] Delete Client.\n";
			UserOptions.push_back(3);
			OptonsNumber++;
		}
		if (Is_AccessRight(clsBankUser::enPermissions::pUpdateClient))
		{
			cout << setw(37) << left << "" << " [" << OptonsNumber << "] Update Client Info.\n";
			UserOptions.push_back(4);
			OptonsNumber++;
		}
		if (Is_AccessRight(clsBankUser::enPermissions::pFindClient))
		{
			cout << setw(37) << left << "" << " [" << OptonsNumber << "] Find Client.\n";
			UserOptions.push_back(5);
			OptonsNumber++;
		}
		if (Is_AccessRight(clsBankUser::enPermissions::pTransactions))
		{
			cout << setw(37) << left << "" << " [" << OptonsNumber << "] Transactions.\n";
			UserOptions.push_back(6);
			OptonsNumber++;
		}
		if (Is_AccessRight(clsBankUser::enPermissions::pManageUsers))
		{
			cout << setw(37) << left << "" << " [" << OptonsNumber << "] Manage Users.\n";
			UserOptions.push_back(7);
			OptonsNumber++;
		}
		cout << setw(37) << left << "" << " [" << OptonsNumber << "] Logout.\n";
		UserOptions.push_back(8);
		cout << setw(37) << left << "" << "==========================================\n";
		_PerformMainMenuOption((_enMainMenuOptions)_ReadMainMenuOption(UserOptions));

	}
};*/