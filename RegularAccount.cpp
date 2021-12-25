#include "RegularAccount.h"
RegularAccount::RegularAccount() {

}
RegularAccount::RegularAccount(Customer* cus) {
    this->id = cus->getID();
    this->address = cus->getAdress();
    this->name = cus->getName();
    this->phone = cus->getPhone();
    this->numOfRentals = cus->getnumOfRentals();
    this->customerType = cus->getcustomerType();
    this->listOfRentals = cus->getListOfRentals();
}
RegularAccount::~RegularAccount() {

}
string RegularAccount::toString() {
    cout << "REGULAR ACCOUNT" << endl;
    return Customer::toString();
}