#include "Games.h"
Games::Games() {

}
Games::Games(Item* item) {
    this->setID(item->getID());
    this->setTitle(item->getTitle());
    this->setLoanType(item->getLoanType());
    this->setNumOfCopy(item->getNumOfCopy());
    this->setNumLoanType(item->getNumLoanType());
    this->setRentalType(item->getRentalType());
    this->setStatus(item->getStatus());
    this->setFee(item->getFee());
}
Games::~Games() {

}