//*************************************************************
//  Date.cpp
//  Date: 11/10/2025
//  Author: Micah Barnes
//  Description: Implementation of the Date class functions.
//*************************************************************

#include "Date.h"
#include <sstream>  // For ostringstream
#include <iostream> // For debugging (optional)

// Helper function: checks valid month (1–12)
bool Date::isValidMonth(int m) {
    return (m >= 1 && m <= 12);
}

// Helper function: checks valid day for given month (no leap years)
bool Date::isValidDay(int m, int d) {
    int daysInMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    return (d >= 1 && d <= daysInMonth[m]);
}

// Helper function: checks valid year range
bool Date::isValidYear(int y) {
    return (y >= 1900 && y <= 2020);
}

// Constructor with validation
Date::Date(int m, int d, int y) {
    if (!isValidMonth(m))
        throw invalid_argument("Invalid month: must be between 1 and 12.");
    if (!isValidDay(m, d))
        throw invalid_argument("Invalid day for that month.");
    if (!isValidYear(y))
        throw invalid_argument("Invalid year: must be between 1900 and 2020.");
    month = m;
    day = d;
    year = y;
}

// Mutator: set month
void Date::setMonth(int m) {
    if (!isValidMonth(m))
        throw invalid_argument("Invalid month: must be between 1 and 12.");
    month = m;
}

// Mutator: set day
void Date::setDay(int d) {
    if (!isValidDay(month, d))
        throw invalid_argument("Invalid day for that month.");
    day = d;
}

// Mutator: set year
void Date::setYear(int y) {
    if (!isValidYear(y))
        throw invalid_argument("Invalid year: must be between 1900 and 2020.");
    year = y;
}

// Formats the date as "Month DD, YYYY"
string Date::toString() const {
    string months[13] = { "", "January","February","March","April","May","June",
        "July","August","September","October","November","December" };

    ostringstream out;
    out << months[month] << " " << day << ", " << year;
    return out.str();
}
