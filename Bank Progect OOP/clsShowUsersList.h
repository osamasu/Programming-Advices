#pragma once

class clsShowUsersList : protected clsScreen
{

private:

    static void _PrintUserRecordLine(clsBankUser &User)
    {

        cout << setw(8) << left << "" << "| " << setw(12) << left << User.UserName;
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(18) << left << User.PhoneNumber;
        cout << "| " << setw(25) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;

    }

public:

    static void ShowUsersList()
    {

        system("cls");
        vector <clsBankUser> vUsers = clsBankUser::GetUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(18) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_________________________________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";

        else {

            for (clsBankUser& User : vUsers)
            {

                _PrintUserRecordLine(User);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

