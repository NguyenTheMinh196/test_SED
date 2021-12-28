#pragma once
#include<string>
#include "Item.h"
using namespace std;
class DVDs : public Item
{
private:
    string genres;
public:
    /*getter*/
    string getGenres();
    /*setter*/
    void setGenres(string genres);
    DVDs();
    DVDs(Item* item);
    ~DVDs();
    string toString();
};

