#pragma once


class clsBankClient : public clsPerson
{
	
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _GetEmptyClientObject() {

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "","",0);
	}
	static clsBankClient _GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}



	static clsBankClient _ConvertLineToClientObject(string LineOfData, string Seperator = "#//#") {

		vector <string> vClient = clsString::Split(LineOfData, Seperator);

		return clsBankClient(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], clsUtili::DecryptText(vClient[5]), stod(vClient[6]));
	}
	static vector <clsBankClient> _LoadFileDataToVClientObject() {

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string sLine;

			while (getline(MyFile,sLine)) 
			{
				clsBankClient Client = _ConvertLineToClientObject(sLine);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client , string Seperator = "#//#") {

		string DataLine = "";
		DataLine = Client.FirstName + Seperator;
		DataLine += Client.LastName + Seperator;
		DataLine += Client.Email + Seperator;
		DataLine += Client.PhoneNumber + Seperator;
		DataLine += Client.AccountNumber() + Seperator;
		DataLine += clsUtili::EncryptText(Client.PinCode) + Seperator;
		DataLine += to_string(Client.AccountBalance);

		return DataLine;
	}

	

	static  void _SaveClientsDataToFile(vector <clsBankClient> &vClients , string Seperator = "#//#") {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open()) {

			string DataLine;

			for (clsBankClient& Client : vClients) {

				if (Client.MarkedToDelete != true) {

					DataLine = _ConvertClientObjectToLine(Client, Seperator);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update() {

		vector <clsBankClient> _vClients = _LoadFileDataToVClientObject();

		for (clsBankClient& Client : _vClients) {

			if (Client.AccountNumber() == AccountNumber()) {

				Client = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string LineOfData) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << LineOfData << endl;
			
			MyFile.close();
		}
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord(clsBankClient DestinationClient, double TransferAmount, string Seperator = "#//#") {

		string TransferLogData = clsDate::GetSystemDateFullTimeInString() + Seperator;
		TransferLogData += _AccountNumber + Seperator + DestinationClient.AccountNumber() + Seperator;
		TransferLogData += to_string(TransferAmount) + Seperator;
		TransferLogData += to_string(_AccountBalance) + Seperator + to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogData += CurrentUser.UserName;
		return TransferLogData;
	}

	void _RegisterTransferLog(clsBankClient DestinationClient, double TransferAmount) {

		string Line = _PrepareTransferLogRecord(DestinationClient, TransferAmount);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << Line << endl;
			MyFile.close();
		}
	}


	struct strTransferLogRecord;
	static strTransferLogRecord _ConvertLineToTransferStructure(string TransferLine,string Seperator = "#//#") {

		vector <string> vTransferLogString = clsString::Split(TransferLine, Seperator);

		strTransferLogRecord strTransferLog;

		strTransferLog.DateTime = vTransferLogString[0];
		strTransferLog.SenderAccountNumber = vTransferLogString[1];
		strTransferLog.RecieverAccountNumber = vTransferLogString[2];
		strTransferLog.TransferAmount = stod(vTransferLogString[3]);
		strTransferLog.SenderBalanceAfterTransfering = stod(vTransferLogString[4]);
		strTransferLog.RecieverBalanceAfterTransfering = stod(vTransferLogString[5]);
		strTransferLog.Username = vTransferLogString[6];
		return strTransferLog;
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber, string AccountNumber, string PinCode, double AccountBalance)
		: clsPerson(FirstName, LastName, Email, PhoneNumber) {

		_Mode = Mode;
		_AccountNumber = AccountNumber;
		SetPinCode(PinCode);
		SetAccountBalance(AccountBalance);
	}


	struct strTransferLogRecord
	{
		string DateTime;
		string SenderAccountNumber;
		string RecieverAccountNumber;
		double TransferAmount;
		double SenderBalanceAfterTransfering;
		double RecieverBalanceAfterTransfering;
		string Username;
	};


	bool isEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber() { // Only Read Proberty

		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {

		_PinCode = PinCode;
	}
	string GetPinCode() {

		return _PinCode;
	}
	__declspec(property(put = SetPinCode, get = GetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance) {

		_AccountBalance = AccountBalance;
	}
	double GetAccountBalance() {

		return _AccountBalance;
	}
	__declspec(property(put = SetAccountBalance, get = GetAccountBalance)) double AccountBalance;

	void SetMarkedToDeleteValue(bool MarkedToDelete) {

		_MarkedForDelete = MarkedToDelete;
	}
	bool GetMarkedToDeleteValue() {

		return _MarkedForDelete;
	}
	__declspec(property(put = SetMarkedToDeleteValue, get = GetMarkedToDeleteValue)) bool MarkedToDelete;


	static clsBankClient Find(string AccountNumber) {

		vector <clsBankClient> vClients = _LoadFileDataToVClientObject();

		for (clsBankClient& BankClient : vClients) {

			if (BankClient.AccountNumber() == AccountNumber) {

				return BankClient;
			}
		}

		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode) {

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (Client.PinCode == PinCode) ?  Client : _GetEmptyClientObject() ;
	}

	static bool isClientExist(string AccountNumber) {

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.isEmpty());
	}
	bool isClientExist() {

		return isClientExist(_AccountNumber);
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {

		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	
	void Deposit(double DepositAmount) {

		_AccountBalance += DepositAmount;
		Save();
	}

	bool Withdraw(double WithdrawAmount) {

		if (WithdrawAmount > AccountBalance)
			return false;

		AccountBalance -= WithdrawAmount;
		Save();
	}

	bool Transfer(double TransferAmount , clsBankClient &DestinationClient) {

		if (_AccountNumber == DestinationClient.AccountNumber())
			return false;

		if (_AccountBalance < TransferAmount)
			return false;

		Withdraw(TransferAmount);
		DestinationClient.Deposit(TransferAmount);
		_RegisterTransferLog(DestinationClient, TransferAmount);
		return true;
	}

	enum enSaveResult { svFailedEmptyObject, svSucceeded , svFailedAccountNumberExists};
	enSaveResult Save() {

		switch (_Mode)
		{
		case clsBankClient::EmptyMode:

			return enSaveResult::svFailedEmptyObject;


		case clsBankClient::UpdateMode:

			_Update();
			return enSaveResult::svSucceeded;


		case clsBankClient::AddNewMode:

			if (isClientExist(_AccountNumber)) {

				return enSaveResult::svFailedAccountNumberExists;
			}

			else {

				_AddNew();

				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
            }
        }
	}

	bool Delete() {

		vector <clsBankClient> _vClients = _LoadFileDataToVClientObject();

		for (clsBankClient& C : _vClients) {

			if (C.AccountNumber() == _AccountNumber) {

				C.MarkedToDelete = true;
				_SaveClientsDataToFile(_vClients);
				*this = _GetEmptyClientObject();
				return true;
			}
		}
	
		return false;
	}

	static vector <clsBankClient> GetClientsList() {

		return _LoadFileDataToVClientObject();
	}

	static double GetTotalBalances() {

		vector <clsBankClient> vClients = _LoadFileDataToVClientObject();

		double TotalBalances = 0;

		for (clsBankClient& C : vClients) {

			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}


	static vector <strTransferLogRecord> GetTransfersLogList() {

		vector <strTransferLogRecord> vTransfers;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open()) {

			strTransferLogRecord TransferTransaction;
			string Line;

			while (getline(MyFile, Line))
			{
				TransferTransaction = _ConvertLineToTransferStructure(Line);
				vTransfers.push_back(TransferTransaction);
			}

			MyFile.close();
		}

		return vTransfers;
	}


};