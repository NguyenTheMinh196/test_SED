//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include "RentalShop.h"
//#include "MovieRecords.h"
//
//using namespace std;
//
//class Interface {
//private:
//    int menuChoice;
//    RentalShop* rs;
//public:
//    Interface();
//
//    void menu();
//    void menu1();
//    void menu2();
//    void menu3();
//    void menu4();
//    void menu5();
//    void menu6();
//    void menu7();
//    void menu8();
//    void menu9();
//    void menu10();
//
//    void option(int choice, RentalShop** rs);
//    int takeChoice(int limit);
//};
//
//Interface::Interface() {
//    this->menuChoice = 0;
//}
//
//void Interface::menu() {
//    cout << "Welcome to Genie’s video store\n";
//    cout << "Enter an option below\n";
//    cout << "1.  Add a new item, update or delete an existing item\n";
//    cout << "2.  Add new customer or update an existing customer\n";
//    cout << "3.  Promote an existing customer\n";
//    cout << "4.  Rent an item\n";
//    cout << "5.  Return an item\n";
//    cout << "6.  Display all items\n";
//    cout << "7.  Display out-of-stock items\n";
//    cout << "8.  Display all customers\n";
//    cout << "9.  Display group of customers\n";
//    cout << "10. Search items or customers\n";
//    cout << "11. Exit\n";
//    cout << "Your choice [1 - 11]: ";
//}
//
//void Interface::menu1() {
//    cout << "1. Add item\n";
//    cout << "2. Update item\n";
//    cout << "3. Delete item\n";
//    cout << "Your choice [1 - 3]: ";
//    int subChoice = this->takeChoice(3);
//}
//
//void Interface::menu2() {
//    cout << "1. Add customer\n";
//    cout << "2. Update customer\n";
//    cout << "Your choice [1 - 2]: ";
//    int subChoice = this->takeChoice(2);
//}
//
//void Interface::menu3() {
//    cout << "Not designed yet";
//}
//
//void Interface::menu4() {
//    cout << "Not designed yet";
//}
//
//void Interface::menu5() {
//    cout << "Not designed yet";
//}
//
//void Interface::menu6() {
//    cout << "Not designed yet";
//}
//
//void Interface::menu7() {
//    this->rs->displayNoCopy();
//}
//
//void Interface::menu8() {
//    cout << "Not designed yet";
//}
//
//void Interface::menu9() {
//    cout << "1. Guest\n";
//    cout << "2. Regular\n";
//    cout << "3. VIP\n";
//    cout << "Your choice [1 - 3]: ";
//    int subChoice = this->takeChoice(3);
//    cout << '\n';
//
//    const char* group[3] = { "Guest", "Regular", "VIP" };
//    this->rs->displayGroup(group[subChoice - 1]);
//    vector<Customer*> tmp = this->rs->getCustomers();
//    tmp.clear();
//    this->rs->setCustomers(tmp);
//}
//
//void Interface::menu10() {
//    cout << "1. Item\n";
//    cout << "2. Customer\n";
//    cout << "Your choice [1 - 2]: ";
//    int subChoice = this->takeChoice(2);
//
//    if (subChoice == 1) {
//        cout << '\n';
//        cout << "1. ID\n";
//        cout << "2. Title\n";
//        cout << "Your choice [1 - 2]: ";
//        subChoice = this->takeChoice(2);
//
//        cout << '\n';
//        string word;
//        if (subChoice == 1) {
//            cout << "ID: ";
//            getline(cin, word);
//            cout << '\n';
//            Item* i1 = this->rs->searchItemID(word);
//            cout << i1->toString();
//        }
//        else if (subChoice == 2) {
//            cout << "Title: ";
//            getline(cin, word);
//            cout << '\n';
//            vector<Item*> i1 = this->rs->searchItemTitle(word);
//            this->rs->display(i1);
//        }
//    }
//    else if (subChoice == 2) {
//        cout << '\n';
//        cout << "1. ID\n";
//        cout << "2. Name\n";
//        cout << "Your choice [1 - 2]: ";
//        subChoice = this->takeChoice(2);
//
//        cout << '\n';
//        string word;
//        if (subChoice == 1) {
//            cout << "ID: ";
//            getline(cin, word);
//            cout << '\n';
//            Customer* c1 = this->rs->searchCusID(word);
//            cout << c1->toString();
//        }
//        else if (subChoice == 2) {
//            cout << "Name: ";
//            getline(cin, word);
//            cout << '\n';
//            vector<Customer*> c1 = this->rs->searchCusName(word);
//            this->rs->display(c1);
//        }
//    }
//}
//
//void Interface::option(int menuChoice, RentalShop** rs) {
//    this->rs = *rs;
//    this->menuChoice = menuChoice;
//    cout << '\n';
//
//    switch (menuChoice)
//    {
//    case 1:
//        this->menu1();
//        break;
//    case 2:
//        this->menu2();
//        break;
//    case 3:
//        this->menu3();
//        break;
//    case 4:
//        this->menu4();
//        break;
//    case 5:
//        this->menu5();
//        break;
//    case 6:
//        this->menu6();
//        break;
//    case 7:
//        this->menu7();
//        break;
//    case 8:
//        this->menu8();
//        break;
//    case 9:
//        this->menu9();
//        break;
//    case 10:
//        this->menu10();
//        break;
//    default:
//        break;
//    }
//    cout << '\n';
//}
//
//int Interface::takeChoice(int limit) {
//    while (true) {
//        string input;
//        int choice;
//        getline(cin, input);
//
//        while (cin.fail() || cin.eof() || input.find_first_not_of("0123456789") != string::npos) {
//            cout << "Require number in range [1 - " << limit << "]: ";
//            if (input.find_first_not_of("0123456789") == string::npos) {
//                cin.clear();
//                cin.ignore(256, '\n');
//            }
//            getline(cin, input);
//        }
//
//        string::size_type st;
//        choice = stoi(input, &st);
//        if (choice >= 1 && choice <= limit) {
//            return choice;
//        }
//        else {
//            cout << "Number must be in range [1 - " << limit << "]: ";
//        }
//    }
//}
//
//int main()
//{
//    ifstream fileinItem;
//    ifstream fileinCustomer;
//    fileinCustomer.open("nhap.txt");
//    fileinItem.open("items.txt");
//    if (!fileinItem || !fileinCustomer) {
//        cout << "CANNOT open the file";
//    }
//    else {
//        RentalShop* rt = new RentalShop(fileinItem, fileinCustomer);
//        Interface display;
//        bool exit = false;
//        int choice = 0;
//        do {
//            display.menu();
//            choice = display.takeChoice(11);
//            if (choice == 11) {
//                exit = true;
//            }
//            else {
//                display.option(choice, &rt);
//            }
//        } while (!exit);
//
//        rt->deletePointerVector();
//        // initialize seven variables to store
//    }
//    fileinItem.close();
//    fileinCustomer.close();
//    return 0;
//}