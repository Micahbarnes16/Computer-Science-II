/*  
   Name: Micah Barnes
   Date: 11/17/2025
   Course: CSCI 201 - Computer Science II
   Assignment: Programming Assignment - Arrays and Vectors
   Description: Stores basic PC info such as RAM and storage
*/

#ifndef PERSONALCOMPUTER_H
#define PERSONALCOMPUTER_H

#include <string>
#include <stdexcept>
using namespace std;

class PersonalComputer {
private:
    string manufacturer;
    string formFactor;
    string serialNumber;
    string processor;
    int ram;
    string storageType;
    string storageSize;

    // Helper function to check if RAM is valid
    bool validRAM(int r) {
        int options[] = {4, 6, 8, 16, 32, 64};
        for (int x : options) {
            if (r == x) return true;
        }
        return false;
    }

public:
    // Constructor
    PersonalComputer(string m, string f, string sn,
                     string cpu, int r,
                     string stype, string ssize) 
    {
        if (m.empty()) throw invalid_argument("Manufacturer cannot be empty.");
        if (f.empty()) throw invalid_argument("Form factor cannot be empty.");
        if (sn.empty()) throw invalid_argument("Serial number cannot be empty.");
        if (!validRAM(r)) throw invalid_argument("Invalid RAM amount.");

        manufacturer = m;
        formFactor = f;
        serialNumber = sn;
        processor = cpu;
        ram = r;
        storageType = stype;
        storageSize = ssize;
    }

    // Get functions
    string getManufacturer() const { return manufacturer; }
    string getFormFactor() const { return formFactor; }
    string getSerialNumber() const { return serialNumber; }
    string getProcessor() const { return processor; }
    int getRAM() const { return ram; }
    string getStorageType() const { return storageType; }
    string getStorageSize() const { return storageSize; }

    // Change RAM if valid
    void setRAM(int newRAM) {
        if (!validRAM(newRAM)) {
            throw invalid_argument("Invalid RAM amount.");
        }
        ram = newRAM;
    }

    // Change storage info
    void setStorage(string type, string size) {
        if (type.empty() || size.empty()) {
            throw invalid_argument("Invalid storage values.");
        }
        storageType = type;
        storageSize = size;
    }

    // Return PC info as a single string
    string toString() const {
        string info;
        info = manufacturer + " " + formFactor + " (" + serialNumber + ")\n";
        info += "CPU: " + processor + "\n";
        info += "RAM: " + to_string(ram) + "GB\n";
        info += "Storage: " + storageType + " " + storageSize;
        return info;
    }
};

#endif
