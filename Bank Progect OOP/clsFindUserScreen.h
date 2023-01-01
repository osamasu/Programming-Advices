#pragma once

class clsFindUserScreen : protected clsScreen
{

private:

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

public:

	static void ShowFindUserScreen() {

		system("cls");

		string Title = "\t  Find User Screen";
		clsScreen::_DrawScreenHeader(Title);

		cout << "________________________________________________________________\n\n";

		string UserName = clsInputValidate::ReadString("\n Enter The UserName ?  | ");

		while (!clsBankUser::IsUserExist(UserName))
		{
			cout << "\n The User Was Not Found !!.\n";
			UserName = clsInputValidate::ReadString(" Enter The UserName ?  | ");
		}

		clsBankUser User = clsBankUser::Find(UserName);

		_PrintUserCardInfo(User); 
		cout << endl;
	}
};

