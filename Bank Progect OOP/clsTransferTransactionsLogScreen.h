#pragma once

class clsTransferTransactionsLogScreen : protected clsScreen
{

private:

    static void _PrintTransferLogRecordLine(clsBankClient::strTransferLogRecord TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.SenderAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.RecieverAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.TransferAmount;
        cout << "| " << setw(10) << left << TransferLogRecord.SenderBalanceAfterTransfering;
        cout << "| " << setw(10) << left << TransferLogRecord.RecieverBalanceAfterTransfering;
        cout << "| " << setw(8) << left << TransferLogRecord.Username;
    }

public:

	static void ShowTransfersTransactionsLogScreen() {

		system("cls");

		vector <clsBankClient::strTransferLogRecord> vTransfers = clsBankClient::GetTransfersLogList();


        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransfers.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransfers.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else
        {

            for (clsBankClient::strTransferLogRecord &TransferRecord : vTransfers)
            {
                _PrintTransferLogRecordLine(TransferRecord);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};

