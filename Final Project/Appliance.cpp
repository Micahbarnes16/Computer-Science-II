/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Appliance implementation (type + cycles per day).
*/

#include "Appliance.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Appliance::Appliance(int id, const std::string& name) : SmartDevice(id, name) {}

void Appliance::configure() {
    std::cout << "\n--- Configure Appliance (" << name << ") ---\n";
    std::cout << "Select type: 0=Washer,1=Dryer,2=Dishwasher,3=Oven,4=Microwave,5=Other: ";
    int t;
    std::cin >> t;
    if (t < 0 || t > 5) throw ValidationError("Appliance type must be 0-5.");

    std::cout << "Enter power draw in kW (0.1 - 8.0): ";
    double pk;
    std::cin >> pk;
    if (pk < 0.1 || pk > 8.0) throw ValidationError("Power must be 0.1-8.0 kW.");

    std::cout << "Enter cycles per day (0-20): ";
    int c;
    std::cin >> c;
    if (c < 0 || c > 20) throw ValidationError("Cycles must be 0-20.");

    std::cout << "Enter hours per cycle (0-6): ";
    double ch;
    std::cin >> ch;
    if (ch < 0 || ch > 6) throw ValidationError("Cycle hours must be 0-6.");

    type = static_cast<ApplianceType>(t);
    powerKw = pk;
    cyclesPerDay = c;
    cycleHours = ch;

    std::cout << "Appliance settings updated.\n";
}

double Appliance::dailyKwh() const {
    if (!isOn) return 0.0;
    return powerKw * cycleHours * cyclesPerDay;
}

void Appliance::print(std::ostream& os) const {
    os << "[Appliance] ID=" << id
       << " Name=\"" << name << "\""
       << " Power=" << (isOn ? "ON" : "OFF")
       << " Type=" << toString(type)
       << " kW=" << powerKw
       << " Cycles=" << cyclesPerDay
       << " CycleHours=" << cycleHours
       << " EstDaily=" << std::fixed << std::setprecision(3) << dailyKwh() << " kWh";
}

std::string Appliance::serialize() const {
    std::ostringstream oss;
    oss << "APPL|" << id << "|" << name << "|" << (isOn ? 1 : 0)
        << "|" << static_cast<int>(type)
        << "|" << powerKw
        << "|" << cyclesPerDay
        << "|" << cycleHours;
    return oss.str();
}

std::unique_ptr<SmartDevice> Appliance::fromParts(const std::vector<std::string>& parts) {
    int id = std::stoi(parts[1]);
    std::string name = parts[2];
    auto d = std::make_unique<Appliance>(id, name);
    d->isOn = (std::stoi(parts[3]) != 0);
    d->type = static_cast<ApplianceType>(std::stoi(parts[4]));
    d->powerKw = std::stod(parts[5]);
    d->cyclesPerDay = std::stoi(parts[6]);
    d->cycleHours = std::stod(parts[7]);
    return d;
}