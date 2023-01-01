#pragma once

class clsAddUserScreen : protected clsScreen
{

private:

	static void _ReadUserInfo(clsBankUser& User)
	{
		User.FirstName = clsInputValidate::ReadString("\nEnter FirstName: ");

		User.LastName = clsInputValidate::ReadString("\nEnter LastName: ");

		User.Email = clsInputValidate::ReadString("\nEnter Email: ");

		User.PhoneNumber = clsInputValidate::ReadString("\nEnter Phone: ");

		User.Password = clsInputValidate::ReadString("\nEnter Password: ");

		cout << "\nEnter Permission: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static void _PrintUserCardInfo(clsBankUser& User) {

		cout << "\n User  Card:";
		cout << "\n -----------------------------------------";
		cout << "\n First Name      : " << User.FirstName;
		cout << "\n Last Name       : " << User.LastName;
		cout << "\n Full Name       : " << User.FullName();
		cout << "\n Email           : " << User.Email;
		cout << "\n Phone Number    : " << User.PhoneNumber;
		cout << "\n UserName        : " << User.UserName;
		cout << "\n Password        : " << User.Password;
		cout << "\n Permission      : " << User.Permissions;
		cout << "\n _______________________________________\n";
	}

	static int _ReadPermissionsToSet() {

		int Permissions = 0;

		char GiveFullAccess = clsInputValidate::ReadChar("\nDo You Want To Give Full Access [Y / N] ?  | ");

		if (toupper(GiveFullAccess) == 'Y') {

			return clsBankUser::enPermissions::eAll;
		}

		else {

			cout << "Do You Want To Give Access To :\n\n";

			char GiveAccessTo;

			if (toupper(GiveAccessTo = clsInputValidate::ReadChar("Show Clients List ?  | ")) == 'Y')
				Permissions += clsBankUser::enPermissions::pListClients;

			if (toupper(GiveAccessTo = clsInputValidate::ReadChar("Add New Client ?  | ")) == 'Y')
				Permissions += clsBankUser::enPermissions::pAddNewClient;

			if (toupper(GiveAccessTo = clsInputValidate::ReadChar("Delete Client ?  | ")) == 'Y')
				Permissions += clsBankUser::enPermissions::pDeleteClient;

			if (toupper(GiveAccessTo = clsInputValidate::ReadChar("Update Client ?  | ")) == 'Y')
				Permissions += clsBankUser::enPermissions::pUpdateClients;

			if (toupper(GiveAccessTo = clsInputValidate::ReadChar("Find Client ?  | ")) == 'Y')
				Permissions += clsBankUser::enPermissions::pFindClient;

			if (toupper(GiveAccessTo = clsInputValidate::ReadChar("Transactions ?  | ")) == 'Y')
				Permissions += clsBankUser::enPermissions::pTranactions;

			if (toupper(GiveAccessTo = clsInputValidate::ReadChar("Manage Users ?  | ")) == 'Y')
				Permissions += clsBankUser::enPermissions::pManageUsers;

			if (toupper(GiveAccessTo = clsInputValidate::ReadChar("Show Login Registers ?  | ")) == 'Y')
				Permissions += clsBankUser::enPermissions::pLoginRegisters;

			return Permissions;
		}
	}

  public:

	static void ShowAddUserScreen() {

		system("cls");

		string Title = "\t  Add User User";
		clsScreen::_DrawScreenHeader(Title);

		cout << "\n---------------------------------------------------------------------------------------------\n";

		string UserName = clsInputValidate::ReadString("\n Enter The UserName ?  | ");

		while (clsBankUser::IsUserExist(UserName))
		{
			cout << "\n This Client is Already Exist.\n";
			UserName = clsInputValidate::ReadString(" Enter The UserName ?  | ");
		}

		clsBankUser NewUser = clsBankUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);
		cout << "\n---------------------------------------------------------------------------------------------\n";

		clsBankUser::enSaveResults SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case clsBankUser::svFailedEmptyObject:

			cout << "\nError User was not saved because it's Empty";
			break;

		case clsBankUser::svFailedUserExist:

			cout << "\nError User was not saved because UserName is used!\n";
			break;

		case clsBankUser::svSuccessed:

			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUserCardInfo(NewUser);
			break;
		}
	}
};
