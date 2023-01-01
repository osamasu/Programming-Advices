#pragma once

class clsFindClientScreen : protected clsScreen
{
private:

	static void _PrintClientInfo(clsBankClient& Client) {

		cout << "\n\t Client Card:";
		cout << "\n\t -----------------------------------------";
		cout << "\n\t First Name      : " << Client.FirstName;
		cout << "\n\t Last Name       : " << Client.LastName;
		cout << "\n\t Full Name       : " << Client.FullName();
		cout << "\n\t Email           : " << Client.Email;
		cout << "\n\t Phone Number    : " << Client.PhoneNumber;
		cout << "\n\t Account Number  : " << Client.AccountNumber();
		cout << "\n\t PIN CODE        : " << Client.PinCode;
		cout << "\n\t Account Balance : " << Client.AccountBalance;
		cout << "\n\t _______________________________________\n\n";
	}


public:

	static void ShowFindClientScreen() {

		system("cls");

		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pFindClient))
			return;

		string Title = "\t  Find Client";
		clsScreen::_DrawScreenHeader(Title);

		cout << "\t------------------------------------------------------------------------\n";

		string AccountNumber = clsInputValidate::ReadString("\n\t Enter The Account Number ?  | ");

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\n\t The Client Was Not Found , Please Try Again !! .\n";
			return;
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClientInfo(Client);

	}
};
