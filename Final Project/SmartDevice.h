/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Abstract base class for all smart devices (inheritance + polymorphism).
*/

#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include "Enums.h"
#include <string>
#include <ostream>
#include <memory>

class SmartDevice {
protected:
    int id = 0;
    std::string name;
    bool isOn = false;

public:
    SmartDevice(int id, const std::string& name);
    virtual ~SmartDevice() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    bool getIsOn() const { return isOn; }

    void setName(const std::string& n) { name = n; }
    virtual DeviceCategory category() const = 0;

    virtual void togglePower(bool on) { isOn = on; }
    virtual void configure() = 0;

    // Polymorphic daily usage estimate in kWh
    virtual double dailyKwh() const = 0;

    // Print (operator<< uses this)
    virtual void print(std::ostream& os) const = 0;

    // File I/O
    virtual std::string serialize() const = 0;
    static std::unique_ptr<SmartDevice> deserialize(const std::string& line);

    friend std::ostream& operator<<(std::ostream& os, const SmartDevice& d) {
        d.print(os);
        return os;
    }
};

#endif