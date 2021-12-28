#include "Validation.h"
/*CHECK INPUT FILE FIELD*/
/*ITEM FILE*/
bool Validation::checkNullField(string field) {
    if (field == "" || field == "\n") {
        return false;
    }
    /*check if it only contains space*/
    else if (field.find_first_not_of(' ') == field.npos) {
        return false;
    }
    return true;
}
/*check ID Item format*/
bool Validation::checkIdItem(string id, vector<string>& IDs) {
    if (id.size() < 9) { // add
        cout << "Item Id is wrong format" << endl;
        return false;
    }
    // if id is not a null field

    if (checkNullField(id)) {
        if (id[0] == 'I' && id[4] == '-') {
            bool checkNum = true;
            // check the next 3 digits
            for (int i = 1; i < id.length(); i++) {
                if (i == 4) continue;
                if (!isdigit(id[i])) {
                    checkNum = false;
                }
            }
            if (checkNum) {
                // convert substr from index 5 to a number
                int year = stoi(id.substr(5, id.length() - 5));
                // validate year
                if (year >= 1000 && year <= 2021) {
                    for (int i = 0; i < IDs.size(); i++) {
                        if (id == IDs[i]) {
                            cout << "ID Item is not unique" << endl;
                            return false;
                        }
                    }
                    IDs.push_back(id);
                    return true;
                }
            }
        }
        cout << "Wrong ID item format!" << endl;
        return false;
    }
    cout << "ID is empty!" << endl;
    return false;
}
bool Validation::validateIdItem(string id) {
    // if id is not a null field
    if (id.size() < 9) {
        cout << "Item Id is wrong format" << endl;
        return false;
    }

    if (checkNullField(id)) {
        if (id[0] == 'I' && id[4] == '-') {
            bool checkNum = true;
            // check the next 3 digits
            for (int i = 1; i < id.length(); i++) {
                if (i == 4) continue;
                if (!isdigit(id[i])) {
                    checkNum = false;
                }
            }
            if (checkNum) {
                // convert substr from index 5 to a number
                int year = stoi(id.substr(5, id.length() - 5));
                // validate year
                if (year >= 1000 && year <= 2021) {
                    return true;
                }
            }
        }
    }
    return false;
}
/*check Rental Type*/
bool Validation::checkRentalType(string rentalType) {
    if (rentalType == "Game" || rentalType == "DVD" || rentalType == "Record") {
        return true;
    }
    cout << "Rental type is not Valid!" << endl;
    return false;
}
/*check loan */
void Validation::checkLoan(string loan, int& numLoanType, string& loanType) {
    if (checkNullField(loan)) {
        int pos = loan.find('-'); // find the token
        loanType = loan.substr(pos + 1, loan.length());
        if (pos != -1 && (loanType == "day" || loanType == "week")) {
            bool checkNum = true;
            for (int i = 0; i < pos; i++) {
                if (!isdigit(loan[i])) {
                    checkNum = false;
                    numLoanType = -1;
                    return;
                }
            }
            if (checkNum) numLoanType = stoi(loan.substr(0, pos));
        }
        else {
            numLoanType = -1;
            cout << "Wrong loan format!" << endl;
            return;
        }
    }
}
/*check fee*/
bool Validation::checkFee(string fee) {
    if (fee.empty())
        return false;

    bool sawDot = false;
    for (char c : fee)
    {
        if (!(isdigit(c) || (c == '.' && !sawDot)))
            return false;
        sawDot = sawDot || (c == '.');
    }

    return true;
}
/*check if a number is integer*/
bool Validation::checkInt(string num) {
    if (num.empty()) {
        cout << "Int is empty!" << endl;
        return false;
    }
    for (char c : num) {
        if (!(isdigit(c))) {
            cout << "Int is wrong format!" << endl;
            return false;
        }
    }
    return true;
}
/*check all element*/
bool Validation::checkItem(string id, vector<string>& IDs, string title, string rentalType, string loan, int& numLoanType, string& loanType, string fee, string numOfCopy, string& genre)
{
    if (rentalType == "DVD" || rentalType == "Record") {
        if (checkNullField(genre) == false) {
            cout << "Missing genre field!" << endl;
            return false;
        }
    }
    if (checkNullField(title) == false) {
        cout << "Missing title! \n";
        return false;
    }
    checkLoan(loan, numLoanType, loanType);
    if (checkIdItem(id, IDs) &&
        checkRentalType(rentalType) &&
        (numLoanType != -1) &&
        checkFee(fee) &&
        checkInt(numOfCopy)) {

        return true;
    }
    return false;
}

