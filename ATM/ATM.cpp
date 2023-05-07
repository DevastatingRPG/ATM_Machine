// ATM.cpp

#include "bank.h"
using namespace std;

int main() {
    cout<<"Welcome \n";
    bool stop{ 0 };
    while (not stop) {
        Customer cust;
        cust.insert();
        cout << "Do you want to exit ? (0.Continue 1.Exit): ";
        cin >> stop;
    }   
    cout << "\nThank you";
    return 0;
}
