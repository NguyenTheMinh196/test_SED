#pragma once
#include "Customer.h"
#include "Item.h"
#include <vector>
#include<iostream>
#include<string>
#include<fstream>
#include"MovieRecords.h"
#include"DVDs.h"
#include"Games.h"
#include "Customer.h"
#include "VipAccount.h"
#include "GuestAccount.h"
#include "RegularAccount.h"
#include "Validation.h"
class RentalShop
{
private:
	//vector<Customer*> customers;
	vector<Item*> items;
	vector<Customer*> customers;
public:
	
	RentalShop(ifstream& filein, ifstream& fileinCustomer);
	~RentalShop();
	/*getter*/
	vector<Customer*> getCustomers();
	vector<Item*> getItems();
	/*setter*/
	void setCustomers(vector<Customer*> customers);
	void setItems(vector<Item*> items);

	/*Search*/
	Item* searchItemID(string ID);
	Customer* searchCusID(string ID);
	vector<Item*> searchItemTitle(string title);
	vector<Customer*> searchCusName(string name);
	vector<Item*> searchNoCopy();
    vector<string> IDs();
    vector<string> CusIDS();

 	Customer* promoteCusID(string ID, int type, int typeSearch);
    bool returnItem(string input, string item, int typeSearch);

    /*Display*/
	void displayNoCopy();
	void display(vector<Item*> obj);
	void display(vector<Customer*> obj);
	void displayGroup(string groupType);
	void printAll();

	void printAllCustomerSortedName(int type);
	void printAllCustomerSortedID(int type);
	void printAllItemSortedName(int type);
	void printAllItemSortedID(int type);

	/*delete vector pointer*/
	void deletePointerVector();
	
	
};

