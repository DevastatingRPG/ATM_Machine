#include "bank.h"
using namespace std;

void Customer::insert() 
{
    cout<<"Enter the Card Number: "<<'\n';
    cin>>cno;
    cout<<"Enter Pin: "<<'\n';
    cin>>pin;
    ano = getacc(cno, pin);
    if (ano == "None")
        cardreg();
    else if (ano == "Invalid")
        cout << "Invalid Pin";
    else
        operations();  
}

void Customer::operations() {
    int choice;
}

long double Customer::balance() 
{
    return 0.0;
}

void Customer::withdraw(long double mon)
{
    if (balance() > mon){
        balup(this-> ano, -mon);
        cout << "Transaction Successful" << '\n';
    }
    else{
        cout << "Insufficient Balance." << '\n';
    }

}

void Customer::deposit(long double mon)
{
    balup(this->ano, mon);
    cout << "Transaction Successful" << '\n';
}

void Customer::transfer(string ano, long double mon)
{
    if(balance()>mon)
    {
        balup(this->ano,-mon);
        balup(ano,mon);
        cout << "Transaction Successful" << '\n';
    }
    else
    {
        cout << "Insufficient Balance." << '\n';
    }
}

void File::cardreg(string cno) {
    int ans,flag=0;
    string accno,npin,rpin;
    vector<Record>& Data = contain();
    
        cout << "Card Number not Found\n";
        cout << "Do you want to register your card in this system? (press 1 for YES and 2 for NO";
        cin >> ans;
        if (ans == 1)
        {
            cout << "Please Enter Your Account Number: ";
            cin >>accno;
            while (flag == 0)
            {
                ans = 0;
                if (ans > 1) cout << "Both pins should be same.\n Try Again";
                cout << "Set a pin: ";
                cin >> npin;
                cout << "Confirm your pin: ";
                cin >> rpin;
                if (npin == rpin) flag = 1;
                ans++;
            }
            for (Record& rec : Data)
            {
                if(rec.ano == accno)
                {
                    rec.cnos.push_back(cno);
                    rec.pins.push_back(rpin);
                    write(Data);
                    break;
                }
            }
        }
        else cout << "Thank you\n";
        
    }

/*
* Updates Balance of entered Account number by entered amount
*/
void File::balup(string ano, long double mon) 
{
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
void File::write(vector<Record> Data) 
{
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
string File::getacc(string cno, string pin) 
{
    vector<Record>& Data = contain();
    for (Record& rec : Data) {
        for (int i = 0; i < rec.cnos.size(); i++) {
            if (rec.cnos[i] == cno) {
                if (rec.pins[i] == pin)
                    return rec.ano;
                else
                    return "Invalid";
            }
        }
    }
    return "None";

}
