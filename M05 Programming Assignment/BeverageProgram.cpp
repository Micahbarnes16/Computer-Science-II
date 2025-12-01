/*
Name: Micah Barnes
Date: 12/01/2025
Course: CSCI 201
Assignment: M05 Programming Assignment
Program: BeverageProgram.cpp
Description:
   This program defines a Beverage base class and four derived classes.
   The program creates beverages and allows the user to input a beverage name
   (ex: "Celsius") to display all the information about it.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Beverage {
protected:
    string name;
    string description;
    string servingSize;
    int calories;
    double price;

public:
    Beverage(string n, string d, string ss, int cals, double p)
        : name(n), description(d), servingSize(ss), calories(cals), price(p) {}

    virtual ~Beverage() {}

    string getName() const { return name; }

    virtual string toString() const {
        ostringstream out;
        out << fixed << setprecision(2);

        out << "Name: " << name
            << "\nDescription: " << description
            << "\nServing Size: " << servingSize
            << "\nCalories: " << calories
            << "\nPrice: $" << price;

        return out.str();
    }
};

// ------------------------- Coffee -------------------------

class Coffee : public Beverage {
private:
    string temperature;
    string caffeinated;
    string roastType;
    string strength;
    string creamer;
    string sweetener;

public:
    Coffee(string n, string d, string ss, int cals, double p,
           string temp, string caf, string roast, string str,
           string crm, string swt)
        : Beverage(n, d, ss, cals, p),
          temperature(temp), caffeinated(caf), roastType(roast),
          strength(str), creamer(crm), sweetener(swt) {}

    string toString() const override {
        return string("[Coffee]\n") + Beverage::toString() +
            "\nTemperature: " + temperature +
            "\nCaffeinated: " + caffeinated +
            "\nRoast Type: " + roastType +
            "\nStrength: " + strength +
            "\nCreamer: " + creamer +
            "\nSweetener: " + sweetener + "\n";
    }
};

// ------------------------- Tea -------------------------

class Tea : public Beverage {
private:
    string type;
    string temperature;
    string creamer;
    string sweetener;
    string lemon;

public:
    Tea(string n, string d, string ss, int cals, double p,
        string t, string temp, string crm, string swt, string lem)
        : Beverage(n, d, ss, cals, p),
          type(t), temperature(temp), creamer(crm),
          sweetener(swt), lemon(lem) {}

    string toString() const override {
        return string("[Tea]\n") + Beverage::toString() +
            "\nType: " + type +
            "\nTemperature: " + temperature +
            "\nCreamer: " + creamer +
            "\nSweetener: " + sweetener +
            "\nLemon: " + lemon + "\n";
    }
};

// ------------------------- Soda -------------------------

class Soda : public Beverage {
private:
    string brand;
    string type;
    string diet;

public:
    Soda(string n, string d, string ss, int cals, double p,
         string br, string t, string dt)
        : Beverage(n, d, ss, cals, p), brand(br), type(t), diet(dt) {}

    string toString() const override {
        return string("[Soda]\n") + Beverage::toString() +
            "\nBrand: " + brand +
            "\nType: " + type +
            "\nDiet: " + diet + "\n";
    }
};

// ------------------------- Energy Drink -------------------------

class EnergyDrink : public Beverage {
private:
    string brand;
    string stimulant;
    string sweetener;

public:
    EnergyDrink(string n, string d, string ss, int cals, double p,
                string br, string stim, string swt)
        : Beverage(n, d, ss, cals, p),
          brand(br), stimulant(stim), sweetener(swt) {}

    string toString() const override {
        return string("[Energy Drink]\n") + Beverage::toString() +
            "\nBrand: " + brand +
            "\nStimulant: " + stimulant +
            "\nSweetener: " + sweetener + "\n";
    }
};

// ------------------------- Main Program -------------------------

int main() {
    // Create beverages
    Coffee c1("Mocha Frappe", "Blended chocolate coffee drink", "20 oz", 420, 5.99,
              "Cold", "Yes", "Espresso", "Medium", "Cream", "Sugar");

    Tea t1("English Breakfast Tea", "Strong black tea", "12 oz", 0, 2.50,
           "Black", "Hot", "None", "Honey", "No");

    Soda s1("Dr Pepper", "Cherry soda", "12 oz", 150, 1.79,
            "Dr Pepper", "Cola", "No");

    EnergyDrink e1("Celsius", "Fitness energy drink", "12 oz", 10, 2.99,
                   "Celsius", "Caffeine + Green Tea Extract", "Sucralose");

    // Store in array
    Beverage* drinks[4] = { &c1, &t1, &s1, &e1 };

    string search;
    cout << "Enter a beverage name (Mocha Frappe, English Breakfast Tea, Dr Pepper, Celsius): ";
    getline(cin, search);

    bool found = false;

    for (int i = 0; i < 4; i++) {
        if (drinks[i]->getName() == search) {
            cout << "\n" << drinks[i]->toString() << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nBeverage not found.\n";
    }

    return 0;
}