void Validation::readOneItemInItemFile(ifstream& filein, Item* item, string& genre, vector<string>& IDs) {
    // initialize seven variables to store 
    string id;
    string title;
    string rentalType;
    string loan;
    int numLoanType;
    string loanType;
    string numOfCopy;
    string fee;
    // read id
    getline(filein, id, ',');
    // read title
    getline(filein, title, ',');
    // read rental  type
    getline(filein, rentalType, ',');
    // get loanType and numLoanType
    getline(filein, loan, ',');
    // set number of copy, fee, genre
    getline(filein, numOfCopy, ',');
    // check rental type of the Item object
    if (rentalType == "Record" || rentalType == "DVD") {
        getline(filein, fee, ',');
        getline(filein, genre);
    }
    else {
        filein >> fee;
        string temp; // read the "\n" of the line    
        getline(filein, temp);
    }
    if (checkItem(id, IDs, title, rentalType, loan, numLoanType, loanType, fee, numOfCopy, genre)) {
        item->setAll(id, title, rentalType, numLoanType, loanType, atoi(numOfCopy.c_str()), stof(fee));
    }
}
/*Check type of item
    return 2 : Record
    return 1: DVDs
    return 0: Game*/
int Validation::checkTypeItem(Item* item) {
    if (item->getRentalType() == "Record") {
        return 2;
    }
    else if (item->getRentalType() == "DVD") {
        return 1;
    }
    else if (item->getRentalType() == "Game") {
        return 0;
    }
    // cout << "Invalid Type!";
    return -1;
}

