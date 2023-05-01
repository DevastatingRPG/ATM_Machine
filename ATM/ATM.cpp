#include <iostream>
#include "bank.h"
using namespace std;

int main() {
    Customer c;
    c.cno = "69740";
    edit(c.cno, 20);
    return 0;
}