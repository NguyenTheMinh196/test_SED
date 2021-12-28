#pragma once
#include "Customer.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class GuestAccount : public Customer
{
public:
    GuestAccount();
    GuestAccount(Customer* cus);
    ~GuestAccount();
    string toString();
};

