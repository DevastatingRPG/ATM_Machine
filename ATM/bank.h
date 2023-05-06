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
    void balup(string ano, long double mon);
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
    long double balance();
    void withdraw(long double mon);
    void deposit(long double mon);
    void transfer(string ano, long double mon); 
};
