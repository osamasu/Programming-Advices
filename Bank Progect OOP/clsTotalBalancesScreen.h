#pragma once

class clsTotalBalancesScreen : protected clsScreen {

private:

	static void _PrintClientRecordBalanceLine(clsBankClient Client)
	{
		cout << "\t\t";
		cout << "|  " << setw(16) << Client.AccountNumber();
		cout << "|  " << setw(35) << Client.FullName();
		cout << "|  $ " << setw(14) << Client.AccountBalance;
	}

public:

	static void ShowTotalBalancesScreen() {

		system("cls");

		string Title = "\t  Total Balances List";
		clsScreen::_DrawScreenHeader(Title);

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		cout << "\t\t_____________________________________________________________________________________\n\n";

		cout << left << setw(17) << "\t\t|  Account Number  ";
		cout << setw(38) << "|  Client Name  ";
		cout << setw(14) << "|  Balances  ";

		cout << "\n\t\t____________________________________________________________________________________\n\n";

		for (clsBankClient& C : vClients) {

			_PrintClientRecordBalanceLine(C);
			cout << endl;
		}
		cout << "\t\t____________________________________________________________________________________\n\n";

		double TotalBalances = clsBankClient::GetTotalBalances();

		printf("\t\t Total Balances = { $ %.4f } \n", TotalBalances);
		printf("\t\t {  %s  }\n\n", clsString::NumberToText((int)TotalBalances).c_str());

	}
};