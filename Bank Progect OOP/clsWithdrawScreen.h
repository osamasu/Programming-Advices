#pragma once
#include "clsBankClient.h"

class clsWithdrawScreen : protected clsScreen
{

private:

	static void _PrintClientInfo(clsBankClient& Client) {

		cout << "\n Client Card:";
		cout << "\n -----------------------------------------";
		cout << "\n First Name      : " << Client.FirstName;
		cout << "\n Last Name       : " << Client.LastName;
		cout << "\n Full Name       : " << Client.FullName();
		cout << "\n Email           : " << Client.Email;
		cout << "\n Phone Number    : " << Client.PhoneNumber;
		cout << "\n Account Number  : " << Client.AccountNumber();
		cout << "\n PIN CODE        : " << Client.PinCode;
		cout << "\n Account Balance : " << Client.AccountBalance;
		cout << "\n _______________________________________\n";
	}

public:

	static void ShowWithdrawScreen() {

		system("cls");

		string Title = "\t  Withdraw Screen";
		clsScreen::_DrawScreenHeader(Title);

		string AccountNumber = clsInputValidate::ReadString("\n Enter The Account Number ?  | ");

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\n The Client Was Not Found , Please Try Again !! .\n";
			AccountNumber = clsInputValidate::ReadString(" Enter An Account Number ?  | ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClientInfo(Client);

		double WithdrawAmount = clsInputValidate::ReadNumber_InRange <double> ("\n  Please Enter Withdraw Amount ? |  ", 0, Client.AccountBalance);

		char SureToWithdraw = clsInputValidate::ReadChar("\n  Are You Sure To Perform This Transaction ");

		if (toupper(SureToWithdraw) == 'Y') {

			if (Client.Withdraw(WithdrawAmount)) {

				cout << "\nAmount Withdraw Successfully\n\n";
				cout << "Your Current Balance = { " << Client.AccountBalance << " } \n\n";
			}
			else {

				cout << "Cannot Withdraw , InInsuffecient Balance !!\n\n";
			}
		}
	}
};

