#include "Account.h"
#include <iostream>
using namespace std;

Account::Account(int accNo,string holder,double bal,string type)
{
    accountNumber=accNo;
    accountHolder=holder;
    balance=bal;
    accountType=type;
}

void Account::deposit(double amount)
{
    if(amount>0) balance+=amount;
}

bool Account::withdraw(double amount)
{
    if(amount<=0 || amount>balance)
        return false;

    balance-=amount;
    return true;
}

void Account::display() const
{
    cout<<"Account Holder : "<<accountHolder<<endl;
    cout<<"Account Number : "<<accountNumber<<endl;
    cout<<"Balance        : "<<balance<<endl;
    cout<<"Account Type   : "<<accountType<<endl;
}

int Account::getAccountNumber() const { return accountNumber; }
string Account::getHolderName() const { return accountHolder; }
double Account::getBalance() const { return balance; }
string Account::getAccountType() const { return accountType; }
