// bank.h

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Record {
    string ano;
    vector<string> cnos;
    vector<string> pins;
    long int balance{ 0 };
};

class File {
public:
    void balup(string ano, long int mon);
    vector<Record>& contain();
    void write(vector<Record> Data);
    string getacc(string cno);
    void cardint(string cno);
    bool acccheck(string ano);
};

class Customer : public File{
public:
    string ano, cno;

    void operations();
    void insert();
    int balance();
    void withdraw(long int mon);
    void deposit(long int mon);
    void transfer(string ano, long int mon); 
};
