/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Appliance device derived class.
*/

#ifndef APPLIANCE_H
#define APPLIANCE_H

#include "SmartDevice.h"
#include "Enums.h"
#include <vector>

class Appliance : public SmartDevice {
private:
    ApplianceType type = ApplianceType::Other;
    double powerKw = 1.2;
    int cyclesPerDay = 1;
    double cycleHours = 1.0;

public:
    Appliance(int id, const std::string& name);

    DeviceCategory category() const override { return DeviceCategory::Appliance; }

    void configure() override;
    double dailyKwh() const override;
    void print(std::ostream& os) const override;

    std::string serialize() const override;

    static std::unique_ptr<SmartDevice> fromParts(const std::vector<std::string>& parts);
};

#endif