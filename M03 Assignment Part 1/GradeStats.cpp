/*  
   Name: Micah Barnes
   Date: 11/17/2025
   Course: CSCI 201 - Computer Science II
   Assignment: Programming Assignment - Arrays and Vectors
   Description:
      This program lets the user enter 16 quiz scores.
*/

#include <iostream>
#include <array>
using namespace std;

// Function prototypes
void getData(array<int,16>& quizzes);
int getHighestValue(const array<int,16>& quizzes);
int getLowestValue(const array<int,16>& quizzes);

int main() {
    array<int,16> quizzes;

    // Get all 16 quiz scores from the user
    getData(quizzes);

    cout << "\nFall 2019 Quiz Grades:\n\n";

    int sum = 0;

    // Print each module's score and compute total
    for (int i = 0; i < 16; i++) {
        cout << "Module " << (i + 1) << ": " << quizzes[i] << endl;
        sum += quizzes[i];
    }

    int avg = sum / 16;  
    int highestValue = getHighestValue(quizzes);
    int lowestValue = getLowestValue(quizzes);

    cout << "\nAverage Grade: " << avg << endl;

    // List all modules with the lowest score
    cout << "Your lowest score was " << lowestValue << " in Module(s): ";
    for (int i = 0; i < 16; i++) {
        if (quizzes[i] == lowestValue) {
            cout << (i + 1) << " ";
        }
    }
    cout << endl;

    // List all modules with the highest score
    cout << "Your highest score was " << highestValue << " in Module(s): ";
    for (int i = 0; i < 16; i++) {
        if (quizzes[i] == highestValue) {
            cout << (i + 1) << " ";
        }
    }
    cout << endl;

    return 0;
}

// Reads 16 quiz scores into the array
void getData(array<int,16>& quizzes) {
    for (int i = 0; i < 16; i++) {
        cout << "Enter quiz score for Module " << (i + 1) << ": ";
        cin >> quizzes[i];
    }
}

// Finds the highest score value
int getHighestValue(const array<int,16>& quizzes) {
    int highest = quizzes[0];

    for (int i = 1; i < 16; i++) {
        if (quizzes[i] > highest) {
            highest = quizzes[i];
        }
    }

    return highest;
}

// Finds the lowest score value
int getLowestValue(const array<int,16>& quizzes) {
    int lowest = quizzes[0];

    for (int i = 1; i < 16; i++) {
        if (quizzes[i] < lowest) {
            lowest = quizzes[i];
        }
    }

    return lowest;
}

