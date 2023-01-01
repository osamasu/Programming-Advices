#pragma once

class clsAddClientScreen : protected clsScreen
{

private:

	static void _ReadClientInfo(clsBankClient &NewClient) {

		NewClient.FirstName = clsInputValidate::ReadString("\n Enter Your First Name ? |  ");

		NewClient.LastName = clsInputValidate::ReadString("\n Enter Your Last Name ? |  ");
	
		NewClient.PhoneNumber = clsInputValidate::ReadString("\n Enter Your Phone Number ? |  ");

		NewClient.Email = clsInputValidate::ReadString("\n Enter Your E-Mail ? |  ");

		NewClient.PinCode = clsInputValidate::ReadString("\n Enter Your PIN CODE ? |  ");

		NewClient.AccountBalance = clsInputValidate::ReadNumber_InRange <double>("\n Enter Your Balance ? |  ", 0, DBL_MAX);
	}

	static void _PrintClientInfo(clsBankClient &Client) {

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

	static void ShowAddClientScreen() {

		system("cls");

		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pAddNewClient))
			return;
		
		clsScreen::_DrawScreenHeader("\t   Add New Client");

		cout << "\n---------------------------------------------------------------------------------------------\n";
		string AccountNumber = clsInputValidate::ReadString("\n Enter The Account Number ?  | ");

		while (clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\n This Client is Already Exist.\n";
			AccountNumber = clsInputValidate::ReadString(" Enter An Account Number ?  | ");
		}


		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		
		_ReadClientInfo(NewClient); cout << endl;
		cout << "\n--------------------------------------------------------------------------------------------\n";

		clsBankClient::enSaveResult Results = NewClient.Save();

		switch (Results)
		{

		case clsBankClient::svSucceeded:

			cout << "Account Added Successfully :-)\n";
			_PrintClientInfo(NewClient);
			break;
		
		case clsBankClient::svFailedEmptyObject:

			cout << "Error . The Save Was Failed, Because The Account is Empty. :-(\n";
			break;

		case clsBankClient::svFailedAccountNumberExists:
	
			cout << "Account Number is Already Exist. :-(\n";
			break;

		}
	}
};