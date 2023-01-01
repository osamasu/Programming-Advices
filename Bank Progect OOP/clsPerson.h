#pragma once
#include <iostream>
using namespace std;

class clsPerson
{

private:

	string _FirstName;
	string _LastName;
	string _Email;
	string _PhoneNumber;

public:

	clsPerson(string FirstName, string LastName, string Email, string PhoneNumber) {

		SetFirstName(FirstName);
		SetLastName(LastName);
		SetEmail(Email);
		SetPhoneNumber(PhoneNumber);
	}

	void SetFirstName(string FirstName) {

		_FirstName = FirstName;
	}
	string GetFirstName() {

		return _FirstName;
	}
	__declspec(property(put = SetFirstName, get = GetFirstName)) string FirstName;

	void SetLastName(string LastName) {

		_LastName = LastName;
	}
	string GetLastName() {

		return _LastName;
	}
	__declspec(property(put = SetLastName, get = GetLastName)) string LastName;

	void SetEmail(string Email) {

		_Email = Email;
	}
	string GetEmail() {

		return _Email;
	}
	__declspec(property(put = SetEmail, get = GetEmail)) string Email;

	void SetPhoneNumber(string PhoneNumber) {

		_PhoneNumber = PhoneNumber;
	}
	string GetPhoneNumber() {

		return _PhoneNumber;
	}
	__declspec(property(put = SetPhoneNumber, get = GetPhoneNumber)) string PhoneNumber;

	string FullName()
	{
		return _FirstName + " " + _LastName;
	}
};

