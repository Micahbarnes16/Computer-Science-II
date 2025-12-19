/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Light class implementation (polymorphic kWh calc + validation).
*/

#include "Light.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Light::Light(int id, const std::string& name) : SmartDevice(id, name) {}

void Light::configure() {
    std::cout << "\n--- Configure Light (" << name << ") ---\n";

    int newWatt = watt;
    double newHours = hoursPerDay;
    int newBright = brightness;

    std::cout << "Enter wattage (1-200): ";
    std::cin >> newWatt;
    if (newWatt < 1 || newWatt > 200) throw ValidationError("Wattage must be between 1 and 200.");

    std::cout << "Enter hours used per day (0-24): ";
    std::cin >> newHours;
    if (newHours < 0 || newHours > 24) throw ValidationError("Hours must be between 0 and 24.");

    std::cout << "Enter brightness (0-100): ";
    std::cin >> newBright;
    if (newBright < 0 || newBright > 100) throw ValidationError("Brightness must be 0-100.");

    watt = newWatt;
    hoursPerDay = newHours;
    brightness = newBright;

    std::cout << "Light settings updated.\n";
}

double Light::dailyKwh() const {
    // brightness scales power draw (simple simulation)
    double brightnessFactor = brightness / 100.0;
    double kw = (watt * brightnessFactor) / 1000.0;
    return kw * hoursPerDay;
}

void Light::print(std::ostream& os) const {
    os << "[Light] ID=" << id
       << " Name=\"" << name << "\""
       << " Power=" << (isOn ? "ON" : "OFF")
       << " Watt=" << watt
       << " Bright=" << brightness << "%"
       << " Hours/Day=" << hoursPerDay
       << " EstDaily=" << std::fixed << std::setprecision(3) << dailyKwh() << " kWh";
}

std::string Light::serialize() const {
    std::ostringstream oss;
    oss << "LIGHT|" << id << "|" << name << "|" << (isOn ? 1 : 0)
        << "|" << watt << "|" << hoursPerDay << "|" << brightness;
    return oss.str();
}

std::unique_ptr<SmartDevice> Light::fromParts(const std::vector<std::string>& parts) {
    int id = std::stoi(parts[1]);
    std::string name = parts[2];
    auto d = std::make_unique<Light>(id, name);
    d->isOn = (std::stoi(parts[3]) != 0);
    d->watt = std::stoi(parts[4]);
    d->hoursPerDay = std::stod(parts[5]);
    d->brightness = std::stoi(parts[6]);
    return d;
}