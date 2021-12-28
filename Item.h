#pragma once
#include <iostream>
#include <string>
using namespace std;
class Item
{
protected:
    string id;
    string title;
    string  rentalType;
    int numLoanType;
    string loanType;
    int numOfCopy;
    float fee;
    bool status; // true if is available and false is borrowed
public:
    /*Constructor*/
    Item();
    /*Deconstructor*/
    ~Item();

    /*getter*/
    string getID();
    string getTitle();
    string getRentalType();
    int getNumLoanType();
    string getLoanType();
    int getNumOfCopy();
    float getFee();
    bool getStatus();

    /*setter*/
    void setID(string id);
    void setTitle(string title);
    void setRentalType(string rentalType);
    void setNumLoanType(int loanType);
    void setLoanType(string numLoanType);
    void setNumOfCopy(int numOfCopy);
    void setFee(float fee);
    void setStatus(bool status);
    void setAll(string id, string titel, string rentaltype, int numLoanType, string loanType, int numOfCopy, float fee);

    /*show item information*/
    virtual string toString();
};

