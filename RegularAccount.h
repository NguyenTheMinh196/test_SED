
#pragma once
#include "Customer.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class RegularAccount : public Customer
{
public:
    RegularAccount();
    RegularAccount(Customer* cus);
    ~RegularAccount();
    string toString();

};

