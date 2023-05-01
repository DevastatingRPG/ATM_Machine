#pragma once
#include <iostream>
using namespace std;

class Customer {
public:
    string cno;
    char cvv[3];

    void insert();
    long double balance();
    void withdraw(int mon);
    void deposit(int mon);
    void transfer();
    void pingen();
    
};

void edit(string cno, int mon);