/*Read file and classofy the Item then add to vector Item*/
void Validation::readFileItem(ifstream& filein, vector<Item*>& items) {
    string temp; // initialize to check "#" before
   // move the pointer to the start of the line
    int space_back = 0; // the size to move back
    int temp_space_back = 0;
    vector<string> IDs;
    for (string temp; getline(filein, temp);) {
        // if (!filein) break; // read until the end of the file
         //getline(filein, temp);
        space_back = filein.tellg();
        if (temp[0] != '#') break; // check the first element is "#" then break
        temp_space_back = space_back;
    }
    filein.seekg(temp_space_back - space_back, ios_base::cur);  // move back
    for (;;) {
        if (filein.tellg() == -1) break; // read until the end of the file
        Item* item = new Item();
        string genre = "";
        readOneItemInItemFile(filein, item, genre, IDs);
        int checkType = checkTypeItem(item);
        if (checkType == 2) {
            MovieRecords* mv = new MovieRecords(item);
            mv->setGenres(genre);
            items.push_back(mv);
        }
        else if (checkType == 1) {
            DVDs* dvd = new DVDs(item);
            dvd->setGenres(genre);
            items.push_back(dvd);
        }
        else if (checkType == 0) {
            Games* game = new Games(item);
            items.push_back(game);
        }
    }
    IDs.clear();
}
/*=====================================================
=========================CUSTOMER======================
==========================================================*/
/*read one line of the item in Customer file*/
/*VALIDATE INPUT FROMCUSTOMER FILE*/
bool Validation::checkIdCustomer(string id, vector<string>& CUSs) {
    // if id is not a null field
    if (checkNullField(id)) {
        if (id[0] == 'C') {
            bool checkNum = true;
            // check the next 3 digits
            for (int i = 1; i < 4; i++) {
                if (i == 4) continue;
                if (!isdigit(id[i])) {
                    checkNum = false;
                }
            }
            if (checkNum) {
                for (int i = 0; i < CUSs.size(); i++) {
                    if (id == CUSs[i]) {
                        cout << "ID Customer is not unique" << endl;
                        return false;
                    }
                }
                CUSs.push_back(id);
                return true;
            }
        }
        cout << "Wrong ID customer format!" << endl;
        return false;
    }
    cout << "ID is empty!" << endl;
    return false;
}
bool Validation::validateIdCus(string id) {
    // if id is not a null field
    if (id.size() != 4) { //fix
        cout << "Item Id is wrong format" << endl;
        return false;
    }
    if (checkNullField(id)) {
        if (id[0] == 'C') {
            bool checkNum = true;
            // check the next 3 digits
            for (int i = 1; i < id.length(); i++) {
                if (i == 4) continue;
                if (!isdigit(id[i])) {
                    checkNum = false;
                }
            }
            return checkNum;
        }
    }
    return false;
}
bool Validation::checkCustomerType(string customerType) {
    if (customerType == "Guest" || customerType == "Regular" || customerType == "VIP") {
        return true;
    }
    cout << "Customer type is not Valid!" << endl;
    return false;
}
bool Validation::validateLine(string line) {
    if (line.empty()) {
        cout << "Line is empty!" << endl;
        return false;
    }
    int count = 0;
    for (char c : line) {
        if (c == ',') {
            count++;
        }
    }
    if (count == 5) {
        return true;
    }
    return false;
}
bool Validation::checkCustomer(string id, vector<string>& CUSs, string name, string address, string phone, string numOfRentals, string customerType, vector<string> listItem) {

    if (!checkNullField(name)) {
        cout << "Name of the Customer is NULL! \n";
        return false;
    }
    if (!checkNullField(address)) {
        cout << "Address of the Customer is NULL! \n";
        return false;
    }
    if (checkNullField(phone)) {
        if (!checkInt(phone)) {
            cout << "Phone of the Customer is wrong format" << endl;
            return false;
        }
    }
    else {
        cout << "Phone of the Customer is NULL! \n";
        return false;
    }
    if (checkIdCustomer(id, CUSs) && checkCustomerType(customerType)) {
        return true;
    }
    return false;
}
void Validation::readOneCustomerInCustomerFile(ifstream& filein, Customer* customer, vector<string>& CUSs) {
    // initialize seven variables to store
    string id;
    string name;
    string address;
    string phone;
    string numOfRentals;
    string customerType;
    vector<string> listItem;
    // read id
    getline(filein, id, ',');
    // read title
    getline(filein, name, ',');
    // read rental  type
    getline(filein, address, ',');
    getline(filein, phone, ',');
    getline(filein, numOfRentals, ',');
    bool checkRental = checkInt(numOfRentals);
    getline(filein, customerType);
    string items = "";
    // check the number of rental
    bool checkId = true;
    if (checkRental) {
        int space_back = 0; // the size to move back
        int temp_space_back = 0;
        for (;;) {
            if (filein.tellg() == -1) break;
            space_back = filein.tellg();
            getline(filein, items);
            temp_space_back = filein.tellg(); // the size to move back
            if (validateIdItem(items)) {
                checkId = checkIdItem(items, listItem);
            }
            else if (validateLine(items)) {
                filein.seekg(-temp_space_back + space_back, ios_base::cur);
                break;
            }
        }
    }
    if (checkId && checkRental && checkCustomer(id, CUSs, name, address, phone, numOfRentals, customerType, listItem)) {
        if (atoi(numOfRentals.c_str()) == listItem.size()) {
            customer->setAll(id, name, address, phone, atoi(numOfRentals.c_str()), customerType, listItem);
        }
        else {
            cout << "Number of items is not valid!" << endl;
        }

    }
}
Item* Validation::searchItemID(vector<Item*> items, string ID) {
    int size = items.size();
    for (int i = 0; i < size; i++) {
        if (items[i]->getID() == ID) {
            return items[i];
        }
    }
    return NULL;
}
/*Read file and classofy the Item then add to vector Item*/
void Validation::readFileCustomer(ifstream& filein, vector<Customer*>& customers) {
    string temp; // initialize to check "#" before
    // move the pointer to the start of the line
    int space_back = 0; // the size to move back
    int temp_space_back = 0;
    vector<string> CUSs;
    for (;;) {
        if (!filein) break; // read until the end of the file
        getline(filein, temp);
        space_back = filein.tellg();
        if (temp[0] != '#') break; // check the first element is "#" then break
        temp_space_back = space_back;
    }
    filein.seekg(temp_space_back - space_back, ios_base::cur);  // move back
    for (;;) {
        if (filein.tellg() == -1) break;
        Customer* customer = new Customer();
        readOneCustomerInCustomerFile(filein, customer, CUSs);
        if (customer->getcustomerType() == "VIP") {
            VipAccount* vip = new VipAccount(customer);
            customers.push_back(vip);
        }
        else if (customer->getcustomerType() == "Guest") {
            GuestAccount* guest = new GuestAccount(customer);
            customers.push_back(guest);
        }
        else if (customer->getcustomerType() == "Regular") {
            RegularAccount* regular = new RegularAccount(customer);
            customers.push_back(regular);
        }
    }
    CUSs.clear();
}
void Validation::checkCustomerAndItems(vector<Item*>& items, vector<Customer*>& customers) {
    // the format of itemsBorrow is item, numberofBorrow of item1, item 2, numberofBorrow of item2, ... so on
    vector<string> itemsBorrow;
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i]->getnumOfRentals() > 0) {
            for (int j = 0; j < customers[i]->getnumOfRentals(); j++) {
                Item* itemBorrow = searchItemID(items, customers[i]->getListOfRentals()[j]);
                if (itemBorrow == NULL) {
                    cout << "The items that " << customers[i]->getID() << " customer borrowed is not exist in Item list" << endl;
                    customers.erase(customers.begin() + i);
                    break;
                }
                else {
                    bool checkExist = true;
                    for (int z = 0; z < itemsBorrow.size(); z++) {
                        if (itemBorrow->getID() == itemsBorrow[z]) {
                            itemsBorrow[z + 1] = to_string(atoi(itemsBorrow[z + 1].c_str()) + 1);
                            checkExist = false;
                            break;
                        }
                    }
                    if (checkExist) {
                        itemsBorrow.push_back(itemBorrow->getID()); // add to the list
                        itemsBorrow.push_back("1"); // add to the list
                    }
                }

            }

        }

    }
    // update the new number of copy for items
    for (int b = 0; b < items.size(); b++) {
        for (int a = 0; a < itemsBorrow.size(); a++) {
            if (items[b]->getID() == itemsBorrow[a]) {
                if (items[b]->getNumOfCopy() < atoi(itemsBorrow[a + 1].c_str())) {
                    items[b]->setNumOfCopy(atoi(itemsBorrow[a + 1].c_str()));
                    break;
                }
            }
        }
    }
    itemsBorrow.clear();
}
Validation::Validation(ifstream& filein, ifstream& fileinCustomer) {

}
Validation::~Validation() {

}