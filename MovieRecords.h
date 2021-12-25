#pragma once
#include<string>
#include "Item.h"
using namespace std;
class MovieRecords : public Item
{
private:
    string genres;
public:
    /*Constructor*/
    MovieRecords();
    MovieRecords(Item* item);
    ~MovieRecords();

    /*getter*/
    string getGenres();

    /*setter*/
    void setGenres(string genres);

    /*Search*/


    /*Override toString()*/
    virtual string toString();
};
