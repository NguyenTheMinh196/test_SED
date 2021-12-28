#include "Item.h"
/*getter and setter ID*/
string Item::getID() {
    return this->id;
};
void Item::setID(string ID) {
    this->id = ID;
}
/*getter and setter Title*/
string Item::getTitle() {
    return this->title;
};
void Item::setTitle(string title) {
    this->title = title;
}
/*getter and setter rentalType*/
string Item::getRentalType() {
    return this->rentalType;
};
void Item::setRentalType(string rentalType) {
    this->rentalType = rentalType;
}
/*getter and setter loanType & numLoanType*/
string Item::getLoanType() {
    return this->loanType;
};
void Item::setLoanType(string loanType) {
    this->loanType = loanType;
}
int Item::getNumLoanType() {
    return this->numLoanType;
};
void Item::setNumLoanType(int numLoanType) {
    this->numLoanType = numLoanType;
}
/*getter and setter numOfCopy*/
int Item::getNumOfCopy() {
    return this->numOfCopy;
};
void Item::setNumOfCopy(int numOfCopy) {
    this->numOfCopy = numOfCopy;
}
/*getter and setter fee*/
float Item::getFee() {
    return this->fee;
};
void Item::setFee(float fee) {
    this->fee = fee;
}
/*getter and setter fee*/
bool Item::getStatus() {
    return this->status;
};
void Item::setStatus(bool status) {
    this->status = status;
}
/*sett all*/
void Item::setAll(string id, string title, string rentaltype, int numLoanType, string loanType, int numOfCopy, float fee) {
    this->id = id;
    this->title = title;
    this->rentalType = rentaltype;
    this->numLoanType = numLoanType;
    this->loanType = loanType;
    this->numOfCopy = numOfCopy;
    this->fee = fee;
}

Item::Item() {

}
Item::~Item() {

}

/*Show info*/
string Item::toString() {
    string status = "";
    // check status
    if (this->getStatus()) {
        status = "Availble";
    }
    else {
        status = "Borrowed";
    }
    return "Id: " +
           this->id +
           "\nTitle: " +
           this->getTitle() +
           "\nRental Type: " +
           this->getRentalType() +
           "\nLoan Type: " +
           std::to_string(this->getNumLoanType()) + "-" + this->getLoanType() +
           "\nNumber of Copy: " +
           std::to_string(this->getNumOfCopy()) +
           "\nFee: " +
           std::to_string(this->getFee()) +
           "\nStatus: " + status +'\n';
}






