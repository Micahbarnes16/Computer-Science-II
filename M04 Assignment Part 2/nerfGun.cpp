/*
   Name: Micah Barnes
   Date: 11/24/2025
   Course: CSCI 201 - Computer Science II
   Assignment: M04 - Part 2
   Program: Nerf Gun Class and Operator Overloading
   Description:
      This file implements all nerfGun member functions.
      Includes firing, reloading, operator overloads, and
      exception handling for underflow and overflow.
*/

#include "nerfGun.h"
#include <stdexcept>

nerfGun::nerfGun(string m, int r, int c) {
    if (c > 144)
        throw invalid_argument("Invalid capacity – must be <= 144.");

    model = m;
    range = r;
    capacity = c;
    dartCount = c;   // fully loaded
}

string nerfGun::getModel() const { return model; }
int nerfGun::getCapacity() const { return capacity; }
int nerfGun::getDartCount() const { return dartCount; }

void nerfGun::fire() {
    if (dartCount <= 0)
        throw underflow_error("Underflow – cannot fire with zero darts.");
    dartCount--;
}

void nerfGun::reload(int quantity) {
    if (dartCount + quantity > capacity)
        throw overflow_error("Overflow – too many darts for this gun.");
    dartCount += quantity;
}

bool nerfGun::operator==(const nerfGun& other) const {
    return dartCount == other.dartCount;
}

bool nerfGun::operator<(const nerfGun& other) const {
    return dartCount < other.dartCount;
}

nerfGun& nerfGun::operator--() {
    fire();
    return *this;
}

nerfGun nerfGun::operator--(int) {
    nerfGun temp = *this;
    fire();
    return temp;
}

nerfGun& nerfGun::operator+=(int quantity) {
    reload(quantity);
    return *this;
}

ostream& operator<<(ostream& out, const nerfGun& gun) {
    out << "Model: " << gun.model
        << " | Range: " << gun.range
        << " | Capacity: " << gun.capacity
        << " | Darts: " << gun.dartCount;
    return out;
}
