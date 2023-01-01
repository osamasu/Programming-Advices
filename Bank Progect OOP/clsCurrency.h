#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"

class clsCurrency
{
private:

	enum enMode { EmptyMode, UpdateMode };

	enMode _Mode;
	string _Country;
	string _CurrencyName;
	string _CurrencyCode;
	double _CurrencyRate;


	static clsCurrency _ConvertRecordLineToVCurrency(string CurrencyDataLine, string Seperator = "#//#") {

		vector <string> VsCurrency = clsString::Split(CurrencyDataLine, Seperator);

		return clsCurrency(enMode::UpdateMode, VsCurrency[0], VsCurrency[1], VsCurrency[2], stod(VsCurrency[3]));
	}

	static vector <clsCurrency> _LoadCurrenciesInfoFromFileToVCurrency() {

		vector <clsCurrency> vCurrency;

		fstream MyFile;
		MyFile.open("Curreencies.txt", ios::in);

		if (MyFile.is_open()) {

			string LineOfData;

			while (getline(MyFile, LineOfData))
			{
				clsCurrency Currency = _ConvertRecordLineToVCurrency(LineOfData);
				vCurrency.push_back(Currency);
			}

			MyFile.close();
		}

		return vCurrency;
	}

	static clsCurrency _GetEmptyCurrancyObject() {

		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static string _ConvertCurrencyObjectToRecordLine(clsCurrency Currency , string Seperator = "#//#") {

		string LineOfData = Currency.Country + Seperator;
		LineOfData += Currency.CurrencyCode + Seperator;
		LineOfData += Currency.CurrencyName + Seperator;
		LineOfData += to_string(Currency.CurrencyRate);

		return LineOfData;
	}

	static void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies) {

		fstream MyFile;
		MyFile.open("Curreencies.txt", ios::out);

		if (MyFile.is_open()) {

			string Line;

			for (clsCurrency& C : vCurrencies) {

				Line = _ConvertCurrencyObjectToRecordLine(C);
				MyFile << Line << endl;
			}

			MyFile.close();
		}
	}

	bool _Update() {

		vector <clsCurrency> vCurrenciesList = _LoadCurrenciesInfoFromFileToVCurrency();

		for (clsCurrency& C : vCurrenciesList) {

			if (C.CurrencyCode == _CurrencyCode) {

				C = *this;
				_SaveCurrenciesDataToFile(vCurrenciesList);
				return true;
			}
		}

		return false;
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, double CurrencyRate) {

		_Mode = Mode;
		_Country = Country;
		_CurrencyName = CurrencyName;
		_CurrencyCode = CurrencyCode;
		_CurrencyRate = CurrencyRate;
	}



	string GetCountry() {

		return _Country;
	}
	__declspec(property(get = GetCountry)) string Country;

	string GetCurrencyName() {

		return _CurrencyName;
	}
	__declspec(property(get = GetCurrencyName)) string CurrencyName;

	string GetCurrencyCode() {

		return _CurrencyCode;
	}
	__declspec(property(get = GetCurrencyCode)) string CurrencyCode;


	void SetCurrencyRate(double CurrencyRate) {

		_CurrencyRate = CurrencyRate;
	}
	double GetCurrencyRate() {

		return _CurrencyRate;
	}
	__declspec(property(put = SetCurrencyRate, get = GetCurrencyRate)) double CurrencyRate;

	bool isEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	static bool isCurrencyExist(string CurrencyCode) {

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return !(Currency.isEmpty());
	}

	static clsCurrency FindByCode(string CurrencyCodeToFind) {

		vector <clsCurrency> vCurrencies = _LoadCurrenciesInfoFromFileToVCurrency();

		CurrencyCodeToFind = clsString::UpperAllString(CurrencyCodeToFind);

		for (clsCurrency& Currancy : vCurrencies) {

			if (Currancy.CurrencyCode == CurrencyCodeToFind)
				return Currancy;
		}

		return _GetEmptyCurrancyObject();
	}
	static clsCurrency FindByCountry(string CurrencyCountryToFind) {

		vector <clsCurrency> vCurrencies = _LoadCurrenciesInfoFromFileToVCurrency();

		CurrencyCountryToFind = clsString::UpperAllString(CurrencyCountryToFind);

		for (clsCurrency& Currancy : vCurrencies) {

			if (clsString::UpperAllString(Currancy.Country) == CurrencyCountryToFind)
				return Currancy;
		}

		return _GetEmptyCurrancyObject();
	}

	static vector < clsCurrency > GetCurranciesList() {

		return _LoadCurrenciesInfoFromFileToVCurrency();
	}

	bool UpdateRate() {

		return _Update();
	}
};

