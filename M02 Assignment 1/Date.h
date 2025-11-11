//*************************************************************
//  Date.h
//  Date: 11/10/2025
//  Author: Micah Barnes
//  Description: Header file for the Date class that stores
//  month, day, and year with validation and formatted output.
//*************************************************************

#ifndef DATE_H
#define DATE_H

#include <string>
#include <stdexcept>  // For invalid_argument exception
using namespace std;

class Date {
private:
    int month;
    int day;
    int year;

    bool isValidMonth(int m);
    bool isValidDay(int m, int d);
    bool isValidYear(int y);

public:
    // Constructor
    Date(int m, int d, int y);

    // Mutators
    void setMonth(int m);
    void setDay(int d);
    void setYear(int y);

    // Accessor / Formatter
    string toString() const;
};

#endif
