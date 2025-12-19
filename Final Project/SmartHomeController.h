/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Controller class managing devices, schedules, navigation, and file I/O.
*/

#ifndef SMARTHOMECONTROLLER_H
#define SMARTHOMECONTROLLER_H

#include "SmartDevice.h"
#include "Schedule.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

class SmartHomeController {
private:
    std::vector<std::unique_ptr<SmartDevice>> devices;           // Data structure #1
    std::unordered_map<int, Schedule> schedulesByDeviceId;       // Data structure #2

    SmartDevice* findDeviceById(int id);
    bool idExists(int id) const;

public:
    void run();

    void addDevice();
    void listDevices() const;
    void configureDevice();
    void toggleDevicePower();
    void addSchedule();
    void showUsageStats() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif