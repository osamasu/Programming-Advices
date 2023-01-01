#pragma once
#include "clsPerson.h"
#include "Global.h"
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsUtili.h"
#include "clsDate.h"

using namespace std;

class clsBankUser : public clsPerson
{

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;


    static clsBankUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData = clsString::Split(Line, Seperator);

        return clsBankUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4], clsUtili::DecryptText(vUserData[5]), stoi(vUserData[6]));
    }

    static string _ConverUserObjectToLine(clsBankUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.PhoneNumber + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtili::EncryptText(User.Password) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;
    }

    static  vector <clsBankUser> _LoadUsersDataFromFile()
    {
        vector <clsBankUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);// read Mode

        if (MyFile.is_open())
        {
            string Line;
            
            while (getline(MyFile, Line))
            {
                clsBankUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();
        }

        return vUsers;
    }

    static void _SaveUsersDataToFile(vector <clsBankUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankUser &U : vUsers)
            {
                if (U.MarkForDelete == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsBankUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsBankUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    static clsBankUser _GetEmptyUserObject()
    {
        return clsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }


    struct strLoginRegisterRecord;
    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateFullTimeInString() + Seperator;
        LoginRecord += UserName + Seperator;
        LoginRecord += clsUtili::EncryptText(Password) + Seperator;
        LoginRecord += to_string(Permissions);
        return LoginRecord;
    }
    static strLoginRegisterRecord _ConvertLineToLoginRegisterStructure(string LineOfData, string Seperator = "#//#") {

        vector <string> vStringLoginRe = clsString::Split(LineOfData, Seperator);

        strLoginRegisterRecord LoginRegister;
        LoginRegister.DateTime = vStringLoginRe[0];
        LoginRegister.UserName = vStringLoginRe[1];
        LoginRegister.Password = clsUtili::DecryptText(vStringLoginRe[2]);
        LoginRegister.Permissions = stoi(vStringLoginRe[3]);

        return LoginRegister;
    }

public:


    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegisters = 128
    };

    struct strLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

    clsBankUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsBankUser Find(string UserName)
    {
        vector <clsBankUser> vUsers = _LoadUsersDataFromFile();

        for (clsBankUser& U : vUsers) {

            if (U.UserName == UserName) {

                return U;
            }
        }

        return _GetEmptyUserObject();
    }

    static clsBankUser Find(string UserName, string Password)
    {
        clsBankUser User = clsBankUser::Find(UserName);

        return (User.Password == Password) ? User : _GetEmptyUserObject();
    }

    void SetMarkForDelete(bool MarkForDelete) {

        _MarkedForDelete = MarkForDelete;
    }
    bool GetMarkedForDeleted()
    {
        return _MarkedForDelete;
    }
    __declspec(property(get = GetMarkedForDeleted, put = SetMarkForDelete)) bool MarkForDelete;

    enum enSaveResults { svFailedEmptyObject, svFailedUserExist, svSuccessed };

    bool Delete() {

        if (_UserName == "Admin")
            return false;

        vector <clsBankUser> vUsers = _LoadUsersDataFromFile();

        for (clsBankUser& U : vUsers) {

            if (U.UserName == _UserName) {

                U.SetMarkForDelete(true);
                _SaveUsersDataToFile(vUsers);
                *this = _GetEmptyUserObject();
                return true;
            }
        }

        return false;
    }

    enSaveResults Save() {

        switch (_Mode)
        {
        case clsBankUser::EmptyMode:

            if (IsEmpty()) {

                return enSaveResults::svFailedEmptyObject;
            }
            break;

        case clsBankUser::UpdateMode:

            _Update();
            return enSaveResults::svSuccessed;

        case clsBankUser::AddNewMode:

            if (IsUserExist(_UserName)) {

                return enSaveResults::svFailedUserExist;
            }

            _AddNew();
            _Mode = enMode::UpdateMode;
            return enSaveResults::svSuccessed;
        }
    }

    static bool IsUserExist(string UserName)
    {
        clsBankUser User = clsBankUser::Find(UserName);
        return (!User.IsEmpty());
    }



    static clsBankUser GetAddNewUserObject(string UserName)
    {
        return clsBankUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsBankUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        return (this->Permissions == enPermissions::eAll) ? true : ((Permission & this->Permissions) == Permission);
    }


    void RegisterLogIn()
    {

        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }


    static vector <strLoginRegisterRecord> GetLoginRegistersList() {

        vector <strLoginRegisterRecord> vLoginRegister;

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);

        if (MyFile.is_open()) {

            string LineOfRecord;
            strLoginRegisterRecord LoginRegister;

            while (getline(MyFile, LineOfRecord))
            {
                LoginRegister = _ConvertLineToLoginRegisterStructure(LineOfRecord);
                vLoginRegister.push_back(LoginRegister);
            }
            MyFile.close();
        }

        return vLoginRegister;
    }


};

