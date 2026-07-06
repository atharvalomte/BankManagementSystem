#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account
{
private:
    int accountNumber;
    string accountHolder;
    double balance;
    string accountType;

public:
    Account(int accNo,string holder,double bal,string type);

    void deposit(double amount);
    bool withdraw(double amount);
    void display() const;

    int getAccountNumber() const;
    string getHolderName() const;
    double getBalance() const;
    string getAccountType() const;
};

#endif
