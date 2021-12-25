#include "VipAccount.h"
VipAccount::VipAccount() {

}
VipAccount::VipAccount(Customer *cus) {
    this->id = cus->getID();
    this->address = cus->getAdress();
    this->name = cus->getName();
    this->phone = cus->getPhone();
    this->numOfRentals = cus->getnumOfRentals();
    this->customerType = cus->getcustomerType();
    this->listOfRentals = cus->getListOfRentals();
}
VipAccount::~VipAccount() {

}
string VipAccount::toString() {
    cout << "VIP ACCOUNT" << endl;
    return Customer::toString();
}
void VipAccount::setRewardPoint(int reward_point) {
    this->reward_point = reward_point;
}
int VipAccount::getRewardPoint() {
    return this->reward_point;
}