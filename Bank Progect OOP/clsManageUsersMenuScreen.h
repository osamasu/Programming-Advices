#pragma once
#include "clsShowUsersList.h"
#include "clsAddUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"


class clsManageUsersMenuScreen : protected clsScreen
{

private:

	enum enManageUsersMenuOptions { eListUsers = 1, eAddNewUser, eDeleteUser, eUpdateUser, eFindUser, eGoBackToMainMenuScreen };

	static short _ReadManageUsersMenuOption() {

		return clsInputValidate::ReadNumber_InRange<short>("\t\t\t\tEnter Your Option [ 1 To 6 ] ?  | ", 1, 6);
	}

	static void _ShowListUsersScreen() {

		clsShowUsersList::ShowUsersList();
	}

	static void _ShowAddNewUserScreen() {

		clsAddUserScreen::ShowAddUserScreen();
	}

	static void _ShowDeleteUserScreen() {

		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen() {

		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen() {

		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _GoBackToManageUsersMenuScreen(short NumberOfTabs = 0) {

		cout << clsUtili::Tabs(NumberOfTabs) << "Press Any Key To Back To Manage Users Menu...";
		system("pause>0");

		ShowManageUsersMenuScreen();
	}

	static void _PerformManageUsersMenuOption(enManageUsersMenuOptions UserOption) {

		switch (UserOption)
		{
		case clsManageUsersMenuScreen::eListUsers:

			_ShowListUsersScreen();
			_GoBackToManageUsersMenuScreen(1);
			break;

		case clsManageUsersMenuScreen::eAddNewUser:
			
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenuScreen();
			break;

		case clsManageUsersMenuScreen::eDeleteUser:
			
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenuScreen();
			break;

		case clsManageUsersMenuScreen::eUpdateUser:

			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenuScreen();
			break;

		case clsManageUsersMenuScreen::eFindUser:

			_ShowFindUserScreen();
			_GoBackToManageUsersMenuScreen();
			break;

		case clsManageUsersMenuScreen::eGoBackToMainMenuScreen:
			break;
		
		}
	}


public:

	static void ShowManageUsersMenuScreen() {

		system("cls");

		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pManageUsers))
			return;

		string Title = "\t  Manage Users Screen";
		clsScreen::_DrawScreenHeader(Title);

		printf("\t\t\t\t________________________________________________________\n\n");
		printf("\t\t\t\t\033[5;96m         [1]  List Users. \n");
		printf("\t\t\t\t         [2]  Add New User. \n");
		printf("\t\t\t\t         [3]  Delete User. \n");
		printf("\t\t\t\t         [4]  Update User. \n");
		printf("\t\t\t\t         [5]  Find User. \033[0m\n");
		printf("\t\t\t\t\033[5;93m         [6]  Main Menu. \033[0m\n");
		printf("\t\t\t\t__________________________________________________________\n\n");
	
		_PerformManageUsersMenuOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
	}

};

