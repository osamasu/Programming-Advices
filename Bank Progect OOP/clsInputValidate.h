#pragma once
#include <iostream>
using namespace std;

class clsInputValidate
{

public:

		template <typename T> static T ReadNumber(string Message) {

			T Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail()) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << " \n|Be Sure To Enter A Number ~" + Message;
				cin >> Number;

			}

			return Number;
		}

		template <typename T> static T ReadNumber_InRange(string Message, T From, T To) {

			T Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail() || (Number<From || Number>To)) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			
				cout << "\n|Be Sure To Enter A Number Between [ " << From << " and " << To << " ] ~ ";
				cout << Message;
				cin >> Number;

			}

			return Number;
		}

		template <typename T> static T ReadPositiveNumber(string Message) {

			T Number = 0;
			cout << Message;
			cin >> Number;

			while (cin.fail() || (Number < 0)) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				printf("\n|Be Sure To Enter A Positive Number ~");
				cout << Message;
				cin >> Number;
			}

			return Number;
		}



	static char ReadChar(string Message) {

		char Character;
		cout << Message;

		cin >> Character;
		return Character;
	}

	static string ReadString(string Message = "")
	{
		string Word = "";

		cout << Message;
		getline(cin >> ws, Word);

		return Word;
	}
};