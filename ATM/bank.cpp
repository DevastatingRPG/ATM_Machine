#include "bank.h"
using namespace std;

void Customer::insert() {

}

long double Customer::balance() {
    return 0.0;
}

void Customer::withdraw(int mon) {
    if (balance() > mon)
    {
        balup(this-> cno, -mon);
        cout << "The amount to be withdrawn is " << mon << '\n';
        cout << "The balance is: " << balance() << '\n';
    }
    else
    {
        cout << "The account has insufficient balance." << '\n';
    }

}

void Customer::deposit(int mon) {
    balup(this->cno, mon);
    cout << "The amount deposited is: " << mon << '\n';
    cout << "The balance is: " << balance();
}

void Customer::transfer() {

}

void Customer::cardreg() {

}

void File::balup(string cno, int mon) {
    vector<Record>& Data = contain();

    for (Record& rec : Data) {   
        for (string card : rec.cnos) {
            if (card == cno)         
                rec.balance += mon;        
        }
    }

    write(Data);
}

vector<Record>& File::contain() {
    static vector<Record> Data;
    ifstream fin;
    string row;
    string col;

    fin.open("bank.csv", ios::in);
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

void File::write(vector<Record> Data) {
    ofstream fout;
    fout.open("banknew.csv");
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