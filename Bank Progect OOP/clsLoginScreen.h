#pragma once
#include "clsScreen.h"
#include "Global.h"
#include "clsMainMenu.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{
private:

	static void _Tistahl() {

		cout << "\t\t\t\t\t\t\033[31m      ___    " << endl;
		cout << "\t\t\t\t\t\t    =     =  " << endl;
		cout << "\t\t\t\t\t\t   =       = " << endl;
		cout << "\t\t\t\t\t\t   ========= " << endl;
		cout << "\t\t\t\t\t\t   ==== ==== " << endl;
		cout << "\t\t\t\t\t\t   ===  ==== " << endl;
		cout << "\t\t\t\t\t\t   ========= \033[0m\n\n" << endl;

		cout << "\t\t\t\t\033[33m       |      ____  |   = =        = =   " << endl;
		cout << "\t\t\t\t   |   |      |  |  |    |          |    " << endl;
		cout << "\t\t\t\t   |___|_____|_|_|  |____|__|_|_|___|    " << endl;
		cout << "\t\t\t\t                                         " << endl;
		cout << "\t\t\t\t                                         " << endl;
		cout << "\t\t\t\t                -------                  " << endl;
		cout << "\t\t\t\t             =============               " << endl;
		cout << "\t\t\t\t            ==== ====== ====             " << endl;
		cout << "\t\t\t\t           === == === == ====            " << endl;
		cout << "\t\t\t\t           ==================            " << endl;
		cout << "\t\t\t\t           ====          ====            " << endl;
		cout << "\t\t\t\t            ====        ====             " << endl;
		cout << "\t\t\t\t              ====____====               " << endl;
		cout << "\t\t\t\t                 ======                  \033[0m" << endl;

		system("pause > 0");
	}

	static bool _Login() {

		bool LoginFailed = false;
		string Username, Password;
		short NumberOfTrials = 0;

		do
		{

			if (LoginFailed)
			{
				cout << "\n\a\b\t\t\t\t Error . { Invlaid Username / Password } !!\n";
				printf("\t\t\t\tYou Have %d Trials To Login.\n\n", 3 - ++NumberOfTrials);

				if (NumberOfTrials == 3) {

					cout << "\a\n\t\t\t { Your Account Was Blocked After 3 Failed Trials , Please Call The Bank To Help ! }\n\n";
					_Tistahl();
					return false;
				}
			}

			Username = clsInputValidate::ReadString("\t\t\t\tEnter Username ? |  ");
			Password = clsInputValidate::ReadString("\t\t\t\tEnter Password ? |  ");

			CurrentUser = clsBankUser::Find(Username, Password);
			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenuScreen();
		return true;
	}

public:

	static bool ShowLoginScreen() {

		system("cls");
		clsScreen::_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}
};

