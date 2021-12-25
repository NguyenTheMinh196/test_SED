#include "GuestAccount.h"
GuestAccount::GuestAccount() {

}
GuestAccount::GuestAccount(Customer* cus) {
    this->id = cus->getID();
    this->address = cus->getAdress();
    this->name = cus->getName();
    this->phone = cus->getPhone();
    this->numOfRentals = cus->getnumOfRentals();
    this->customerType = cus->getcustomerType();
    this->listOfRentals = cus->getListOfRentals();
}
GuestAccount::~GuestAccount() {

}
string GuestAccount::toString() {
    return Customer::toString();
}