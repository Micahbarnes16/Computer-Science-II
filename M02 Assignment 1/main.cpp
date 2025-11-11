//*************************************************************
//  main.cpp
//  Date: 11/10/2025
//  Author: Micah Barnes
//  Description: Demonstrates the Date class with user input,
//  valid and invalid values, and try/catch exception handling.
//*************************************************************

#include <iostream>
#include "Date.h"
using namespace std;

int main() {
    int m, d, y;

    cout << "Enter a date (month day year): ";
    cin >> m >> d >> y;

    try {
        Date myDate(m, d, y);
        cout << "Created date: " << myDate.toString() << endl;

        cout << "\nEnter new month: ";
        cin >> m;
        myDate.setMonth(m);

        cout << "Enter new day: ";
        cin >> d;
        myDate.setDay(d);

        cout << "Enter new year: ";
        cin >> y;
        myDate.setYear(y);

        cout << "\nUpdated date: " << myDate.toString() << endl;
    }
    catch (invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nProgram finished successfully." << endl;
    return 0;
}
