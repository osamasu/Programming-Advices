#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <iomanip>
#include <vector>
#include <fstream>
#include "clsInputValidate.h"
using namespace std;

class clsUtili;

class clsUtili
{


public :


	const double PI = 3.141592653589793238462643383279502884197;

	static void  Srand()
	{
		//Seeds the random number generator in C++, called only once
		srand((unsigned)time(NULL));
	}

		static short GetRandomNumber(short From, short To)
		{
			return  rand() % (To - From + 1) + From;
		}

		enum enCharType {
			SamallLetter = 1, CapitalLetter = 2,
			Digit = 3, MixChars = 4, SpecialCharacter = 5
		};

	


		class clsMatrix {

		public:

			static void FillMatrix_WithRandomNumbers(short Array[3][3], short Rows, short Cols)
			{
				for (int i = 0; i < Rows; i++)
				{
					for (short j = 0; j < Cols; j++) {

						Array[i][j] = GetRandomNumber(1, 100);
					}

				}
			}

			static void PrintMatrix(short arr[3][3], short Rows, short Cols) {

				for (short i = 0; i < Rows; i++) {

					for (short j = 0; j < Cols; j++) {

						cout << setw(3); printf("%0*d\t", 2, arr[i][j]);
					}
					cout << endl;
				}
			}

			static void FillMatrixWithOrderedNumbers(short arr[3][3], short Rows, short Cols)
			{

				short Counter = 0;
				for (short i = 0; i < Rows; i++)
				{
					for (short j = 0; j < Cols; j++)
					{
						Counter++;
						arr[i][j] = Counter;
					}
				}
			}

			static short RowsSum(short arr[3][3], short Rows, short Cols) {

				int RowsSum = 0;

				for (short j = 0; j < Cols; j++) {

					RowsSum += arr[Rows][j];
				}

				return RowsSum;
			}

			static 	short ColumsSum(short arr[3][3], short Rows, short Cols) {

				int SumColum = 0;

				for (short j = 0; j < Rows; j++) {

					SumColum += arr[j][Cols];

				}

				return SumColum;
			}

			static int MatrixSum(short Marr[3][3], short Rows, short Cols) {

				int MatrixSum = 0;

				for (short i = 0; i < Rows; i++) {

					for (short j = 0; j < Cols; j++) {

						MatrixSum += Marr[i][j];
					}
				}

				return MatrixSum;
			}

			static short Count_NeededNumber_InMatrix(short arr[3][3], short NumberToCount, short Rows, short Cols) {

				short Count_RepeatedNumber = 0;

				for (short i = 0; i < Rows; i++) {

					for (short j = 0; j < Cols; j++) {

						(arr[i][j] == NumberToCount) ? Count_RepeatedNumber++ : 0;
					}
				}

				return Count_RepeatedNumber;

			}

			static bool IsNumber_InMatrix(short marr[3][3], short NumberToCheck, short Rows, short Cols) {

				for (short i = 0; i < Rows; i++) {

					for (short j = 0; j < Cols; j++) {

						if (marr[i][j] == NumberToCheck)
							return true;
					}
				}
				return false;
			}
		};
		clsMatrix Matricies;


		class clsArrays {
			
		public:

			static void FillArrayWithRandomNumbers(short Array[100], short &arrLength , short From , short To, bool WithoutReading = true)
			{

				if (!WithoutReading) {

					arrLength = clsInputValidate::ReadNumber_InRange <short> ("How Many Elements Do You Want ,From [ 1 to 100 ] ?    |~ ", 1, 100);
				}

				for (int i = 0; i < arrLength; i++)
				{
					Array[i] = GetRandomNumber(From, To);
				}
			}
			static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
			{
				for (int i = 0; i < arrLength; i++)
					arr[i] = GenerateWord(CharType, Wordlength);

			}
			static void FillArrayWithRandomKeys(string arr[100], short arrLength, enCharType CharType)
			{
				for (int i = 0; i < arrLength; i++)
					arr[i] = GenerateKey(CharType);
			}

			static short FindNumberPosition_InArray(short arr[100], short arrLength, short SearchFor)
			{
				for (int i = 0; i < arrLength; i++)
				{
					if (arr[i] == SearchFor)
						return i;
				}

				return -1;
			}

