#pragma once


#include<iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{

private:

    enum enMode {EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2};
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;




    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

         return clsBankClient( enMode::UpdateMode,vClientData[0],
         vClientData[1] , vClientData[2],vClientData[3],
         vClientData[4],vClientData[5],stod(vClientData[6]));
        
    }



    static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);
        return stClientRecord;
    }

    struct stTransferLogRecord;

    static stTransferLogRecord _ConvertstTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTransferLogRecord TransferLogRecord;

        vector <string> vTransferLogRecord = clsString::Split(Line, Seperator);

        TransferLogRecord.DateTime = vTransferLogRecord[0];
        TransferLogRecord.SourceAccountNumber = vTransferLogRecord[1];
        TransferLogRecord.DestinationAccountNumber = vTransferLogRecord[2];
        TransferLogRecord.Amount = stof(vTransferLogRecord[3]);
        TransferLogRecord.SrcAccountBalanceAfter = stof(vTransferLogRecord[4]);
        TransferLogRecord.DestinationAccountBalance = stof(vTransferLogRecord[5]);
        TransferLogRecord.UserName = vTransferLogRecord[6];

        return TransferLogRecord;
    }

    
    string _PrepareTransferLogRecord(float Amount ,clsBankClient DestinationClient , string UserName , string Seperator = "#//#")
    {

        string stTranseferLogRecord = "";

        stTranseferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        stTranseferLogRecord += GetAccountNumber() + Seperator;
        stTranseferLogRecord += DestinationClient.GetAccountNumber() + Seperator;
        stTranseferLogRecord += to_string(Amount) + Seperator;
        stTranseferLogRecord += to_string(GetAccountBalance()) + Seperator;
        stTranseferLogRecord += to_string(DestinationClient.GetAccountBalance())+ Seperator;
        stTranseferLogRecord += UserName;

        return stTranseferLogRecord;
    }

   

    void _RegisterTransferLog(float Amount , clsBankClient DestinationClient , string UserName)
    {

        fstream MyFile;
        string  stDataLine = _PrepareTransferLogRecord(Amount , DestinationClient , UserName);

        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }


    static vector <clsBankClient> _LoadCleintsDataFromFile()
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in); //read Mode

        if (MyFile.is_open())
        {
            string Line;
            

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }



    vector <clsBankClient> _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {
            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDeleted() == false) {

                    DataLine = _ConvertClientObjectToLine(C);
                    MyFile << DataLine << endl;

                }
                  

            }

            MyFile.close();
        }

        return vClients;
    }


    void _Update() {

        vector <clsBankClient> _vClients;
        _vClients = _LoadCleintsDataFromFile();

        for (clsBankClient& C : _vClients) {

            if (C.AccountNumber == AccountNumber ) {

                 C = *this; 
                 break;

            }

           
        }

        _SaveCleintsDataToFile(_vClients);
    }

    void _AddDataLineToFile(string stDataLine) {

        fstream MyFile;

        MyFile.open("Clients.txt" , ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    void _AddNew() {
        
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
        
    }


    static clsBankClient _GetEmptyClientObject() {

        return clsBankClient(enMode::EmptyMode , "" , "" , "", "", "", "" , 0);

    }


public :

    struct stTransferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float SrcAccountBalanceAfter;
        float DestinationAccountBalance;
        string UserName;
    };

    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

   

    bool IsEmpty() {

        return (_Mode == enMode::EmptyMode);

    }


    bool MarkedForDeleted() {
        
        return _MarkedForDelete;
       
    }


    void SetAccountNumber(string AccountNumber)
    {
        _AccountNumber = AccountNumber;
    }

    string GetAccountNumber() {
        return _AccountNumber;
    }

    __declspec(property(get = GetAccountNumber, put = SetAccountNumber)) string AccountNumber;



    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode() {
        return _PinCode;
    }

    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;



    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance() {

        return _AccountBalance;

    }

    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    /*No UI Code will be included in this class*/

    //void Print() {
    //    cout << "\nInfo : ";
    //    cout << "\n___________________";
    //    cout << "\nFirstName   : " << FirstName;
    //    cout << "\nLastName    : " << LastName;
    //    cout << "\nFullName    : " << FullName();
    //    cout << "\nEmail       : " << Email;
    //    cout << "\nPhone       : " << Phone;
    //    cout << "\nAcc. Number : " << _AccountNumber;
    //    cout << "\nPassword    : " << _PinCode;
    //    cout << "\nBalance     : " << _AccountBalance;
    //    cout << "\n___________________";
    //}




    static clsBankClient Find(string AccountNumber)
    { 
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
          

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);

                if (Client.AccountNumber == AccountNumber) {

                    MyFile.close();
                    return Client;

                }
                
                
                
            }
            
        }

        return _GetEmptyClientObject();
        
    }

    static clsBankClient Find(string AccountNumber , string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;


            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);

                if (Client.AccountNumber == AccountNumber && Client.PinCode == PinCode) {

                    MyFile.close();
                    return Client;

                }



            }

        }

        return _GetEmptyClientObject();

    }

    enum enSaveResults {svFailedEmptyObject = 0 , svSucceeded = 1 , svFailedAccountNumberExists = 2};

    enSaveResults Save() {

        switch (_Mode) {

             case enMode::EmptyMode:
             {
                 return enSaveResults::svFailedEmptyObject;
                 break;
             }

             case enMode::UpdateMode:
             {
                 _Update();
                 return enSaveResults::svSucceeded;
                 break;
             }

             case enMode::AddNewMode:
             {
                 if (clsBankClient::IsClientExist(_AccountNumber)) {
                     
                     return enSaveResults::svFailedAccountNumberExists;

                 }
                 else {

                     _AddNew();

                     _Mode = enMode::UpdateMode;

                     return enSaveResults::svSucceeded;
                 }

                 break;
             }
        }
    }

    static bool IsClientExist(string AccountNumber) {
        
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return(!Client1.IsEmpty());

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber) {

       return clsBankClient(enMode::AddNewMode , "" , "" , "" , "" , AccountNumber , "" , 0);

    }


    bool Delete() {

       vector <clsBankClient> _vClients;
       _vClients = _LoadCleintsDataFromFile();

       for (clsBankClient& C : _vClients) 
       {
           if (C.GetAccountNumber() == _AccountNumber) {
                
                C._MarkedForDelete = true;
                break;
           }
       }

       _SaveCleintsDataToFile(_vClients);

       *this = _GetEmptyClientObject();

       return true;

    }

   
    static vector <clsBankClient> GetClientsList() {

        return _LoadCleintsDataFromFile();

    }

    static double GetTotalBalances() {

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient &Client : vClients) {
             
            TotalBalances += Client.AccountBalance;

        }

        return TotalBalances;
    }


    void Deposit(double Amount) {

        _AccountBalance += Amount;
        Save();
    }


    bool Withdraw(double Amount) {

        if (Amount > _AccountBalance)
        {
           return false; 
        }
        else 
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
  
    }


     bool Transfer(float Amount , clsBankClient &DestinationClient , string UserName)
     {
        if (Amount > _AccountBalance) 
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);

        _RegisterTransferLog(Amount , DestinationClient , UserName);

         return true;
     }


     static vector <stTransferLogRecord> GetTransferLogList() 
     {
         vector <stTransferLogRecord>  vTransferLogRecord;

         fstream MyFile;

         MyFile.open("TransferLog.txt" , ios::in);

         if (MyFile.is_open()) 
         {
            string Line;

             while (getline(MyFile ,Line) )
             {
                 stTransferLogRecord TransferLogRecord = _ConvertstTransferLogLineToRecord(Line);

                 vTransferLogRecord.push_back(TransferLogRecord);
             }

             MyFile.close();

         }

         return vTransferLogRecord;
     }

    

};

