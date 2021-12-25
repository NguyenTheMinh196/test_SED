#pragma once
#include "Customer.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class VipAccount : public Customer
{
private:
    int reward_point;
public:
	VipAccount();
	VipAccount(Customer* cus);
	~VipAccount();
	string toString();
    void setRewardPoint(int reward_point);
    int getRewardPoint();

};