			static bool IsNumber_InArray(short arr[100], short arrLength, short NumberToCheck)
			{
				return (FindNumberPosition_InArray(arr, arrLength, NumberToCheck) != -1);
			}

			static void AddArrayElement_InArray(int NumberToAdd, int ArrayDistination[100], short& arrDistinationLength)
			{
				arrDistinationLength++;
				ArrayDistination[arrDistinationLength - 1] = NumberToAdd;
			}
			static void AddArrayElement_InArray(short NumberToAdd, short ArrayDistination[100], short& arrDistinationLength)
			{
				arrDistinationLength++;
				ArrayDistination[arrDistinationLength - 1] = NumberToAdd;
			}

			static void InputUserNumbers_InArray(int arr[100], short& arrLength)
			{
				char AddMore = ' ';

				do
				{
					AddArrayElement_InArray(clsInputValidate::ReadNumber <int> ("Please enter a Number ? | "), arr, arrLength);

					AddMore = ReadChar("Press [y] For Add More Elements  Or Any Key If You Finish   |"); cout << "\n\n";

				} while (AddMore == 'Y' || AddMore == 'y');
			}
			static void CopyArray(short SourceArray[100], short ArrayDistination[100], short arrSourceLength, short& arrDistinationLength)
			{
				for (int i = 0; i < arrSourceLength; i++)
				{
					AddArrayElement_InArray(SourceArray[i], ArrayDistination, arrDistinationLength);
				}
			}

			static void ReadArray(int arr[100], short& arrLength)
			{

				arrLength = clsInputValidate::ReadPositiveNumber <short> ("Enter Number Of Elements :\n");

				cout << "\nEnter array elements :\n";

				for (int i = 0; i < arrLength; i++)
				{
					arr[i] = clsInputValidate::ReadNumber <int> ("Element [" + to_string(i + 1) + "]:");
				}
			}

			static void PrintArray(int Arr[], short arrLength)
			{
				for (int i = 0; i < arrLength; i++)
				{
					cout << Arr[i] << " ";
				}
				cout << endl;
			}
			static void PrintArray(short Arr[], short arrLength)
			{
				for (int i = 0; i < arrLength; i++)
				{
					cout << Arr[i] << " ";
				}
				cout << endl;
			}

			static  void ShuffleArray(short arr[100], short arrLength)
			{

				for (int i = 0; i < arrLength; i++)
				{
					Swap <short> (arr[GetRandomNumber(1, arrLength) - 1], arr[GetRandomNumber(1, arrLength) - 1]);
				}

			}
			static  void ShuffleArray(string arr[100], int arrLength)
			{

				for (int i = 0; i < arrLength; i++)
				{
					Swap <string>(arr[GetRandomNumber(1, arrLength) - 1], arr[GetRandomNumber(1, arrLength) - 1]);
				}

			}
		};
		clsArrays Arrays;
	

		class clsFiles {

		public:

			static void PrintFileContenet(string FileName) {

				fstream MyFile; string Line;

				MyFile.open(FileName, ios::in); //read mode

				if (MyFile.is_open()) {

					while (getline(MyFile, Line)) {

						cout << Line << endl;
					}
					MyFile.close();
				}
			}

			static void LoadDataFromFileToVector(string FileName, vector <string>& vFileContenet) {

				fstream MyFile; string Line;

				MyFile.open(FileName, ios::in);

				if (MyFile.is_open()) {

					while (getline(MyFile, Line)) {

						vFileContenet.push_back(Line);
					}

					MyFile.close();
				}
			}

			static void SaveVectorToFile(string FileName, vector <string>& vFileContenet) {

				fstream MyFile;

				MyFile.open(FileName, ios::out);

				if (MyFile.is_open()) {

					for (string& Line : vFileContenet) {

						if (Line != "") {

							MyFile << Line << endl;
						}
					}
					MyFile.close();
				}
			}

			static void DeleteRecordFromFile(string MyFile, string RecordToDelete) {

				vector <string> vFileContenet;
				LoadDataFromFileToVector(MyFile, vFileContenet);

				for (string& Line : vFileContenet) {

					if (Line == RecordToDelete) {
						Line = "";
					}
				}
				SaveVectorToFile(MyFile, vFileContenet);
			}

