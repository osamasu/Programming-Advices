#pragma once

class clsUpdateClientScreen : protected clsScreen
{

protected:

	static void _UpdateClientInfo(clsBankClient& NewClient) {

		NewClient.FirstName = clsInputValidate::ReadString("\n Enter Your First Name ? |  ");

		NewClient.LastName = clsInputValidate::ReadString("\n Enter Your Last Name ? |  ");

		NewClient.PhoneNumber = clsInputValidate::ReadString("\n Enter Your Phone Number ? |  ");

		NewClient.Email = clsInputValidate::ReadString("\n Enter Your E-Mail ? |  ");

		NewClient.PinCode = clsInputValidate::ReadString("\n Enter Your PIN CODE ? |  ");

		NewClient.AccountBalance = clsInputValidate::ReadNumber <double> ("\n Enter Your Balance ? |  ");
	}

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

	static void ShowUpdateClientScreen() {

		system("cls");

		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pUpdateClients))
			return;

		string Title = "\tUpdate Clien";
		clsScreen::_DrawScreenHeader(Title);

		string AccountNumber = clsInputValidate::ReadString("\n Enter The Account Number ?  | ");

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\n The Client Was Not Found , Please Try Again !! .\n";
			AccountNumber = clsInputValidate::ReadString(" Enter An Account Number ?  | ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClientInfo(Client);

		char SureToUpdate = clsInputValidate::ReadChar("\n Are You Sure To Update This Client Account ? |  ");



		if (toupper(SureToUpdate) == 'Y') {

			cout << "\nUpdate Client Info:\n";
			cout << "---------------------------------------------------------------------------------------------\n";
			_UpdateClientInfo(Client);
			cout << "\n---------------------------------------------------------------------------------------------\n";

			clsBankClient::enSaveResult Result = Client.Save();

			switch (Result)
			{
			case clsBankClient::svFailedEmptyObject:

				cout << "Error . The Save Was Failed, Because The Account is Empty. :-(\n";
				break;

			case clsBankClient::svFailedAccountNumberExists:

				cout << "Account Number is Already Exist. :-(\n";
				break;

			case clsBankClient::svSucceeded:

				cout << "The Updates Was Saved Successfully :-) .";
				break;
			}
		}
	}


};
