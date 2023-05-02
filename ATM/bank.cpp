#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "bank.h"
using namespace std;

struct Record {
    string ano;
    vector<string> cnos;
    vector<string> pins;
    long double balance{ 0.0 };
};

void Customer::insert() {

}

long double Customer::balance() {
    return 0.0;
}

void Customer::withdraw(int mon) {
    if (balance() > mon)
    {
        edit(this-> cno, -mon);
        cout << "The amount to be withdrawn is " << mon << '\n';
        cout << "The balance is: " << balance() << '\n';
    }
    else
    {
        cout << "The account has insufficient balance." << '\n';
    }

}

void Customer::deposit(int mon) {
    edit(this->cno, mon);
    cout << "The amount deposited is: " << mon << '\n';
    cout << "The balance is: " << balance();
}

void Customer::transfer() {

}

void Customer::cardreg() {

}

void edit(string cno, int mon) {
    fstream fin, fout;

    fin.open("bank.csv", ios::in);
    fout.open("banknew.csv", ios::out);
    string row;
    string col;

    while (getline(fin, row)) {
        Record rec;
        stringstream conv(row);
        bool found{ 0 };

        getline(conv, col, ',');
        rec.ano = col;

        getline(conv, col, '"');
        getline(conv, col, '"');
        stringstream cards(col);
        string card;
        while (getline(cards, card, ',')) {
            card.erase(remove(card.begin(), card.end(), ' '), card.end());
            cout << card << endl;
            if (card == cno)
                found = 1;
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
        if (found) {
            col.erase(remove(col.begin(), col.end(), ' '), col.end());
            stringstream bal;
            int size;
            bal << col;
            bal >> rec.balance;
            
            rec.balance += mon;
            fout << rec.ano << ", \"";

            size = rec.cnos.size();
            for (int i = 0; i < size; i++) {
                fout << rec.cnos[i];
                if (i != size - 1)
                    fout << ", ";
            }
            fout << "\",\"";

            size = rec.pins.size();
            for (int i = 0; i < size; i++) {
                fout << rec.pins[i];
                if (i != size - 1)
                    fout << ", ";
            }
            fout << "\", ";

            fout << rec.balance << endl;
        }
        else
            fout << row << endl;
        
    }

    fin.close();
    fout.close();
    remove("bank.csv");
    rename("banknew.csv", "bank.csv");
}
