#include "Bank.h"
#include <iostream>
using namespace std;

void Bank::saveToFile()
{
    ofstream file("accounts.txt");

    for(Account &acc:accounts)
    {
        file<<acc.getAccountNumber()<<" "
            <<acc.getHolderName()<<" "
            <<acc.getBalance()<<" "
            <<acc.getAccountType()<<endl;
    }

    file.close();
}

void Bank::loadFromFile()
{
    ifstream file("accounts.txt");

    int no;
    string holder;
    double bal;
    string type;

    while(file>>no>>holder>>bal>>type)
    {
        accounts.push_back(Account(no,holder,bal,type));
    }

    file.close();
}

void Bank::createAccount(int accNo,string holder,double balance,string type)
{
    for(Account &acc:accounts)
    {
        if(acc.getAccountNumber()==accNo)
        {
            cout<<"Account number already exists."<<endl;
            return;
        }
    }

    accounts.push_back(Account(accNo,holder,balance,type));
    saveToFile();
    cout<<"Account created successfully."<<endl;
}

void Bank::depositMoney(int accNo,double amount)
{
    for(Account &acc:accounts)
    {
        if(acc.getAccountNumber()==accNo)
        {
            acc.deposit(amount);
            saveToFile();
            cout<<"Money deposited successfully."<<endl;
            return;
        }
    }
    cout<<"Account not found."<<endl;
}

void Bank::withdrawMoney(int accNo,double amount)
{
    for(Account &acc:accounts)
    {
        if(acc.getAccountNumber()==accNo)
        {
            if(acc.withdraw(amount))
            {
                saveToFile();
                cout<<"Money withdrawn successfully."<<endl;
            }
            else
                cout<<"Insufficient balance."<<endl;
            return;
        }
    }
    cout<<"Account not found."<<endl;
}

void Bank::searchAccount(int accNo)
{
    for(Account &acc:accounts)
    {
        if(acc.getAccountNumber()==accNo)
        {
            acc.display();
            return;
        }
    }
    cout<<"Account not found."<<endl;
}

void Bank::displayAllAccounts()
{
    if(accounts.empty())
    {
        cout<<"No accounts found."<<endl;
        return;
    }

    for(Account &acc:accounts)
    {
        acc.display();
        cout<<" Account displayed"<<endl;
    }
}

void Bank::deleteAccount(int accNo)
{
    for(size_t i=0;i<accounts.size();i++)
    {
        if(accounts[i].getAccountNumber()==accNo)
        {
            accounts.erase(accounts.begin()+i);
            saveToFile();
            cout<<"Account deleted successfully."<<endl;
            return;
        }
    }
    cout<<"Account not found."<<endl;
}
