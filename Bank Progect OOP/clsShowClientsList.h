#pragma once
#include <iomanip>
#include <vector>
#include "clsBankClient.h"
using namespace std;

class clsClientsListScreen : protected clsScreen
{
private:

	static void _PrintClientDataLine(clsBankClient& Client) {

		cout << "\t";
		cout << left << "|  " << setw(16) << Client.AccountNumber();
		cout << left << "|  " << setw(10) << Client.PinCode;
		cout << left << "|  " << setw(20) << Client.FullName();
		cout << left << "|  " << setw(30) << Client.Email;
		cout << left << "|  " << setw(24) << Client.PhoneNumber;
		cout << left << "|   $ " << setw(10) << Client.AccountBalance;
	}

public:

	static void ShowClientsListScreen() {
		
		system("cls");

		if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pListClients))
			return;

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string SubTitle = "\t\t" + to_string(vClients.size()) + " Client(s).";
		clsScreen::_DrawScreenHeader("\t   Clients List", SubTitle);

		printf("\t________________________________________________________________________________________________________________________________\n\n\t");

		cout << left << '|' << setw(18) << "  Account Number  ";
		cout << left << '|' << setw(10) << "  PIN Code  ";
		cout << left << '|' << setw(22) << "  Client Name  ";
		cout << left << '|' << setw(32) << "  E-Mail  ";
		cout << left << '|' << setw(26) << "  Phone Number  ";
		cout << left << '|' << setw(10) << "  Balance  ";

		printf("\n\t________________________________________________________________________________________________________________________________\n\n");

		if (vClients.size() == 0) {

			printf("\n\t\t  N O   C L I E N T S   A V A I L A B L E   ,  I N   T H E   S Y S T E M \n\n");
		}

		else {
		
			for (clsBankClient& Client : vClients) {


				_PrintClientDataLine(Client);

				cout << endl;
			}
		}
		printf("\n\t_________________________________________________________________________________________________________________________________\n\n");
	}
};

