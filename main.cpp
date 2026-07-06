#include <iostream>
#include "Bank.h"
using namespace std;

int main()
{
    Bank bank;
    bank.loadFromFile();

    int choice=0;

    while(choice!=7)
    {
        cout<<"\n BANK MANAGEMENT SYSTEM \n";
        cout<<"1. Create Account\n";
        cout<<"2. Deposit Money\n";
        cout<<"3. Withdraw Money\n";
        cout<<"4. Search Account\n";
        cout<<"5. Display All Accounts\n";
        cout<<"6. Delete Account\n";
        cout<<"7. Exit\n";
        cout<<"Choice: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
        {
            int no;
            string name,type;
            double bal;

            cout<<"Account Number: ";
            cin>>no;
            cout<<"Holder Name: ";
            cin>>name;
            cout<<"Initial Balance: ";
            cin>>bal;
            cout<<"Type: ";
            cin>>type;

            bank.createAccount(no,name,bal,type);
            break;
        }

        case 2:
        {
            int no;
            double amt;
            cout<<"Account Number: ";
            cin>>no;
            cout<<"Amount: ";
            cin>>amt;
            bank.depositMoney(no,amt);
            break;
        }

        case 3:
        {
            int no;
            double amt;
            cout<<"Account Number: ";
            cin>>no;
            cout<<"Amount: ";
            cin>>amt;
            bank.withdrawMoney(no,amt);
            break;
        }

        case 4:
        {
            int no;
            cout<<"Account Number: ";
            cin>>no;
            bank.searchAccount(no);
            break;
        }

        case 5:
            bank.displayAllAccounts();
            break;

        case 6:
        {
            int no;
            cout<<"Account Number: ";
            cin>>no;
            bank.deleteAccount(no);
            break;
        }

        case 7:
            cout<<"Goodbye!"<<endl;
            break;

        default:
            cout<<"Invalid choice."<<endl;
        }
    }
}
