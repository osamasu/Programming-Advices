#pragma once

class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen() {

		system("cls");

		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pDeleteClient))
			return;

		string Title = "\t  Delete Client Screen";
		clsScreen::_DrawScreenHeader(Title);

		string AccountNumber = clsInputValidate::ReadString("\n Enter The Account Number ?  | ");

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\n The Client Was Not Found , Please Try Again !! .\n";
			AccountNumber = clsInputValidate::ReadString(" Enter An Account Number ?  | ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClientInfo(Client);

		char SureToDelete = clsInputValidate::ReadChar("\n Are You Sure To Delete This Client Account ? |  ");

		if (toupper(SureToDelete) == 'Y') {

			if (Client.Delete()) {

				_PrintClientInfo(Client);
				cout << "\nAccount Was Deleted Successfully :-) \n\n";
			}
			else {
				cout << "Error . Account Failed To Delete.\n\n";
			}
		}
	}

};

