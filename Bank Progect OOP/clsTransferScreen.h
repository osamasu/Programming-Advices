#pragma once

class clsTransferScreen : protected clsScreen
{
private:

	static void _ClientTransferCardInfo(clsBankClient &Client) {

		printf("\n Client Info:\n");
		printf("_______________________\n\n");
		printf(" Full Name    : %s \n",Client.FullName().c_str());
		printf(" Acc. Number  : %s \n", Client.AccountNumber().c_str());
		printf(" Balance      : %.3f \n", Client.AccountBalance);
		printf("_______________________\n\n");
	}

	static string _ReadAccountNumber(string Message)
	{
		string AccountNumber;
	
		AccountNumber = clsInputValidate::ReadString(Message);

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadString(Message);
		}

		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient SourceClient)
	{
		double Amount;

		Amount = clsInputValidate::ReadNumber_InRange <double> ("\nEnter Transfer Amount? ",0,SourceClient.AccountBalance);

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? \n";

			Amount = clsInputValidate::ReadNumber_InRange<double>("Enter Transfer Amount ? |  ", 0, SourceClient.AccountBalance);
		}

		return Amount;
	}

public:

	static void ShowTransferScreen() {

		system("cls");
		clsScreen::_DrawScreenHeader("\t  Transfer Screen");

		string AccountNumber = _ReadAccountNumber("Enter Account Number To Transfer From ? |  ");
		clsBankClient SourceClient = clsBankClient::Find(AccountNumber);
		_ClientTransferCardInfo(SourceClient);

		AccountNumber = _ReadAccountNumber("Enter Account Number To Transfer To ? |  ");
		clsBankClient DestinationClient = clsBankClient::Find(AccountNumber);
		_ClientTransferCardInfo(DestinationClient);

		double TransferAmount = _ReadAmount(SourceClient);

		char SureToTransfer = clsInputValidate::ReadChar("Are You Sure , You Want To Perform This Operation ? |  ");

		if (toupper(SureToTransfer) == 'Y')
		{
			if (SourceClient.Transfer(TransferAmount, DestinationClient)) {

				cout << "\nTransfer Done Successfully. :-) \n\n";
			}
			else
				cout << "\n Transfer Failed !!  :-(\n";
			
		}

		_ClientTransferCardInfo(SourceClient);
		_ClientTransferCardInfo(DestinationClient);
	}

};

