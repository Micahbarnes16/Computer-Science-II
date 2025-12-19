/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Lightd derived class.
*/

#ifndef LIGHT_H
#define LIGHT_H

#include "SmartDevice.h"
#include <vector>

class Light : public SmartDevice {
private:
    int watt = 10;
    double hoursPerDay = 2.0;
    int brightness = 100; // 0-100

public:
    Light(int id, const std::string& name);

    DeviceCategory category() const override { return DeviceCategory::Light; }

    void configure() override;
    double dailyKwh() const override;
    void print(std::ostream& os) const override;

    std::string serialize() const override;

    static std::unique_ptr<SmartDevice> fromParts(const std::vector<std::string>& parts);
};

#endif