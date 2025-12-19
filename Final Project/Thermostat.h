/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Thermostat device derived class.
*/

#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "SmartDevice.h"
#include "Enums.h"
#include <vector>

class Thermostat : public SmartDevice {
private:
    ThermostatMode mode = ThermostatMode::Auto;
    double setTempF = 72.0;
    double runtimeHoursPerDay = 6.0;  // simulated HVAC runtime
    double hvacPowerKw = 3.0;         // simulated power draw

public:
    Thermostat(int id, const std::string& name);

    DeviceCategory category() const override { return DeviceCategory::Thermostat; }

    void configure() override;
    double dailyKwh() const override;
    void print(std::ostream& os) const override;

    std::string serialize() const override;

    // Accessors for UI/display
    double getSetTemp() const { return setTempF; }
    double getRuntime() const { return runtimeHoursPerDay; }
    double getPowerKw() const { return hvacPowerKw; }

    static std::unique_ptr<SmartDevice> fromParts(const std::vector<std::string>& parts);
};

#endif