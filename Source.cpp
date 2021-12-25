#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "RentalShop.h"
#include "MovieRecords.h"
#include "Interface.h"

using namespace std;

int main()
{
    ifstream fileinItem;
    ifstream fileinCustomer;
    fileinCustomer.open("../nhap.txt");
    fileinItem.open("../items.txt");
    if (!fileinItem || !fileinCustomer) {
        cout << "CANNOT open the file";
    }
    else {
        RentalShop* rt = new RentalShop(fileinItem, fileinCustomer);
        Interface display;
        bool exit = false;
        int choice = 0;
        do {
            display.menu();
            choice = display.takeChoice(11);
            if (choice == 11) {
                exit = true;
            }
            else {
                cout << "\n************************************************************************\n";
                display.option(choice, &rt);
            }
        } while (!exit);

        rt->deletePointerVector();
        fileinItem.close();
        fileinCustomer.close();
    }

    cout << '\n';
    cout << "ASSIGNMENT 2 GROUP 16" << '\n';
    cout << "s3819521, s3819521@rmit.edu.vn, Nguyen, Pham Gia" << '\n';
    cout << "s3836605, s3836605@rmit.edu.vn, Dang, La Tran Hai" << '\n';
    cout << "s3836320, s3836320@rmit.edu.vn, Anh, Huynh Van" << '\n';
    cout << "s3878434, s3878434@rmit.edu.vn, Minh, Nguyen The" << '\n';

    return 0;
}