			static void UpdateRecordInFile(string FileName, string RecordToReplace, string UpdateTo) {

				vector <string> vFileContenet;
				LoadDataFromFileToVector(FileName, vFileContenet);

				for (string& Line : vFileContenet) {

					if (Line == RecordToReplace) {

						Line = UpdateTo;
					}
				}
				SaveVectorToFile(FileName, vFileContenet);
			}

			static void AddDataLineToFile(string FileName, string Line) {

				fstream MyFile;

				MyFile.open(FileName, ios::out | ios::app);

				if (MyFile.is_open()) {

					MyFile << Line << endl;

					MyFile.close();
				}

			}
		};
		clsFiles Files;

	

		static char ReadChar(string Message) {

			char Character;
			cout << Message;

			cin >> Character;
			return Character;
		}

		
		static char GetRandomCharacter(enCharType CharType)
		{

			
			if (CharType == MixChars)
			{
				//Capital/Samll/Digits only
				CharType = (enCharType)GetRandomNumber(1, 3);

			}

			switch (CharType)
			{

			case enCharType::SamallLetter:

				return char(GetRandomNumber(97, 122));
			
			case enCharType::CapitalLetter:
			
				return char(GetRandomNumber(65, 90));
			
			case enCharType::SpecialCharacter:
			
				return char(GetRandomNumber(33, 47));
			
			case enCharType::Digit:
			
				return char(GetRandomNumber(48, 57));
			}
		}
		static  string GenerateWord(enCharType CharType, short Length) {

			string Word;

			for (int i = 1; i <= Length; i++)

			{

				Word = Word + GetRandomCharacter(CharType);

			}
			return Word;
		}

		static int ReverseNumber(int Number)
		{
			short Remainder = 0; int ReversedNumber = 0;
			while (Number > 0)
			{
				Remainder = (Number % 10);
				Number /= 10;

				ReversedNumber = ReversedNumber * 10 + Remainder;
			}

			return ReversedNumber;
		}
		static bool Check_IsPrimeNumber(int Number)
		{

			for (int i = 2; i <= ceil(Number / 2); i++)
			{
				if (Number % i == 0)
					return false;
			}

			return true;
		}
		static bool Check_IsPerfectNumber(int Number)
		{
			int Sum = 0;
			for (int i = 1; i <= ceil(Number / 2); i++)
			{
				if (Number % i == 0)
				{
					Sum += i;
				}
			}

			return (Number == Sum);
		}
		static bool Check_IsPalindromeNumber(int Number)
		{
			return (Number == ReverseNumber(Number));
		}



	


		static string  GenerateKey(enCharType CharType = CapitalLetter)
		{

			string Key = "";


			Key = GenerateWord(CharType, 4) + "-";
			Key = Key + GenerateWord(CharType, 4) + "-";
			Key = Key + GenerateWord(CharType, 4) + "-";
			Key = Key + GenerateWord(CharType, 4);


			return Key;
		}
		static void GenerateKeys(short NumberOfKeys, enCharType CharType)
		{

			for (int i = 1; i <= NumberOfKeys; i++)

			{
				cout << "Key [" << i << "] : ";
				cout << GenerateKey(CharType) << endl;
			}

		}

	
		static string NextLine(short NumberOfLinesToStepUp) {

			string NextLine = "";
			for (short NextLines = 1; NextLines <= NumberOfLinesToStepUp; NextLines++)
				NextLine += "\n";

			return NextLine;

		}

		static string Tabs(short NumberOfTabs) {

			string OrderedTabs = "";

			for (short i = 1; i <= NumberOfTabs; i++)
				OrderedTabs += "\t";

			return OrderedTabs;
		}

		static string  EncryptText(string Text, short EncryptionKey = 19)
		{

			for (int i = 0; i <= Text.length(); i++)
			{

				Text[i] = char((int)Text[i] + EncryptionKey);

			}

			return Text;
		}

		static string  DecryptText(string Text, short EncryptionKey = 19)
		{

			for (int i = 0; i <= Text.length(); i++)
			{

				Text[i] = char((int)Text[i] - EncryptionKey);

			}
			return Text;
		}



		template <typename T> static T Swap(T& FirstNumber, T& SecondNumber) {

			T* Temp = new T;

			*Temp = FirstNumber;
			FirstNumber = SecondNumber;
			SecondNumber = *Temp;

			delete Temp;
		}
};