#pragma once
using namespace std;
#include <string>
#include<iostream>
#include "Item.h"
#include <vector>
class Customer
{
protected:
    string id;
    string name;
    string address;
    string phone;
    int numOfRentals;
    string customerType;
    vector<string> listOfRentals;

    int borrowedDVD;

public:


    string getID();
    string getName();
    string getAdress();
    string getPhone();
    int getnumOfRentals();
    string getcustomerType();
    vector<string> getListOfRentals();

    int getBorrowedDVD();
    void setBorrowedDVD(int numReturn);
    void setBorrowedDVD(bool numReturn);

    void setID(string id);
    void setName(string name);
    void setAddress(string address);
    void setPhone(string phone);
    void setNumOfRentals(int numOfRentals);
    void setcustomerType(string type);
    void setListOfRentals(vector<string> listOfRentals);
    void setAll(string id, string name, string address, string phone, int numberOfRentals, string customerType, vector<string> listOfRentals);

    /*Constructor*/
    Customer();

    ~Customer();
    /*toString*/
    virtual string toString();
};

