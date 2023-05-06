#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Record {
    string ano;
    vector<string> cnos;
    vector<string> pins;
    long double balance{ 0.0 };
};

class File {
public:
    void balup(string ano, int mon);
    vector<Record>& contain();
    void write(vector<Record> Data);
    string getacc(string cno, string pin);
    void cardreg(string cno);
};

class Customer : public File{
public:
    string ano, cno, pin;

    void operations();
    void insert();
    int balance();
    void withdraw(int mon);
    void deposit(int mon);
    void transfer(string ano, int mon); 
};
