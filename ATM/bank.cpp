#include "bank.h"
using namespace std;

void Customer::insert() {
    cout<<"Enter the Card Number:"<<'\n';
    cin>>cno;
    cout<<"Enter CVV:"<<'\n';
    cin>>cvv;
    ano = getacc(cno);
}

long double Customer::balance() {
    return 0.0;
}

void Customer::withdraw(int mon) {
    if (balance() > mon){
        balup(this-> ano, -mon);
        cout << "Transaction Successful" << '\n';
    }
    else{
        cout << "The account has insufficient balance." << '\n';
    }

}

void Customer::deposit(int mon) {
    balup(this->ano, mon);
    cout << "Transaction Successful" << '\n';
}

void Customer::transfer() {

}

void Customer::cardreg() {

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
        }           
    }  
}

/*
* Returns csv file Data in a Vector form where each vector element is a 
* Record type with properties ano, cnos, pins, balance
*/
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

/*
* Writes Vector back to bank.csv
*/
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

/*
* Accepts Card number and returns Account number
*/
string File::getacc(string cno) {
    vector<Record>& Data = contain();
    for (Record& rec : Data) {
        for (string card : rec.cnos) {
            if (card == cno)
                return rec.ano;
        }
    }

}
