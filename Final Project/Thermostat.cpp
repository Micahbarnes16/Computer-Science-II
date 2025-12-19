/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Thermostat class implementation (mode + kWh simulation).
*/

#include "Thermostat.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Thermostat::Thermostat(int id, const std::string& name) : SmartDevice(id, name) {}

void Thermostat::configure() {
    std::cout << "\n--- Configure Thermostat (" << name << ") ---\n";
    std::cout << "Select mode: 0=Off, 1=Heat, 2=Cool, 3=Auto: ";
    int m;
    std::cin >> m;
    if (m < 0 || m > 3) throw ValidationError("Mode must be 0-3.");

    std::cout << "Enter set temperature (50-85 F): ";
    double t;
    std::cin >> t;
    if (t < 50 || t > 85) throw ValidationError("Temperature must be 50-85 F.");

    std::cout << "Enter estimated HVAC runtime hours per day (0-24): ";
    double rh;
    std::cin >> rh;
    if (rh < 0 || rh > 24) throw ValidationError("Runtime must be 0-24 hours.");

    std::cout << "Enter HVAC power draw in kW (0.5 - 10.0): ";
    double pk;
    std::cin >> pk;
    if (pk < 0.5 || pk > 10.0) throw ValidationError("Power must be 0.5-10.0 kW.");

    mode = static_cast<ThermostatMode>(m);
    setTempF = t;
    runtimeHoursPerDay = rh;
    hvacPowerKw = pk;

    std::cout << "Thermostat settings updated.\n";
}

double Thermostat::dailyKwh() const {
    if (mode == ThermostatMode::Off) return 0.0;
    // if device "off", treat as no usage even if configured
    if (!isOn) return 0.0;
    return hvacPowerKw * runtimeHoursPerDay;
}

void Thermostat::print(std::ostream& os) const {
    os << "[Thermostat] ID=" << id
       << " Name=\"" << name << "\""
       << " Power=" << (isOn ? "ON" : "OFF")
       << " Mode=" << toString(mode)
       << " Set=" << setTempF << "F"
       << " Runtime=" << runtimeHoursPerDay << "h/day"
       << " kW=" << hvacPowerKw
       << " EstDaily=" << std::fixed << std::setprecision(3) << dailyKwh() << " kWh";
}

std::string Thermostat::serialize() const {
    std::ostringstream oss;
    oss << "THERM|" << id << "|" << name << "|" << (isOn ? 1 : 0)
        << "|" << static_cast<int>(mode)
        << "|" << setTempF
        << "|" << runtimeHoursPerDay
        << "|" << hvacPowerKw;
    return oss.str();
}

std::unique_ptr<SmartDevice> Thermostat::fromParts(const std::vector<std::string>& parts) {
    int id = std::stoi(parts[1]);
    std::string name = parts[2];
    auto d = std::make_unique<Thermostat>(id, name);
    d->isOn = (std::stoi(parts[3]) != 0);
    d->mode = static_cast<ThermostatMode>(std::stoi(parts[4]));
    d->setTempF = std::stod(parts[5]);
    d->runtimeHoursPerDay = std::stod(parts[6]);
    d->hvacPowerKw = std::stod(parts[7]);
    return d;
}