#pragma once

class clsLoginResgistersScreen : protected clsScreen
{

private:

	static void _PrintLoginRegisterRecordLine(clsBankUser::strLoginRegisterRecord &LoginRegisterRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
		cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
		cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
		cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
	}


public:

	static void ShowLoginRegistersScreen() {

        system("cls");

        if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pLoginRegisters))
            return;

		vector < clsBankUser::strLoginRegisterRecord > vLoginResgisters = clsBankUser::GetLoginRegistersList();


		string Title = "\t  Login Resgister List Screen";
		string SubTitle = "\t    (" + to_string(vLoginResgisters.size()) + ") Record(s).";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginResgisters.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else {

            for (clsBankUser::strLoginRegisterRecord& LoginRecord : vLoginResgisters)
            {

                _PrintLoginRegisterRecordLine(LoginRecord);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

	}
};

