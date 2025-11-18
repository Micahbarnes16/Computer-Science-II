/*  
   Name: Micah Barnes
   Date: 11/17/2025
   Course: CSCI 201 - Computer Science II
   Assignment: Programming Assignment - Arrays and Vectors
   Part 2: Personal Computer Inventory Program
   Description:
      This program lets the user enter as many personal computers as they want.
      Each PC is stored in a vector, and the program prints the full list at the end.
*/

#include <iostream>
#include <vector>
#include <string>
#include "PersonalComputer.h"
using namespace std;

int main() {
    vector<PersonalComputer> inventory;
    char again = 'y';

    while (again == 'y' || again == 'Y') {

        string man, form, sn, cpu, stype, ssize;
        int ram;

        try {
            // Basic user input for PC details
            cout << "Enter Manufacturer (e.g. Dell, Gateway, etc.): ";
            getline(cin, man);

            cout << "Enter Form Factor (laptop/desktop): ";
            getline(cin, form);

            cout << "Enter Serial Number: ";
            getline(cin, sn);

            cout << "Enter Processor (I3, I5, I7, AMD Ryzen 3, AMD Ryzen 5, etc.): ";
            getline(cin, cpu);

            cout << "Enter RAM (4, 6, 8, 16, 32, or 64GB): ";
            cin >> ram;
            cin.ignore();  // clear leftover newline

            cout << "Enter Storage Type (UFS, SDD, HDD): ";
            getline(cin, stype);

            cout << "Enter Storage Size (128GB, 256GB, 512GB, 1TB, 2TB): ";
            getline(cin, ssize);

            // Create PC object
            PersonalComputer pc(man, form, sn, cpu, ram, stype, ssize);

            // Add to inventory
            inventory.push_back(pc);

            cout << "\nPC added:\n";
            cout << pc.toString() << endl;

            cout << "\nTotal PCs in inventory: " << inventory.size() << endl;
        }
        catch (invalid_argument& e) {
            // If something is wrong, show error message
            cout << "Error: " << e.what() << "\nPlease re-enter this PC.\n\n";
        }

        cout << "\nAdd another PC? (y/n): ";
        cin >> again;
        cin.ignore();
        cout << endl;
    }

    // Print full list
    cout << "\nFULL INVENTORY LIST\n";
    cout << "---------------------\n";

    for (size_t i = 0; i < inventory.size(); i++) {
        cout << "\nPC #" << (i + 1) << ":\n";
        cout << inventory[i].toString() << endl;
    }

    return 0;
}
