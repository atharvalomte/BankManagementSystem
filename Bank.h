#ifndef BANK_H
#define BANK_H

#include <vector>
#include <fstream>
#include "Account.h"
using namespace std;

class Bank
{
private:
    vector<Account> accounts;

public:
    void createAccount(int,string,double,string);
    void depositMoney(int,double);
    void withdrawMoney(int,double);
    void searchAccount(int);
    void displayAllAccounts();
    void deleteAccount(int);

    void saveToFile();
    void loadFromFile();
};

#endif
