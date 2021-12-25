#include "MovieRecords.h"
/*getter*/
string MovieRecords::getGenres() {
    return this->genres;
}
/*setter*/
void MovieRecords::setGenres(string genres) {
    this->genres = genres;
}
/*Construtor*/
MovieRecords::MovieRecords() {

}
MovieRecords::MovieRecords(Item *item) {
    this->setID(item->getID());
    this->setTitle(item->getTitle());
    this->setLoanType(item->getLoanType());
    this->setNumOfCopy(item->getNumOfCopy());
    this->setNumLoanType(item->getNumLoanType());
    this->setFee(item->getFee());
    this->setRentalType(item->getRentalType());
    this->setStatus(item->getStatus());
}
/*Deconstructor*/
MovieRecords::~MovieRecords() {

}
/*toString*/
string MovieRecords::toString() {
    return Item::toString()+
           "Genre: " + this->getGenres() + "\n";
}