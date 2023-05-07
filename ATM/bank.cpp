#include "bank.h"
using namespace std;

/*
* Accepts Card Number from user and checks if it exists using getacc(). If it exists, asks for a pin and verifies it, then
* calls operations() if verified.. If it doesn’t exist, asks user if they want to initialize the card to their account.
*/
void Customer::insert() {
    cout << "Enter the Card Number: "<<'\n';
    cin >> cno;
    ano = getacc(cno);
    if (ano == "None")       
        cardint(cno);
    else if (ano == "Invalid")
        cout << "Invalid Pin";
    else
        operations();  
}

/*
* Asks the user for their choice of operations and performs it by calling the respective functions.
*/
void Customer::operations() {
    int choice, money;
    cout << "1.Balance 2.Withdraw 3.Deposit 4.Transfer \n";
    cin >> choice;
    switch(choice) {       
        case 1:
            cout<<"Account balance is : " << balance();
            break;
        case 2: {
            cout << "Enter the amount to be withdrawn : ";
            cin >> money;
            withdraw(money);
            break; }
        case 3:            
            cout<<"Enter the amount to be deposited : ";
            cin>>money;
            deposit(money);
            break;
        case 4: {     
            string ano;
            cout << "Enter the account number of recipient : ";
            cin >> ano;
            cout << "Enter the amount to be transferred : ";
            cin >> money;
            transfer(ano, money);
            break; }
        default:
            cout<<"Invalid Operation\n";
            break;
    }
}

/*
* Returns Balance of account
*/
int Customer::balance() {
    int balance;
    vector<Record>& Data = contain();
    for (Record rec : Data){
        if (this->ano == rec.ano) {
            balance = rec.balance;
            Data.clear();
            return balance;
        }                      
    }
}

/*
* Withdraws money from account
*/
void Customer::withdraw(int mon) {
    if (balance() > mon && mon % 10 == 0) {
        balup(this-> ano, -mon);
        cout << "Transaction Successful" << '\n';
    }
    else
        cout << "Insufficient Balance or Invalid Denomination." << '\n';
}

/*
* Deposits money into account
*/
void Customer::deposit(int mon) {
    if (mon % 10 != 0)
        cout << "Invalid Denomination \n";
    else {
        balup(this->ano, mon);
        cout << "Transaction Successful" << '\n';
    }    
}

/*
* Transfers money from 1 account to another
*/
void Customer::transfer(string ano, int mon) {
    if(balance() > mon){
        balup(this->ano, -mon);
        balup(ano, mon);
        cout << "Transaction Successful" << '\n';
    }
    else
        cout << "Insufficient Balance." << '\n';
}

/*
* Initializes card by adding it to the account along with a pin
*/
void File::cardint(string cno) {
    bool ans; int flag = 0;
    string accno,npin,rpin;
    vector<Record>& Data = contain();
    cout << "Card not Found\n";
    cout << "Do you want to Initialize your card ? (0 : NO, 1 : YES) : ";
    cin >> ans;
    if (ans == 1)
    {
        cout << "Please Enter Your Account Number: ";
        cin >>accno;
        while (flag != 1) {           
            if (flag == 2) 
                cout << "Both pins should be same.\n Try Again";
            cout << "Set a pin: ";
            cin >> npin;
            cout << "Confirm your pin: ";
            cin >> rpin;
            if (npin == rpin)
                flag = 1;
            else
                flag = 2;
        }
            
        for (Record& rec : Data) {  
            if(rec.ano == accno) {  
                rec.cnos.push_back(cno);  
                rec.pins.push_back(rpin);    
                write(Data);
                Data.clear();
                break;
            }   
        }
        Data.clear();
    }
    else cout << "Thank you\n";       
}

/*
* Updates Balance of entered Account number by entered amount
*/
void File::balup(string ano, int mon) {
    vector<Record>& Data = contain();
    for (Record& rec : Data) { 
        if (rec.ano == ano) {
            rec.balance += mon;        
            write(Data);
            Data.clear();
            break;
        }           
    }  
}

/*
* Returns csv file Data in a Vector form where each vector element is a 
* Record type with properties ano, cnos, pins, balance
*/
vector<Record>& File::contain() 
{
    static vector<Record> Data;
    ifstream fin;
    string row;
    string col;

    fin.open("bank.csv", ios::in);
    while (getline(fin, row)) {
        Record rec;
        stringstream conv(row);

        getline(conv, col, ',');
        rec.ano = col;

        getline(conv, col, '"');
        getline(conv, col, '"');
        stringstream cards(col);
        string card;
        while (getline(cards, card, ',')) {
            card.erase(remove(card.begin(), card.end(), ' '), card.end());
            rec.cnos.push_back(card);
        }
        getline(conv, col, '"');

        getline(conv, col, '"');
        stringstream pins(col);
        string pin;
        while (getline(pins, pin, ',')) {
            pin.erase(remove(pin.begin(), pin.end(), ' '), pin.end());
            rec.pins.push_back(pin);
        }
        getline(conv, col, ',');

        getline(conv, col);
        col.erase(remove(col.begin(), col.end(), ' '), col.end());
        stringstream bal(col);
        bal >> rec.balance;
        Data.push_back(rec);
    }
    return Data;
}

/*
* Writes Vector back to bank.csv
*/
void File::write(vector<Record> Data) {
    ofstream fout;
    fout.open("banknew.csv", ios::out);
    for (Record rec : Data) {
        int i;
        int size;
        fout << rec.ano << ", \"";

        size = rec.cnos.size();
        for (i = 0; i < size; i++) {
            fout << rec.cnos[i];
            if (i != size - 1) 
                fout << ", ";        
        }
        fout << "\", \"";

        size = rec.pins.size();
        for (i = 0; i < size; i++) {
            fout << rec.pins[i];
            if (i != size - 1)
                fout << ", ";
        }
        fout << "\", ";

        fout << rec.balance << endl;
    }
    fout.close();

    remove("bank.csv");
    rename("banknew.csv", "bank.csv");
}

/*
* Accepts Card number and returns Account number
*/
string File::getacc(string cno) {
    string ano;
    vector<Record>& Data = contain();   
    for (Record& rec : Data) {
        for (int i = 0; i < rec.cnos.size(); i++) {
            if (rec.cnos[i] == cno) {
                cout << "Enter Pin: " << '\n';
                string pin;
                cin >> pin;
                if (rec.pins[i] == pin) {
                    ano = rec.ano;
                    Data.clear();
                    return ano;
                }                                                     
                else
                    return "Invalid";
            }
        }
    }
    Data.clear();
    return "None";
}
