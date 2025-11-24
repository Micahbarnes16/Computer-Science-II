/*
   Name: Micah Barnes
   Date: 11/24/2025
   Course: CSCI 201 - Computer Science II
   Assignment: M04 - Part 2
   Program: Nerf Gun Class and Operator Overloading
   Description:
      defines the nerfGun class.
*/

#ifndef NERFGUN_H
#define NERFGUN_H

#include <string>
#include <iostream>
using namespace std;

class nerfGun {
private:
    string model;
    int range;
    int capacity;
    int dartCount;

public:
    nerfGun(string m, int r, int c);

    string getModel() const;
    int getCapacity() const;
    int getDartCount() const;

    void fire();
    void reload(int quantity);

    bool operator==(const nerfGun& other) const;
    bool operator<(const nerfGun& other) const;

    nerfGun& operator--();       
    nerfGun operator--(int);      
    nerfGun& operator+=(int quantity);

    friend ostream& operator<<(ostream& out, const nerfGun& gun);
};

#endif

