/*
   Name: Micah Barnes
   Date: 11/17/2025
   Course: CSCI 201 - Computer Science II
   Assignment: M03 - Part 2
   Program 2: State Information Using a Map
   Description:
    This program reads state information from a text file and
    allows the user to look up details by state abbreviation.
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

// Structure to hold the state information
struct StateData {
    string longName;
    string governor;
    string flower;
};

int main() {
    map<string, StateData> states;
    ifstream inputFile("states.txt");

    if (!inputFile.is_open()) {
        cout << "Error: Could not open states.txt" << endl;
        return 1;
    }

    string abbrev;
    StateData info;

    // Read each state's four lines from the file
    while (true) {
        if (!getline(inputFile, abbrev)) break;        // abbreviation
        if (!getline(inputFile, info.longName)) break; // long name
        if (!getline(inputFile, info.governor)) break; // governor
        if (!getline(inputFile, info.flower)) break;   // flower

        states[abbrev] = info; // store in map
    }

    inputFile.close();

    // Ask user for abbreviations
    string userAbbrev;
    cout << "Enter a state abbreviation (XX to quit): ";
    cin >> userAbbrev;

    while (userAbbrev != "XX") {
        // Check if the state exists in the map
        if (states.find(userAbbrev) != states.end()) {
            cout << "\nState: " << states[userAbbrev].longName << endl;
            cout << "Governor: " << states[userAbbrev].governor << endl;
            cout << "State Flower: " << states[userAbbrev].flower << endl;
        } 
        else {
            cout << "Error: Invalid state abbreviation.\n";
        }

        cout << "\nEnter a state abbreviation (XX to quit): ";
        cin >> userAbbrev;
    }

    cout << "\nProgram ended.\n";

    return 0;
}

