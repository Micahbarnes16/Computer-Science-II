/*
   Name: Micah Barnes
   Date: 11/17/2025
   Course: CSCI 201 - Computer Science II
   Assignment: M03 - Part 2
   Program 1: Unique Words Using a Set
   Description:
   This program reads words from a text file and stores
   only the unique words in a set. 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <string>
using namespace std;

int main() {
    set<string> uniqueWords;     // holds non-duplicate words
    string word;

    ifstream inputFile("words.txt");  // input file of words

    if (!inputFile.is_open()) {
        cout << "Error: Could not open words.txt" << endl;
        return 1;
    }

    // Read all words from the file into the set
    while (inputFile >> word) {
        uniqueWords.insert(word);
    }

    inputFile.close();

    cout << "Unique words found in file:\n\n";

    // Display all unique words
    for (const string& w : uniqueWords) {
        cout << w << endl;
    }

    return 0;
}
