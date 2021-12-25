#include "DVDs.h"
/*getter*/
string DVDs::getGenres() {
    return this->genres;
}
/*setter*/
void DVDs::setGenres(string genres) {
    this->genres = genres;
}
/*Construtor*/
DVDs::DVDs() {

}
DVDs::DVDs(Item* item) {
    this->setID(item->getID());
    this->setTitle(item->getTitle());
    this->setLoanType(item->getLoanType());
    this->setNumOfCopy(item->getNumOfCopy());
    this->setNumLoanType(item->getNumLoanType());
    this->setRentalType(item->getRentalType());
    this->setStatus(item->getStatus());
    this->setFee(item->getFee());
}
/*Deconstructor*/
DVDs::~DVDs() {

}
/*toString*/
string DVDs::toString() {
    return Item::toString() +
           "Genre: " + this->getGenres() + "\n";
}