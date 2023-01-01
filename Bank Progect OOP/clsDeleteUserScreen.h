#pragma once


using namespace std;

class clsDeleteUserScreen : protected clsScreen
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

	static void ShowDeleteUserScreen() {

		system("cls");

		string Title = "\t  Delete User Screen";
		clsScreen::_DrawScreenHeader(Title);

		string UserName = clsInputValidate::ReadString("\n Enter The UserName ?  | ");

		while (!clsBankUser::IsUserExist(UserName))
		{
			cout << "\nThis User Is Not Found !!";
			UserName = clsInputValidate::ReadString("\n Enter The UserName ?  | ");
		}

		clsBankUser User = clsBankUser::Find(UserName);
		_PrintUserCardInfo(User);

		char SureToDelete = clsInputValidate::ReadChar("\n Are You Sure To Delete This User !!  | ");

		if (toupper(SureToDelete) == 'Y')
		{
			if (User.Delete()) {

				cout << "\nThis User Was Deleted Successfully :-) \n\n.";
			}
			else
			{
				cout << "\nError !! ,  We Failed To Delete This Account :-( \n\n.";
			}
		}
	}

};

