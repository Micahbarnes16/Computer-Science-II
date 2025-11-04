//***************************************************************
// Program Name: Main.cpp
// Author: [Micah Barnes]
// Date: [11/3/2025]
// Purpose: Create a Cube class that calculates and displays volume.
//***************************************************************

#include <iostream>
#include <string>
using namespace std;

class Cube {
private:
    int length;
    int width;
    int height;
    string color;

public:
    // Constructor
    Cube(int l, int w, int h, string c) {
        length = l;
        width = w;
        height = h;
        color = c;
    }

    // Accessors
    int getLength() { return length; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    string getColor() { return color; }

    // Mutators
    void setLength(int l) { length = l; }
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setColor(string c) { color = c; }

    // Calculate volume
    int calculateVolume() {
        return length * width * height;
    }
};

int main() {
    int length, width, height;
    string color;

    cout << "Enter cube length: ";
    cin >> length;
    while (length <= 0) {
        cout << "Please enter a positive number: ";
        cin >> length;
    }

    cout << "Enter cube width: ";
    cin >> width;
    while (width <= 0) {
        cout << "Please enter a positive number: ";
        cin >> width;
    }

    cout << "Enter cube height: ";
    cin >> height;
    while (height <= 0) {
        cout << "Please enter a positive number: ";
        cin >> height;
    }

    cout << "Enter cube color: ";
    cin >> color;

    // Create cube object
    Cube cube1(length, width, height, color);

    // Display cube info
    cout << "\nCube Info:" << endl;
    cout << "Length: " << cube1.getLength() << endl;
    cout << "Width: " << cube1.getWidth() << endl;
    cout << "Height: " << cube1.getHeight() << endl;
    cout << "Color: " << cube1.getColor() << endl;
    cout << "Volume: " << cube1.calculateVolume() << endl;

    // Allow user to change values
    cout << "\nChange cube attributes:" << endl;
    cout << "Enter new length: ";
    cin >> length;
    cout << "Enter new width: ";
    cin >> width;
    cout << "Enter new height: ";
    cin >> height;
    cout << "Enter new color: ";
    cin >> color;

    cube1.setLength(length);
    cube1.setWidth(width);
    cube1.setHeight(height);
    cube1.setColor(color);

    // Display updated info
    cout << "\nUpdated Cube Info:" << endl;
    cout << "Length: " << cube1.getLength() << endl;
    cout << "Width: " << cube1.getWidth() << endl;
    cout << "Height: " << cube1.getHeight() << endl;
    cout << "Color: " << cube1.getColor() << endl;
    cout << "Volume: " << cube1.calculateVolume() << endl;

    return 0;
}
