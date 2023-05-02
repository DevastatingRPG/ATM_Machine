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
            remove(card.begin(), card.end(), ' ');
            if (card == cno)
                found = 1;
            rec.cnos.push_back(card);
        }
        getline(conv, col, ',');

        getline(conv, col);
        if (found) {
            stringstream bal;
            bal << col;
            bal >> rec.balance;
            rec.balance += mon;
            fout << rec.ano << ",\"";

            int size = rec.cnos.size();
            for (int i = 0; i < size; i++) {
                fout << rec.cnos[i];
                if (i != size - 1)
                    fout << ", ";
            }
            fout << "\",";

            fout << rec.balance << endl;
        }
        else
            fout << row << endl;
        
    }

}
