#include <algorithm>
#include "Interface.h"

Interface::Interface() {
    this->menuChoice = 0;
}

void Interface::menu() {
    cout << "Welcome to Genie’s video store\n";
    cout << "Enter an option below\n";
    cout << "1.  Add a new item, update or delete an existing item\n";
    cout << "2.  Add new customer or update an existing customer\n";
    cout << "3.  Promote an existing customer\n";
    cout << "4.  Rent an item\n";
    cout << "5.  Return an item\n";
    cout << "6.  Display all items\n";
    cout << "7.  Display out-of-stock items\n";
    cout << "8.  Display all customers\n";
    cout << "9.  Display group of customers\n";
    cout << "10. Search items or customers\n";
    cout << "11. Exit\n";
    cout << "Your choice [1 - 11]: ";
}

void Interface::menu1() {
    cout << "1. Add item\n";
    cout << "2. Update item\n";
    cout << "3. Delete item\n";
    cout << "Your choice [1 - 3]: ";
    int subChoice = this->takeChoice(3);
    if(subChoice == 1 ) {
        //add item
        vector<Item *> items;
        Item *item = new Item;
        vector<string> IDs = this->rs->IDs();
        string id;
        string title;
        string rentalType;
        string loan;
        int numLoanType;
        string loanType;
        string numOfCopy;
        string fee;
        string genre;
        Validation *vl = new Validation();
        while (true) {
            // read id
            cout << "\nPlease put in the id for the new item: ";
            getline(cin, id);
            if(vl->validateIdItem(id)) {
                // read title
                cout << "Please put in the title for the new item: ";
                getline(cin, title);
                // read rental  type
                cout << "Please put in the rental type for the new item\n";
                cout << "1. Record\n";
                cout << "2. DVD\n";
                cout << "3. Game\n";
                cout << "Your choice [1 - 3]: ";
                int rentalTypeChoice = this->takeChoice(3);
                if (rentalTypeChoice == 1 || rentalTypeChoice == 2) {
                    cout << "Please put in the genre for the new item\n"
                            "1. Action\n"
                            "2. Drama\n"
                            "3. Comedy\n"
                            "4. Horror \n"
                            "Your choice: ";
                    int genreChoice = this->takeChoice(4);
                    if (rentalTypeChoice == 1) {
                        rentalType = "Record";
                    } else if (rentalTypeChoice == 2) {
                        rentalType = "DVD";
                    }
                    if (genreChoice == 1) {
                        genre = "Action";
                    } else if (genreChoice == 2) {
                        genre = "Drama";
                    } else if (genreChoice == 3) {
                        genre = "Comedy";
                    } else if (genreChoice == 4) {
                        genre = "Horror";
                    }
                } else if (rentalTypeChoice == 3) {
                    rentalType = "Game";
                }
                // get loanType and numLoanType
                cout << "Please put in the loan type for the new item\n"
                        "1. 2-day\n"
                        "2. 1-week\n"
                        "Your choice: ";
                int loanTypeChoice = this->takeChoice(2);
                if (loanTypeChoice == 1) {
                    loan = "2-day";
                } else if (loanTypeChoice == 2) {
                    loan = "1-week";
                }
                // set number of copy, fee, genre
                cout << "Please put in the number of copies available for the new item: ";
                getline(cin, numOfCopy);
                cout << "Please put in the rental fee for the new item: ";
                getline(cin, fee);
                // check rental type of the Item object
                if (vl->checkItem(id, IDs, title, rentalType, loan, numLoanType, loanType, fee, numOfCopy, genre)) {
                    item->setAll(id, title, rentalType, numLoanType, loanType, atoi(numOfCopy.c_str()), stof(fee));
                    if (rentalTypeChoice == 1) {
                        MovieRecords *mv = new MovieRecords(item);
                        mv->setGenres(genre);
                        items = this->rs->getItems();
                        items.push_back(mv);// can't delete the old vector or access the old vector
                        this->rs->setItems(items);
                    } else if (rentalTypeChoice == 2) {
                        DVDs *dvd = new DVDs(item);
                        dvd->setGenres(genre);
                        items = this->rs->getItems();
                        items.push_back(dvd);// can't delete the old vector or access the old vector
                        this->rs->setItems(items);
                    } else if (rentalTypeChoice == 3) {
                        Games *game = new Games(item);
                        items = this->rs->getItems();
                        items.push_back(game);// can't delete the old vector or access the old vector
                        this->rs->setItems(items);
                    }
                }
                this->rs->printAll();
            }
        }
    }
    else if(subChoice == 2){
        Validation* vl = new Validation();
        this->rs->printAllItemSortedID(1);
        string ID;
        while(true) {
            cout << "Please write the ID of the item you want to change here: ";
            getline(cin, ID);
            if(vl->validateIdItem(ID)) {
                Item *update_item = this->rs->searchItemID(ID);
                if (update_item == NULL) {
                    cout << "You have put in the wrong ID ";
                    cout << "Please try again ";
                } else if (update_item->getRentalType() == "DVD" || update_item->getRentalType() == "Record") {
                    cout << "Choose what kind of data you would like to change: \n"
                            "1. Title\n"
                            "2. Rental Type\n"
                            "3. Loan Type\n"
                            "4. Number of Copy\n"
                            "5. Fee\n"
                            "6. Status\n"
                            "7. genre\n"
                            "Your choice: ";
                    int kind = this->takeChoice(7);
                    if (kind == 1) {
                        string title;
                        cout << "Please put in a new title for the item: ";
                        getline(cin, title);
                        update_item->setTitle(title);
                        break;
                    } else if (kind == 2) {
                        cout
                                << "Warning: If you change the rental type to Game, the genre of the item will be deleted.\n"
                                   "Please choose the rental type you want to change to: \n"
                                   "1. DVD\n"
                                   "2. Record\n"
                                   "3. Game\n"
                                   "Your choice: ";
                        int newRentalType = this->takeChoice(3);
                        if (newRentalType == 1) { //change type to DVD
                            if (update_item->getRentalType() == "DVD") {
                                cout << "This item is already DVD";
                            } else if (update_item->getRentalType() == "Record") {
                                vector<Item *> items;
                                MovieRecords *newupdateitem = new MovieRecords;
                                newupdateitem->setAll(
                                        update_item->getID(),
                                        update_item->getTitle(),
                                        update_item->getRentalType(),
                                        update_item->getNumLoanType(),
                                        update_item->getLoanType(),
                                        update_item->getNumOfCopy(),
                                        update_item->getFee()
                                );
                                DVDs *dvd = new DVDs(newupdateitem);
                                dvd->setGenres(newupdateitem->getGenres());
                                items = this->rs->getItems();
                                items.push_back(dvd);// can't delete the old vector or access the old vector
                                this->rs->setItems(items);
                            }
                        } else if (newRentalType == 2) {
                            if (update_item->getRentalType() == "Record") {
                                cout << "This item is already a Movie Record";
                            } else if (update_item->getRentalType() == "DVD") {
                                vector<Item *> items;
                                DVDs *newupdateitem = new DVDs;
                                newupdateitem->setAll(
                                        update_item->getID(),
                                        update_item->getTitle(),
                                        update_item->getRentalType(),
                                        update_item->getNumLoanType(),
                                        update_item->getLoanType(),
                                        update_item->getNumOfCopy(),
                                        update_item->getFee()
                                );
                                MovieRecords *mv = new MovieRecords(newupdateitem);
                                mv->setGenres(newupdateitem->getGenres());
                                items = this->rs->getItems();
                                items.push_back(mv);// can't delete the old vector or access the old vector
                                this->rs->setItems(items);
                            }
                        } else if (newRentalType == 3) {
                            cout
                                    << "We will be deleting the genre section of the item to change this item rental type to Game";
                            vector<Item *> items;
                            Games *newupdateitem = new Games;
                            newupdateitem->setAll(
                                    update_item->getID(),
                                    update_item->getTitle(),
                                    update_item->getRentalType(),
                                    update_item->getNumLoanType(),
                                    update_item->getLoanType(),
                                    update_item->getNumOfCopy(),
                                    update_item->getFee());
                            items = this->rs->getItems();
                            int position = 0;
                            for (int i = 0; i < items.size(); i++) {
                                if (items[i]->getID() == update_item->getID()) {
                                    position = i;
                                }
                            }
                            items.erase(items.begin() + position);
                            items.push_back(newupdateitem);// can't delete the old vector or access the old vector
                            this->rs->setItems(items);
                        }
                        break;
                    } else if (kind == 3) {
                        cout << "Please choose the rental type you want to change to: \n"
                                "1. 2-day\n"
                                "2. 1-week\n"
                                "Your choice: ";
                        int choice = this->takeChoice(2);
                        if (choice == 1) {
                            if (update_item->getLoanType() == "2-day") {
                                cout << "This item loan type is already for 2 days";
                            } else if (update_item->getLoanType() == "1-week") {
                                update_item->setLoanType("2-day");
                            }
                        } else if (choice == 2) {
                            if (update_item->getLoanType() == "1-week") {
                                cout << "This item loan type is already for 1 week";
                            } else if (update_item->getLoanType() == "2-day") {
                                update_item->setLoanType("1-week");
                            }
                        }
                        break;
                    } else if (kind == 4) {
                        string numofCopy;
                        while (true) {
                            cout << "Please put in the amount of copy available for the item: ";
                            getline(cin, numofCopy);
                            if (vl->checkInt(numofCopy)) {
                                update_item->setNumOfCopy(atoi(numofCopy.c_str()));
                                break;
                            } else {
                                cout << "Please enter an integer!";
                            }
                        }
                        break;
                    } else if (kind == 5) {
                        string fee;
                        while (true) {
                            cout << "Please put in the cost to rent this item: ";
                            getline(cin, fee);
                            if (vl->checkFee(fee)) {
                                update_item->setNumOfCopy(stof(fee));
                                break;
                            } else {
                                cout << "Please enter the right type for fee!";
                            }
                        }
                        break;
                    } else if (kind == 6) {
                        cout
                                << "Reminder: If you change the status of the item, the number of copy will change accordingly!";
                        cout << "Please enter the status you wish to change for this item to: \n"
                                "1. Borrowed\n"
                                "2. available\n"
                                "Your choice: ";
                        int status = this->takeChoice(2);
                        if (status == 1) {
                            if (update_item->getStatus()) {
                                update_item->setStatus(false);
                                update_item->setNumOfCopy(0);
                            } else {
                                cout << "The item is already borrowed and there is no more stock available";
                            }
                        } else if (status == 2) {
                            if (update_item->getStatus()) {
                                cout << "The item is already available and there is still more stock available";
                            } else {
                                update_item->setStatus(true);
                                string fee;
                                while (true) {
                                    cout << "Please put in the cost to rent this item: ";
                                    getline(cin, fee);
                                    if (vl->checkFee(fee)) {
                                        update_item->setNumOfCopy(stof(fee));
                                        break;
                                    } else {
                                        cout << "Please enter the right type for fee!";
                                    }
                                }
                            }
                        }
                    } else if (kind == 7) {
                        cout << "Please put in the genre for the new item\n"
                                "1. Action\n"
                                "2. Drama\n"
                                "3. Comedy\n"
                                "4. Horror \n"
                                "Your choice: ";
                        int genreChoice = this->takeChoice(4);
                        if (update_item->getRentalType() == "DVD") {
                            vector<Item *> items;
                            items = this->rs->getItems();
                            DVDs *DVD_update_item = new DVDs(update_item);
                            int position = 0;
                            for (int i = 0; i < items.size(); i++) {
                                if (items[i]->getID() == update_item->getID()) {
                                    position = i;
                                }
                            }
                            items.erase(items.begin() + position);
                            if (genreChoice == 1) {
                                DVD_update_item->setGenres("Action");
                            } else if (genreChoice == 2) {
                                DVD_update_item->setGenres("Drama");
                            } else if (genreChoice == 3) {
                                DVD_update_item->setGenres("Comedy");
                            } else if (genreChoice == 4) {
                                DVD_update_item->setGenres("Horror");
                            }
                            items.push_back(DVD_update_item);// can't delete the old vector or access the old vector
                            this->rs->setItems(items);
                        } else if (update_item->getRentalType() == "Record") {
                            vector<Item *> items;
                            items = this->rs->getItems();
                            MovieRecords *MV_update_item = new MovieRecords(update_item);
                            int position = 0;
                            for (int i = 0; i < items.size(); i++) {
                                if (items[i]->getID() == update_item->getID()) {
                                    position = i;
                                }
                            }
                            items.erase(items.begin() + position);
                            if (genreChoice == 1) {
                                MV_update_item->setGenres("Action");
                            } else if (genreChoice == 2) {
                                MV_update_item->setGenres("Drama");
                            } else if (genreChoice == 3) {
                                MV_update_item->setGenres("Comedy");
                            } else if (genreChoice == 4) {
                                MV_update_item->setGenres("Horror");
                            }
                            items.push_back(MV_update_item);// can't delete the old vector or access the old vector
                            this->rs->setItems(items);
                        }
                    }
                    break; //break from the big loop and return to
                } else if (update_item->getRentalType() == "Game") {
                    cout << "Choose what kind of data you would like to change: "
                            "1. Title"
                            "2. Rental Type"
                            "3. Loan Type"
                            "4. Number of Copy"
                            "5. Fee"
                            "6. Status";
                    int kind = this->takeChoice(6);
                    if (kind == 1) {
                        string title;
                        cout << "Please put in a new title for the item: ";
                        getline(cin, title);
                        update_item->setTitle(title);
                        break;
                    } else if (kind == 2) {
                        cout
                                << "Warning: If you change the rental type to Game, the genre of the item will be deleted.\n"
                                   "Please choose the rental type you want to change to: \n"
                                   "1. DVD\n"
                                   "2. Record\n"
                                   "3. Game\n"
                                   "Your choice: ";
                        int newRentalType = this->takeChoice(3);
                        if (newRentalType == 1) {
                            update_item->setLoanType("DVD");
                            cout << "Please put in the genre for the new item\n"
                                    "1. Action\n"
                                    "2. Drama\n"
                                    "3. Comedy\n"
                                    "4. Horror \n"
                                    "Your choice: ";
                            int genreChoice = this->takeChoice(4);
                            vector<Item *> items;
                            items = this->rs->getItems();
                            DVDs *DVD_update_item = new DVDs(update_item);
                            int position = 0;
                            for (int i = 0; i < items.size(); i++) {
                                if (items[i]->getID() == update_item->getID()) {
                                    position = i;
                                }
                            }
                            items.erase(items.begin() + position);
                            if (genreChoice == 1) {
                                DVD_update_item->setGenres("Action");
                            } else if (genreChoice == 2) {
                                DVD_update_item->setGenres("Drama");
                            } else if (genreChoice == 3) {
                                DVD_update_item->setGenres("Comedy");
                            } else if (genreChoice == 4) {
                                DVD_update_item->setGenres("Horror");
                            }
                            items.push_back(DVD_update_item);// can't delete the old vector or access the old vector
                            this->rs->setItems(items);
                        } else if (newRentalType == 2) {
                            update_item->setLoanType("Record");
                            cout << "Please put in the genre for the new item\n"
                                    "1. Action\n"
                                    "2. Drama\n"
                                    "3. Comedy\n"
                                    "4. Horror \n"
                                    "Your choice: ";
                            int genreChoice = this->takeChoice(4);
                            vector<Item *> items;
                            items = this->rs->getItems();
                            MovieRecords *MV_update_item = new MovieRecords(update_item);
                            int position = 0;
                            for (int i = 0; i < items.size(); i++) {
                                if (items[i]->getID() == update_item->getID()) {
                                    position = i;
                                }
                            }
                            items.erase(items.begin() + position);
                            if (genreChoice == 1) {
                                MV_update_item->setGenres("Action");
                            } else if (genreChoice == 2) {
                                MV_update_item->setGenres("Drama");
                            } else if (genreChoice == 3) {
                                MV_update_item->setGenres("Comedy");
                            } else if (genreChoice == 4) {
                                MV_update_item->setGenres("Horror");
                            }
                            items.push_back(MV_update_item);// can't delete the old vector or access the old vector
                            this->rs->setItems(items);
                        } else if (newRentalType == 3) {
                            cout << "This item is already a game type item!";
                        }
                        break;
                    } else if (kind == 3) {
                        cout << "Please choose the rental type you want to change to: \n"
                                "1. 2-day\n"
                                "2. 1-week\n"
                                "Your choice: ";
                        int choice = this->takeChoice(2);
                        if (choice == 1) {
                            if (update_item->getLoanType() == "2-day") {
                                cout << "This item loan type is already for 2 days";
                            } else if (update_item->getLoanType() == "1-week") {
                                update_item->setLoanType("2-day");
                            }
                        } else if (choice == 2) {
                            if (update_item->getLoanType() == "1-week") {
                                cout << "This item loan type is already for 1 week";
                            } else if (update_item->getLoanType() == "2-day") {
                                update_item->setLoanType("1-week");
                            }
                        }
                        break;
                    } else if (kind == 4) {
                        string numofCopy;
                        while (true) {
                            cout << "Please put in the amount of copy available for the item: ";
                            getline(cin, numofCopy);
                            if (vl->checkInt(numofCopy)) {
                                update_item->setNumOfCopy(atoi(numofCopy.c_str()));

                                if (numofCopy == "0") {
                                    update_item->setStatus(false);
                                }
                                break;
                            } else {
                                cout << "Please enter an integer!";
                            }
                        }
                        break;
                    } else if (kind == 5) {
                        string fee;
                        while (true) {
                            cout << "Please put in the cost to rent this item: ";
                            getline(cin, fee);
                            if (vl->checkFee(fee)) {
                                update_item->setFee(stof(fee));
                                break;
                            } else {
                                cout << "Please enter the right type for fee!";
                            }
                        }
                        break;
                    } else if (kind == 6) {
                        cout
                                << "Reminder: If you change the status of the item, the number of copy will change accordingly!";
                        cout << "Please enter the status you wish to change for this item to: \n"
                                "1. Borrowed\n"
                                "2. available\n"
                                "Your choice: ";
                        int status = this->takeChoice(2);
                        if (status == 1) {
                            if (update_item->getStatus()) {
                                update_item->setStatus(false);
                                update_item->setNumOfCopy(0);
                            } else {
                                cout << "The item is already borrowed and there is no more stock available";
                            }
                        } else if (status == 2) {
                            if (update_item->getStatus()) {
                                cout << "The item is already available and there is still more stock available";
                            } else {
                                update_item->setStatus(true);
                                string numofCopy;
                                while (true) {
                                    cout << "Please put in the amount of copy available for this item: ";
                                    getline(cin, numofCopy);
                                    if (vl->checkInt(numofCopy)) {
                                        update_item->setNumOfCopy(atoi(numofCopy.c_str()));
                                        break;
                                    } else {
                                        cout << "Please enter the right type for fee!";
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    else if(subChoice == 3) {
        int position;
        this->rs->printAllItemSortedID(1);
        string ID;
        while (true) {
            cout << "Please write the ID of the item you want to delete here: ";
            Validation *vl = new Validation();
            getline(cin, ID);
            if (vl->validateIdItem(ID)) {
                Item *update_item = this->rs->searchItemID(ID);
                if (update_item == NULL) {
                    cout << "You have put in the wrong ID ";
                    cout << "Please try again ";
                } else {
                    int size = this->rs->getItems().size();
                    for (int i = 0; i < size; i++) {
                        if (this->rs->getItems()[i]->getID() == ID) {
                            position = i;
                        }
                    }
                    this->rs->getItems().erase(this->rs->getItems().begin() + position);
                    break;
                }
            }
        }
    }
}

void Interface::menu2() {
    cout << "1. Add customer\n";
    cout << "2. Update customer\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);
    Validation* vl = new Validation();
    if(subChoice == 1) {
        // initialize seven variables to store
        string id;
        string name;
        string address;
        string phone;
        string numOfRentals;
        string customerType;
        vector<string> listItem;
        Validation *vl = new Validation();
        vector<string> CUSs = this->rs->CusIDS();
        Customer *customer = new Customer;
        // read id
        cout << "Please put in the ID for the new customer: ";
        getline(cin, id);
        if (vl->validateIdCus(id)) {
            // read title
            cout << "Please put in the name of the new customer: ";
            getline(cin, name);
            // read rental  type
            cout << "Please put in the address of the new customer: ";
            getline(cin, address);
            cout << "Please put in the phone number of the new customer: ";
            getline(cin, phone);
            cout << "Please put in the number of rental that this customer has already loaned of the new customer: ";
            getline(cin, numOfRentals);
            bool checkRental = vl->checkInt(numOfRentals);
            cout << numOfRentals << "This is numofRentals: ";
            int numOfRental = stoi(numOfRentals);
            cout << numOfRental << "This is numofRental:";
            cout << "Please choose the customer kind for this account: \n"
                    "1. Guest\n"
                    "2. Regular\n"
                    "3. VIP\n"
                    "Your choice: ";
            int customerkind = this->takeChoice(3);
            if (customerkind == 1) {
                customerType = "Guest";
            } else if (customerkind == 2) {
                customerType = "Regular";
            } else if (customerkind == 3) {
                customerType = "VIP";
            }
            string items = "";
            // check the number of rental
            bool checkId = true;
            int num_of_vid = 0;
            if (checkRental) {
                for (int i = 0; i < numOfRental; i ++) {
                    this->rs->printAllItemSortedID(1);
                    cout << "Please enter the ID of the item that the customer want to loan: ";
                    getline(cin, items);
                    bool founditem = false;
                    vector<string> listitemID = this->rs->IDs(); //list of item's id
                    if(vl->validateIdItem(items)) {
                        for(int i = 0; i < listitemID.size(); i ++){
                            if(listitemID[i] == items){
                                founditem = true;
                                break;
                            }
                        }
                        if(founditem) {
                            Item *new_item = this->rs->searchItemID(items);
                            if (new_item->getNumOfCopy() == 0) {
                                cout << "There is no more item in stock";
                                i--;
                            } else if (new_item->getNumOfCopy() > 0) {
                                if (customerType == "Guest") {
                                    if (new_item->getLoanType() == "Video" && new_item->getLoanType() == "2-day") {
                                        cout
                                                << "Guest can not loan a video for two day. Please upgrade your membership!";
                                    } else if (num_of_vid < 2) {
                                        if (new_item->getLoanType() == "Video" && new_item->getLoanType() == "1-week") {
                                            num_of_vid += num_of_vid;
                                        }
                                        new_item->setNumOfCopy(new_item->getNumOfCopy() - 1);
                                        if (new_item->getNumOfCopy() == 0) {
                                            new_item->setStatus(false);
                                        }
                                        listItem.push_back(new_item->getID());
                                    } else if (num_of_vid > 2) {
                                        cout
                                                << "The maximum amount of video that the guest can loan is 2! Please loan another item";
                                    }
                                    i--;
                                } else {
                                    new_item->setNumOfCopy(new_item->getNumOfCopy() - 1);
                                    listItem.push_back(new_item->getID());
                                    cout << listItem.size();
                                }
                            }
                        }
                        else{
                            cout<<"You have enter wrong item's ID!\n";
                            i--;
                        }
                    }
                    else{
                        cout << "You have enter wrong item's ID format!\n";
                        i--;
                    }
                }
            }
            if (checkId && checkRental &&
                vl->checkCustomer(id, CUSs, name, address, phone, numOfRentals, customerType, listItem)) {
                customer->setAll(id, name, address, phone, numOfRental, customerType, listItem);
            }
            if (customer->getcustomerType() == "VIP") {
                VipAccount *vip = new VipAccount(customer);
                vip->setRewardPoint(vip->getnumOfRentals());
                vector<Customer *> customers = this->rs->getCustomers();
                customers.push_back(vip);
                this->rs->setCustomers(customers);
            } else if (customer->getcustomerType() == "Guest") {
                GuestAccount *guest = new GuestAccount(customer);
                vector<Customer *> customers = this->rs->getCustomers();
                customers.push_back(guest);
                this->rs->setCustomers(customers);
            } else if (customer->getcustomerType() == "Regular") {
                RegularAccount *regular = new RegularAccount(customer);
                vector<Customer *> customers = this->rs->getCustomers();
                customers.push_back(regular);
                this->rs->setCustomers(customers);
            }
        }
        else {
            cout << "You have enter wrong customer ID's format";
        }
    }
    else if(subChoice == 2){
        this->rs->printAllCustomerSortedID(1);
        Validation* vl = new Validation();
        string ID;
        while(true) {
            cout << "Please write the ID of the Customer you want to change here: ";
            getline(cin, ID);
            Customer *update_customer = this->rs->searchCusID(ID);
            if (update_customer == NULL) {
                cout << "You have put in the wrong ID ";
                cout << "Please try again ";
            }
            else if(update_customer->getcustomerType() == "Guest"|| update_customer->getcustomerType() == "Regular"){
                cout<<"Choose what kind of data you would like to change: \n"
                      "Note: If you change the rental list section, number of rental will also change accordingly.\n"
                      "1. Name\n"
                      "2. Address\n"
                      "3. Phone\n"
                      "4. Customer type\n"
                      "5. Rental list\n"
                      "Your choice: ";
                int kind = this->takeChoice(5);
                if(kind == 1){
                    string name;
                    cout<<"Please put in a new name for the customer: ";
                    getline(cin, name);
                    update_customer->setName(name);
                    break;
                }
                else if(kind == 2){
                    string address;
                    cout<<"Please put in a new address for the customer: ";
                    getline(cin, address);
                    update_customer->setName(address);
                    break;
                }
                else if(kind == 3){
                    string Phonenumber;
                    cout<<"Please put in a new phone number for the customer: ";
                    getline(cin, Phonenumber);
                    update_customer->setName(Phonenumber);
                    break;
                }
                else if(kind == 4) {
                    cout << "Warning: If you change the rental type to Game, the genre of the item will be deleted.\n"
                            "Please choose the rental type you want to change to: \n"
                            "1. Guest\n"
                            "2. Regular\n"
                            "3. VIP\n"
                            "Your choice: ";
                    int newcustomertype = this->takeChoice(3);
                    if (newcustomertype == 1) {
                        if (update_customer->getcustomerType() == "Guest") {
                            cout << "This account is already a guest account!";
                        } else if (update_customer->getcustomerType() == "Regular") {
                            vector<Customer *> customers;
                            RegularAccount *newupdatecustomer = new RegularAccount;
                            newupdatecustomer->setAll(
                                    update_customer->getID(),
                                    update_customer->getName(),
                                    update_customer->getAdress(),
                                    update_customer->getPhone(),
                                    update_customer->getnumOfRentals(),
                                    update_customer->getcustomerType(),
                                    update_customer->getListOfRentals()
                            );
                            customers = this->rs->getCustomers();
                            customers.push_back(
                                    newupdatecustomer);// can't delete the old vector or access the old vector
                            this->rs->setCustomers(customers);
                            cout << "The update process has been successful!";
                        }
                    } else if (newcustomertype == 2) {
                        if (update_customer->getcustomerType() == "Regular") {
                            cout << "This account is already a regular account!";
                        } else if (update_customer->getcustomerType() == "Guest") {
                            vector<Customer *> customers;
                            GuestAccount *newupdatecustomer = new GuestAccount;
                            newupdatecustomer->setAll(
                                    update_customer->getID(),
                                    update_customer->getName(),
                                    update_customer->getAdress(),
                                    update_customer->getPhone(),
                                    update_customer->getnumOfRentals(),
                                    update_customer->getcustomerType(),
                                    update_customer->getListOfRentals()
                            );
                            customers = this->rs->getCustomers();
                            customers.push_back(
                                    newupdatecustomer);// can't delete the old vector or access the old vector
                            this->rs->setCustomers(customers);
                            cout << "The update process has been successful!";
                        }
                    } else if (newcustomertype == 3) {
                        if (update_customer->getcustomerType() == "Regular") {
                            vector<Customer *> customers;
                            RegularAccount *newupdatecustomer = new RegularAccount;
                            newupdatecustomer->setAll(
                                    update_customer->getID(),
                                    update_customer->getName(),
                                    update_customer->getAdress(),
                                    update_customer->getPhone(),
                                    update_customer->getnumOfRentals(),
                                    update_customer->getcustomerType(),
                                    update_customer->getListOfRentals()
                            );
                            customers = this->rs->getCustomers();
                            customers.push_back(
                                    newupdatecustomer);// can't delete the old vector or access the old vector
                            this->rs->setCustomers(customers);
                            cout << "The update process has been successful!";
                        } else if (update_customer->getcustomerType() == "Guest") {
                            vector<Customer *> customers;
                            GuestAccount *newupdatecustomer = new GuestAccount;
                            newupdatecustomer->setAll(
                                    update_customer->getID(),
                                    update_customer->getName(),
                                    update_customer->getAdress(),
                                    update_customer->getPhone(),
                                    update_customer->getnumOfRentals(),
                                    update_customer->getcustomerType(),
                                    update_customer->getListOfRentals()
                            );
                            customers = this->rs->getCustomers();
                            customers.push_back(
                                    newupdatecustomer);// can't delete the old vector or access the old vector
                            this->rs->setCustomers(customers);
                            cout << "The update process has been successful!";
                        }
                    }
                    break;
                }
                else if(kind == 5){
                    vector<Item*> items = this->rs->getItems();
                    this->rs->printAllCustomerSortedID(1);
                    cout<<"Reminder: Making changes in the list of rental item will also affect the number of rental item!\n";
                    cout <<"Please choose what would you like to do with the list of item: \n"
                           "1. Add an item\n"
                           "2. Reduce item\n"
                           "Your choice: \n";
                    int Rentallistchoice = this->takeChoice(2);
                    if(Rentallistchoice == 1){
                        if(update_customer->getcustomerType() == "Guest"){
                            string item_ID;
                            cout<<"List of items available: \n";
                            int vid_borrowed = 0;
                            this->rs->printAllItemSortedID(1);
                            cout<<"Reminder: The account that you want to update is a Guest account so you can not borrow 3 or more videos at a time or a 1-week type video!\n";
                            cout<<"Please type in the ID of the item that you wish to loan: ";
                            getline(cin, item_ID);
                            if(vl->validateIdItem(item_ID)){
                                for(int i = 0; i<items.size(); i++){
                                    if(items[i]->getID() == item_ID){
                                        vector<string> borrowed_item = update_customer->getListOfRentals();
                                        for(int a = 0; a < borrowed_item.size(); a++){
                                            if(this->rs->searchItemID(borrowed_item[a])->getRentalType() == "Video" && this->rs->searchItemID(borrowed_item[a])->getLoanType() == "1-week")
                                            {
                                                vid_borrowed += vid_borrowed;
                                            }
                                        }
                                        if(items[i]->getLoanType() == "1-week" && items[i]->getRentalType() == "Video" && vid_borrowed == 2){
                                            cout << "This account have already rent 2 of 1-week type video so this account can not loan more!";
                                        }
                                        else if(items[i]->getLoanType() == "2-day" && items[i]->getRentalType() == "Video"){
                                            cout<<"Guest account can not loan 2-day type video!";
                                        }
                                        else{
                                            if(items[i]->getNumOfCopy()>0){
                                                items[i]->setNumOfCopy(items[i]->getNumOfCopy() - 1);
                                                if(items[i]->getNumOfCopy() == 0){
                                                    items[i]->setStatus(false);
                                                }
                                                update_customer->setNumOfRentals(update_customer->getnumOfRentals()+1);
                                                update_customer->getListOfRentals().push_back(items[i]->getID());
                                            }
                                            else if(items[i]->getNumOfCopy() == 0){
                                                cout<<"There is no more stock available for this item in stock!";
                                            }
                                        }
                                    }
                                    cout << "You have enter wrong item ID!";
                                    break;
                                }
                            }
                            else{
                                cout << "You have enter the wrong item ID!";
                            }
                        }
                        else if(update_customer->getcustomerType() == "Regular"){
                            string item_ID;
                            cout<<"List of items available: \n";
                            int vid_borrowed = 0;
                            this->rs->printAllItemSortedID(1);
                            cout<<"Please type in the ID of the item that you wish to loan: ";
                            getline(cin, item_ID);
                            if(vl->validateIdItem(item_ID)){
                                Item* choosen_item = this->rs->searchItemID(item_ID);
                                if(choosen_item->getNumOfCopy()>0){
                                    choosen_item->setNumOfCopy(choosen_item->getNumOfCopy() - 1);
                                    if(choosen_item->getNumOfCopy() == 0){
                                        choosen_item->setStatus(false);
                                    }
                                    update_customer->setNumOfRentals(update_customer->getnumOfRentals()+1);
                                    update_customer->getListOfRentals().push_back(choosen_item->getID());
                                }
                                else if(choosen_item->getNumOfCopy() == 0){
                                    cout<<"There is no more stock available for this item in stock!";
                                }
                            }
                            else{
                                cout<<"You have enter the wrong item ID";
                            }
                        }
                    }
                    else if(Rentallistchoice == 2){
                        if(update_customer->getcustomerType() == "Guest"){
                            string item_ID;
                            cout<<"List of items that the user currently has: \n";
                            for(int i; i < update_customer->getnumOfRentals(); i++) {
                                cout << this->rs->searchItemID(update_customer->getListOfRentals()[i] + "\n");
                            }
                            cout<<"Please type in the ID of the item that you wish to delete: ";
                            getline(cin, item_ID);
                            if(vl->validateIdItem(item_ID)){
                                bool founditem = false;
                                int position = 0;
                                for(int i = 0; i<items.size(); i++){
                                    if(items[i]->getID() == item_ID){
                                        vector<string> borrowed_item = update_customer->getListOfRentals();
                                        for (int i = 0; i < update_customer->getnumOfRentals(); i++){
                                            if(update_customer->getListOfRentals()[i] == item_ID){
                                                founditem= true;
                                                position = i;
                                            }
                                        }
                                        if(founditem) {
                                            update_customer->getListOfRentals().erase(update_customer->getListOfRentals().begin() + position);
                                            if(this->rs->searchItemID(item_ID)->getNumOfCopy() == 0){
                                                this->rs->searchItemID(item_ID)->setStatus(false);
                                            }
                                            this->rs->searchItemID(item_ID)->setNumOfCopy(this->rs->searchItemID(item_ID)->getNumOfCopy() + 1);
                                            update_customer->setNumOfRentals(update_customer->getnumOfRentals()-1);
                                        }
                                    }
                                    cout << "You have enter wrong item ID!";
                                    break;
                                }
                            }
                            else{
                                cout << "You have enter the wrong item ID!";
                            }
                        }
                        else if(update_customer->getcustomerType() == "Regular"){
                            string item_ID;
                            cout<<"List of items that the user currently has: \n";
                            for(int i; i < update_customer->getnumOfRentals(); i++) {
                                cout << this->rs->searchItemID(update_customer->getListOfRentals()[i] + "\n");
                            }
                            cout<<"Please type in the ID of the item that you wish to delete: ";
                            getline(cin, item_ID);
                            if(vl->validateIdItem(item_ID)){
                                bool founditem = false;
                                int position = 0;
                                for(int i = 0; i<items.size(); i++){
                                    if(items[i]->getID() == item_ID){
                                        vector<string> borrowed_item = update_customer->getListOfRentals();
                                        for (int i = 0; i < update_customer->getnumOfRentals(); i++){
                                            if(update_customer->getListOfRentals()[i] == item_ID){
                                                founditem= true;
                                                position = i;
                                            }
                                        }
                                        if(founditem) {
                                            update_customer->getListOfRentals().erase(update_customer->getListOfRentals().begin() + position);
                                            if(this->rs->searchItemID(item_ID)->getNumOfCopy() == 0){
                                                this->rs->searchItemID(item_ID)->setStatus(false);
                                            }
                                            this->rs->searchItemID(item_ID)->setNumOfCopy(this->rs->searchItemID(item_ID)->getNumOfCopy() + 1);
                                            update_customer->setNumOfRentals(update_customer->getnumOfRentals()-1);
                                        }
                                    }
                                    cout << "You have enter wrong item ID!";
                                    break;
                                }
                            }
                            else{
                                cout << "You have enter the wrong item ID!";
                            }
                        }
                    }
                    break;
                }
                else if(kind == 6){

                }
            }
            else if(update_customer->getcustomerType() == "VIP"){
                cout<<"Choose what kind of data you would like to change: \n"
                      "Note: If you change the rental list section, number of rental will also change accordingly.\n"
                      "1. Name\n"
                      "2. Address\n"
                      "3. Phone\n"
                      "4. Customer type\n"
                      "5. Rental list\n"
                      "6. Reward point\n"
                      "Your choice: ";
                int kind = this->takeChoice(6);
                if(kind == 1){
                    string name;
                    cout<<"Please put in a new name for the customer: ";
                    getline(cin, name);
                    update_customer->setName(name);
                    break;
                }
                else if(kind == 2){
                    string address;
                    cout<<"Please put in a new address for the customer: ";
                    getline(cin, address);
                    update_customer->setName(address);
                    break;
                }
                else if(kind == 3){
                    string Phonenumber;
                    cout<<"Please put in a new phone number for the customer: ";
                    getline(cin, Phonenumber);
                    update_customer->setName(Phonenumber);
                    break;
                }
                else if(kind == 4) {
                    cout << "Warning: If you change the rental type to Game, the genre of the item will be deleted.\n"
                            "Please choose the rental type you want to change to: \n"
                            "1. Guest\n"
                            "2. Regular\n"
                            "3. VIP\n"
                            "Your choice: ";
                    int newcustomertype = this->takeChoice(3);
                    if (newcustomertype == 1) {
                        vector<Customer *> customers;
                        VipAccount *newupdatecustomer = new VipAccount;
                        newupdatecustomer->setAll(
                                update_customer->getID(),
                                update_customer->getName(),
                                update_customer->getAdress(),
                                update_customer->getPhone(),
                                update_customer->getnumOfRentals(),
                                update_customer->getcustomerType(),
                                update_customer->getListOfRentals());
                        newupdatecustomer->setRewardPoint(newupdatecustomer->getnumOfRentals() * 10);
                        customers = this->rs->getCustomers();
                        customers.push_back(newupdatecustomer);// can't delete the old vector or access the old vector
                        this->rs->setCustomers(customers);
                        cout << "The update process has been successful!";
                    } else if (newcustomertype == 2) {
                        vector<Customer *> customers;
                        VipAccount *newupdatecustomer = new VipAccount;
                        newupdatecustomer->setAll(
                                update_customer->getID(),
                                update_customer->getName(),
                                update_customer->getAdress(),
                                update_customer->getPhone(),
                                update_customer->getnumOfRentals(),
                                update_customer->getcustomerType(),
                                update_customer->getListOfRentals());
                        newupdatecustomer->setRewardPoint(newupdatecustomer->getnumOfRentals() * 10);
                        customers = this->rs->getCustomers();
                        customers.push_back(newupdatecustomer);// can't delete the old vector or access the old vector
                        this->rs->setCustomers(customers);
                        cout << "The update process has been successful!";
                    } else if (newcustomertype == 3) {
                        cout << "This account is already a VIP account!";
                    }
                    break;
                }
                else if(kind == 5){
                    vector<Item*> items = this->rs->getItems();
                    this->rs->printAllCustomerSortedID(1);
                    cout<<"Reminder: Making changes in the list of rental item will also affect the number of rental item!\n";
                    cout <<"Please choose what would you like to do with the list of item: \n"
                           "1. Add an item\n"
                           "2. Reduce item\n"
                           "Your choice: ";
                    int Rentallistchoice = this->takeChoice(3);
                    if(Rentallistchoice == 1){
                        string item_ID;
                        cout<<"List of items available: \n";
                        int vid_borrowed = 0;
                        this->rs->printAllItemSortedID(1);
                        cout<<"Please type in the ID of the item that you wish to loan: ";
                        getline(cin, item_ID);
                        if(vl->validateIdItem(item_ID)){
                            Item* choosen_item = this->rs->searchItemID(item_ID);
                            if(choosen_item->getNumOfCopy()>0){
                                choosen_item->setNumOfCopy(choosen_item->getNumOfCopy() - 1);
                                if(choosen_item->getNumOfCopy() == 0){
                                    choosen_item->setStatus(false);
                                }
                                update_customer->setNumOfRentals(update_customer->getnumOfRentals()+1);
                                update_customer->getListOfRentals().push_back(choosen_item->getID());
                                VipAccount* vip = new VipAccount(update_customer);
                                vip->setRewardPoint(vip->getnumOfRentals() + 10);
                            }
                            else if(choosen_item->getNumOfCopy() == 0){
                                cout<<"There is no more stock available for this item in stock!";
                            }
                        }
                    }
                    else if(Rentallistchoice == 2){
                        string item_ID;
                        cout<<"List of items that the user currently has: \n";
                        for(int i; i < update_customer->getnumOfRentals(); i++) {
                            cout << this->rs->searchItemID(update_customer->getListOfRentals()[i] + "\n");
                        }
                        cout<<"Please type in the ID of the item that you wish to delete: ";
                        getline(cin, item_ID);
                        if(vl->validateIdItem(item_ID)){
                            bool founditem = false;
                            int position = 0;
                            for(int i = 0; i<items.size(); i++){
                                if(items[i]->getID() == item_ID){
                                    vector<string> borrowed_item = update_customer->getListOfRentals();
                                    for (int i = 0; i < update_customer->getnumOfRentals(); i++){
                                        if(update_customer->getListOfRentals()[i] == item_ID){
                                            founditem= true;
                                            position = i;
                                        }
                                    }
                                    if(founditem) {
                                        update_customer->getListOfRentals().erase(update_customer->getListOfRentals().begin() + position);
                                        if(this->rs->searchItemID(item_ID)->getNumOfCopy() == 0){
                                            this->rs->searchItemID(item_ID)->setStatus(false);
                                        }
                                        this->rs->searchItemID(item_ID)->setNumOfCopy(this->rs->searchItemID(item_ID)->getNumOfCopy() + 1);
                                        update_customer->setNumOfRentals(update_customer->getnumOfRentals()-1);
                                    }
                                }
                                cout << "You have enter wrong item ID!";
                                break;
                            }
                        }
                        else{
                            cout << "You have enter the wrong item ID!";
                        }
                    }
                }
                else if(kind == 6){
                    string new_reward_point;
                    VipAccount* vip = new VipAccount(update_customer);
                    cout << "The current Reward point that this account has is " + vip->getRewardPoint();
                    cout << "\n Please write the new Reward point that this account has: ";
                    getline(cin, new_reward_point);
                    if(vl->checkInt(new_reward_point)){
                        vip->setRewardPoint(stoi(new_reward_point));
                    }
                }
            }
            break;
        }
    }
}

void Interface::menu3() {
    cout << "1. Promote custormer by ID\n";
    cout << "2. Promote custormer by Name\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);
    if (subChoice == 1) {
        cout << '\n';
        cout << "1. Promote customer from Guest to Regular\n";
        cout << "2. Promote customer from Regular to VIP\n";
        cout << "Your choice [1 - 2]: ";
        int subsubChoice = this->takeChoice(2);
        cout << '\n';
        string word;
        if (subsubChoice == 1) {
            while (true)
            {
                cout << "ID: ";
                getline(cin, word);
                cout << '\n';
                Customer* i1 = this->rs->promoteCusID(word, 0, 0);
                if (i1 != NULL) {
                    cout << i1->toString();
                    break;
                }
            }
        }
        else if (subsubChoice == 2) {
            while (true)
            {
                cout << "ID: ";
                getline(cin, word);
                cout << '\n';
                Customer* i1 = this->rs->promoteCusID(word, 1, 0);
                if (i1 != NULL) {
                    cout << i1->toString();
                    break;
                }
            }
        }
    }
    if (subChoice == 2) {
        cout << '\n';
        cout << "1. Promote customer from Guest to Regular\n";
        cout << "2. Promote customer from Regular to VIP\n";
        cout << "Your choice [1 - 2]: ";
        int subsubChoice = this->takeChoice(2);
        cout << '\n';
        string word;
        if (subsubChoice == 1) {
            while (true)
            {
                cout << "Name: ";
                getline(cin, word);
                cout << '\n';
                Customer* i1 = this->rs->promoteCusID(word, 0, 1);
                if (i1 != NULL) {
                    cout << i1->toString();
                    break;
                }
            }
        }
        else if (subsubChoice == 2) {
            while (true)
            {
                cout << "Name: ";
                getline(cin, word);
                cout << '\n';
                Customer* i1 = this->rs->promoteCusID(word, 1, 1);
                if (i1 != NULL) {
                    cout << i1->toString();
                    break;
                }
            }
        }
    }
}

void Interface::menu4() {
    string cusID;
    string itemID;
    Validation *vl = new Validation();
    vector<Item *> items = this->rs->getItems();
    vector<Customer *> customers = this->rs->getCustomers();
    vector<string> listItems;
    bool found_cus = false;
    bool found_item = false;
    while (true) {
        cout << "Please choose the customer that will be renting an item:\n";
        this->rs->printAllCustomerSortedID(1);
        cout << "Please put in that customer ID: ";
        getline(cin, cusID);
        if (vl->validateIdCus(cusID)) {
            for (int i = 0; i < customers.size(); i++) {
                if (customers[i]->getID() == cusID) {
                    found_cus = true;
                }
            }
            if (found_cus) {
                Customer* cus = this->rs->searchCusID(cusID);
                while (true) {
                    cout << "Please choose the item that customer will be renting an item:\n";
                    this->rs->printAllItemSortedID(1);
                    cout << "Please put in that Item ID: ";
                    getline(cin, itemID);
                    if (vl->validateIdItem(itemID)) {
                        for (int i = 0; i < items.size(); i++) {
                            if (items[i]->getID() == itemID) {
                                found_item = true;
                                break;
                            }
                        }
                        if (found_item) {
                            Item* item = this->rs->searchItemID(itemID);
                            if (cus->getcustomerType() == "Guest") {
                                int vid_borrowed = 0;
                                for (int i = 0; i < items.size(); i++) {
                                    vector<string> borrowed_item = cus->getListOfRentals();
                                    for (int a = 0; a < borrowed_item.size(); a++) {
                                        if (this->rs->searchItemID(borrowed_item[a])->getRentalType() == "Video" &&
                                        this->rs->searchItemID(borrowed_item[a])->getLoanType() == "1-week") {
                                            vid_borrowed += vid_borrowed;
                                        }
                                    }
                                    if (item->getLoanType() == "1-week" &&
                                    item->getRentalType() == "Video" &&
                                    vid_borrowed == 2) {
                                        cout<< "This account have already rent 2 of 1-week type video so this account can not loan more!";
                                    } else if (item->getLoanType() == "2-day" &&
                                    item->getRentalType() == "Video") {
                                        cout << "Guest account can not loan 2-day type video!";
                                    }
                                    else {
                                        if (item->getNumOfCopy() > 0) {
                                            item->setNumOfCopy(items[i]->getNumOfCopy() - 1);
                                            if (item->getNumOfCopy() == 0) {
                                                item->setStatus(false);
                                            }
                                            cus->setNumOfRentals(cus->getnumOfRentals() + 1);
                                            listItems = cus->getListOfRentals();
                                            listItems.push_back(item->getID());
                                            cus->setListOfRentals(listItems);                                        } else if (item->getNumOfCopy() == 0) {
                                            cout << "There is no more stock available for this item in stock!\n";
                                        }
                                    }
                                    cout << "You have enter wrong item ID!\n";
                                    break;
                                }
                            }
                            else if(cus->getcustomerType()== "Regular"){
                                if(item->getNumOfCopy()>0){
                                    item->setNumOfCopy(item->getNumOfCopy() - 1);
                                    if(item->getNumOfCopy() == 0){
                                        item->setStatus(false);
                                    }
                                    cus->setNumOfRentals(cus->getnumOfRentals()+1);
                                    listItems = cus->getListOfRentals();
                                    listItems.push_back(item->getID());
                                    cus->setListOfRentals(listItems);                                }
                                else if(item->getNumOfCopy() == 0){
                                    cout<<"There is no more stock available for this item in stock!\n";
                                }
                            }
                            else if(cus->getcustomerType()== "VIP"){
                                if(item->getNumOfCopy()>0){
                                    item->setNumOfCopy(item->getNumOfCopy() - 1);
                                    if(item->getNumOfCopy() == 0){
                                        item->setStatus(false);
                                    }
                                    cus->setNumOfRentals(cus->getnumOfRentals()+1);
                                    listItems = cus->getListOfRentals();
                                    listItems.push_back(item->getID());
                                    cus->setListOfRentals(listItems);
                                    VipAccount* vip = new VipAccount(cus);
                                    vip->setRewardPoint(vip->getnumOfRentals() + 10);
                                }
                                else if(item->getNumOfCopy() == 0){
                                    cout<<"There is no more stock available for this item in stock!\n";
                                }
                            }
                            break;
                        }
                        else {
                            cout << "You have enter an item's ID that is not in the database!\n";
                        }
                        break;
                    }
                    else {
                        cout << "Please choose again! \n";
                    }
                }
                break;
            }
            else{
                cout << "You have enter a customer's ID that is not in the database!\n";
            }
            break;
        }
        else {
            cout << "Please choose again!\n";
        }
    }
}

void Interface::menu5() {
    cout << "1. Return item for custormer by ID\n";
    cout << "2. Return item for custormer by Name\n";
    cout << "Your choice [1 - 2]:";
    int subChoice = this->takeChoice(2);
    if (subChoice == 1) {
        string word, item;
        while (true)
        {
            cout << "\nID of customer to return: ";
            getline(cin, word);
            cout << "ID of item to return: ";
            getline(cin, item);
            cout << '\n';
            bool newitem = this->rs->returnItem(word, item, 0);
            if (newitem) {
                newitem;
                break;
            }
        }
    }
    if (subChoice == 2) {
        string word, item;
        while (true)
        {
            cout << "\nName of customer to return: ";
            getline(cin, word);
            cout << "ID of item to return: ";
            getline(cin, item);
            cout << '\n';
            bool newitem = this->rs->returnItem(word, item, 1);
            if (newitem) {
                newitem;
                break;
            }
        }
    }
}

void Interface::menu6() {
    cout << "1. Sorted by Title\n";
    cout << "2. Sorted by ID\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);
    cout << '\n';
    cout << "1. Sorted assending\n";
    cout << "2. Sorted desending\n";
    cout << "Your choice [1 - 2]: ";
    if (subChoice == 1) {
        cout << '\n';
        int subsubChoice = this->takeChoice(2);
        if (subsubChoice == 1) {
            this->rs->printAllItemSortedName(0);
        }
        if (subsubChoice == 2) {
            this->rs->printAllItemSortedName(1);
        }
    }
    if (subChoice == 2) {
        cout << '\n';
        int subsubChoice = this->takeChoice(2);
        if (subsubChoice == 1) {
            this->rs->printAllItemSortedID(0);
        }
        if (subsubChoice == 2) {
            this->rs->printAllItemSortedID(1);
        }
    }
}

void Interface::menu7() {
    this->rs->displayNoCopy();
}

void Interface::menu8() {
    cout << "1. Sorted by name\n";
    cout << "2. Sorted by ID\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);
    cout << '\n';
    cout << "1. Sorted assending\n";
    cout << "2. Sorted desending\n";
    cout << "Your choice [1 - 2]: ";
    if (subChoice == 1) {
        cout << '\n';
        int subsubChoice = this->takeChoice(2);
        if (subsubChoice == 1) {
            this->rs->printAllCustomerSortedName(0);
        }
        if (subsubChoice == 2) {
            this->rs->printAllCustomerSortedName(1);
        }
    }
    if (subChoice == 2) {
        cout << '\n';
        int subsubChoice = this->takeChoice(2);
        if (subsubChoice == 1) {
            this->rs->printAllCustomerSortedID(0);
        }
        if (subsubChoice == 2) {
            this->rs->printAllCustomerSortedID(1);
        }
    }
}

void Interface::menu9() {
    cout << "1. Guest\n";
    cout << "2. Regular\n";
    cout << "3. VIP\n";
    cout << "Your choice [1 - 3]: ";
    int subChoice = this->takeChoice(3);
    cout << '\n';

    const char* group[3] = { "Guest", "Regular", "VIP" };
    this->rs->displayGroup(group[subChoice - 1]);
}

void Interface::menu10() {
    cout << "1. Item\n";
    cout << "2. Customer\n";
    cout << "Your choice [1 - 2]: ";
    int subChoice = this->takeChoice(2);

    if (subChoice == 1) {
        cout << '\n';
        cout << "1. ID\n";
        cout << "2. Title\n";
        cout << "Your choice [1 - 2]: ";
        subChoice = this->takeChoice(2);

        this->menu10_1(subChoice);
    }
    else if (subChoice == 2) {
        cout << '\n';
        cout << "1. ID\n";
        cout << "2. Name\n";
        cout << "Your choice [1 - 2]: ";
        subChoice = this->takeChoice(2);

        this->menu10_2(subChoice);
    }
}

void Interface::menu10_1(int subChoice) {
    cout << '\n';
    string word;
    if (subChoice == 1) {
        Item* i1;
        while (true) {
            cout << "ID: ";
            getline(cin, word);
            i1 = this->rs->searchItemID(word);
            if (i1 != NULL) {
                cout << '\n';
                break;
            }
        }
        cout << i1->toString();
    }
    else if (subChoice == 2) {
        vector<Item*> i1;
        while (true) {
            cout << "Title: ";
            getline(cin, word);
            i1 = this->rs->searchItemTitle(word);
            if (i1.size() != 0) {
                cout << '\n';
                break;
            }
        }
        this->rs->display(i1);
    }
}

void Interface::menu10_2(int subChoice) {
    cout << '\n';
    string word;
    if (subChoice == 1) {
        Customer* c1;
        while (true) {
            cout << "ID: ";
            getline(cin, word);
            c1 = this->rs->searchCusID(word);
            if (c1 != NULL) {
                cout << '\n';
                break;
            }
        }
        cout << c1->toString();
    }
    else if (subChoice == 2) {
        vector<Customer*> c1;
        while (true) {
            cout << "Name: ";
            getline(cin, word);
            c1 = this->rs->searchCusName(word);
            if (c1.size() != 0) {
                cout << '\n';
                break;
            }
        }
        this->rs->display(c1);
    }
}

void Interface::option(int menuChoice, RentalShop** rs) {
    this->rs = *rs;
    this->menuChoice = menuChoice;
    cout << '\n';

    switch (menuChoice)
    {
        case 1:
            this->menu1();
            break;
        case 2:
            this->menu2();
            break;
        case 3:
            this->menu3();
            break;
        case 4:
            this->menu4();
            break;
        case 5:
            this->menu5();
            break;
        case 6:
            this->menu6();
            break;
        case 7:
            this->menu7();
            break;
        case 8:
            this->menu8();
            break;
        case 9:
            this->menu9();
            break;
        case 10:
            this->menu10();
            break;
        default:
            break;
    }
    cout << '\n';
}

int Interface::takeChoice(int limit) {
    /*
    Choices are between 1 and limit [1 - limit]
    @param limit: the maximum choice for the input (e.g limit = 3 -> 3 choices)
    */
    while (true) {
        string input;
        int choice;
        getline(cin, input);

        while (cin.fail() || cin.eof() || input.find_first_not_of("0123456789") != string::npos || input.size() == 0) {
            cout << "Require number in range [1 - " << limit << "]: ";
            if (input.find_first_not_of("0123456789") == string::npos || input.size() == 0) {
                cin.clear();
                //cin.ignore(256, '\n');
                //cout << "REACH" << '\n';
            }
            getline(cin, input);
        }

        string::size_type st;
        choice = stoi(input, &st);
        if (choice >= 1 && choice <= limit) {
            return choice;
        }
        else {
            cout << "Number must be in range [1 - " << limit << "]: ";
        }
    }
}