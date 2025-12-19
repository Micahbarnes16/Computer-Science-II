/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Controls device management, scheduling, file saving/loading.
*/

#include "SmartHomeController.h"
#include "Exceptions.h"
#include "Light.h"
#include "Thermostat.h"
#include "Appliance.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

// Utility: clear bad input
static void clearCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Find device by ID
SmartDevice* SmartHomeController::findDeviceById(int id) {
    for (auto& d : devices) {
        if (d->getId() == id)
            return d.get();
    }
    return nullptr;
}

// Check if ID exists
bool SmartHomeController::idExists(int id) const {
    for (const auto& d : devices) {
        if (d->getId() == id)
            return true;
    }
    return false;
}

// ================= MENU LOOP =================
void SmartHomeController::run() {
    bool running = true;

    while (running) {
        std::cout << "\n====================================\n";
        std::cout << " SMART HOME DEVICE MANAGER\n";
        std::cout << "====================================\n";
        std::cout << "1) Add Device\n";
        std::cout << "2) List Devices\n";
        std::cout << "3) Configure Device\n";
        std::cout << "4) Toggle Device Power\n";
        std::cout << "5) Add / Combine Schedule\n";
        std::cout << "6) Show Daily Usage Stats\n";
        std::cout << "7) Save Smart Home System\n";
        std::cout << "8) Load Smart Home System\n";
        std::cout << "9) Exit\n";
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;

        if (!std::cin) {
            clearCin();
            continue;
        }

        try {
            switch (choice) {
                case 1: addDevice(); break;
                case 2: listDevices(); break;
                case 3: configureDevice(); break;
                case 4: toggleDevicePower(); break;
                case 5: addSchedule(); break;
                case 6: showUsageStats(); break;
                case 7: {
                    std::cout << "Enter filename to save: ";
                    std::string f;
                    std::cin >> f;
                    saveToFile(f);
                    std::cout << "\nSystem saved successfully.\n";
                    break;
                }
                case 8: {
                    std::cout << "Enter filename to load: ";
                    std::string f;
                    std::cin >> f;
                    loadFromFile(f);
                    break;
                }
                case 9:
                    running = false;
                    break;
                default:
                    std::cout << "Invalid menu option.\n";
            }
        }
        catch (const std::exception& ex) {
            std::cout << "ERROR: " << ex.what() << "\n";
            clearCin();
        }
    }
}

// ================= ADD DEVICE =================
void SmartHomeController::addDevice() {
    std::cout << "\n--- Add New Device ---\n";
    std::cout << "1) Light\n2) Thermostat\n3) Appliance\n";
    std::cout << "Choose device type: ";

    int type;
    std::cin >> type;
    if (type < 1 || type > 3)
        throw ValidationError("Invalid device type.");

    std::cout << "Enter device ID: ";
    int id;
    std::cin >> id;
    if (id <= 0 || idExists(id))
        throw ValidationError("Device ID must be unique and positive.");

    clearCin();
    std::cout << "Enter device name: ";
    std::string name;
    std::getline(std::cin, name);
    if (name.empty())
        throw ValidationError("Device name cannot be empty.");

    std::unique_ptr<SmartDevice> device;
    if (type == 1) device = std::make_unique<Light>(id, name);
    if (type == 2) device = std::make_unique<Thermostat>(id, name);
    if (type == 3) device = std::make_unique<Appliance>(id, name);

    device->togglePower(true);

    std::cout << "Configure now? (y/n): ";
    char yn;
    std::cin >> yn;
    if (yn == 'y' || yn == 'Y')
        device->configure();

    devices.push_back(std::move(device));
    std::cout << "Device added.\n";
}

// ================= LIST DEVICES =================
void SmartHomeController::listDevices() const {
    std::cout << "\n====================================\n";
    std::cout << " REGISTERED DEVICES\n";
    std::cout << "====================================\n";

    if (devices.empty()) {
        std::cout << "No devices registered.\n";
        return;
    }

    for (const auto& d : devices) {
        std::cout << *d << "\n";
    }
}

// ================= CONFIGURE DEVICE =================
void SmartHomeController::configureDevice() {
    std::cout << "Enter device ID to configure: ";
    int id;
    std::cin >> id;

    SmartDevice* d = findDeviceById(id);
    if (!d)
        throw InvalidOperation("Device not found.");

    d->configure();
}

// ================= TOGGLE POWER =================
void SmartHomeController::toggleDevicePower() {
    std::cout << "Enter device ID: ";
    int id;
    std::cin >> id;

    SmartDevice* d = findDeviceById(id);
    if (!d)
        throw InvalidOperation("Device not found.");

    std::cout << "Set power (1=ON, 0=OFF): ";
    int p;
    std::cin >> p;
    if (p != 0 && p != 1)
        throw ValidationError("Invalid power value.");

    d->togglePower(p == 1);
    std::cout << "Power updated." << "\n";
}

// ================= SCHEDULES =================
void SmartHomeController::addSchedule() {
    std::cout << "Enter device ID to add schedule: ";
    int id;
    std::cin >> id;

    SmartDevice* d = findDeviceById(id);
    if (!d)
        throw InvalidOperation("Device not found.");

    clearCin();
    std::cout << "Enter time windows (HH:MM-HH:MM). Enter blank line to finish." << "\n";
    Schedule newSch;
    while (true) {
        std::cout << "Window (or blank to finish): ";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) break;
        auto dash = line.find('-');
        if (dash == std::string::npos) {
            std::cout << "Invalid format." << "\n";
            continue;
        }
        try {
            int s = parseTimeToMinutes(line.substr(0, dash));
            int e = parseTimeToMinutes(line.substr(dash + 1));
            newSch.addWindow(s, e);
            std::cout << "Added window " << line << "." << "\n";
        } catch (const std::exception& ex) {
            std::cout << "ERROR: " << ex.what() << "\n";
        }
    }

    if (newSch.getWindows().empty()) {
        std::cout << "No windows were added; aborting." << "\n";
        return;
    }

    auto it = schedulesByDeviceId.find(id);
    if (it == schedulesByDeviceId.end()) {
        schedulesByDeviceId[id] = newSch;
    } else {
        std::cout << "Device already has a schedule. Combine (c) or Replace (r)? ";
        char c;
        std::cin >> c;
        if (c == 'c' || c == 'C') {
            it->second = it->second + newSch;
        } else if (c == 'r' || c == 'R') {
            it->second = newSch;
        } else {
            std::cout << "Aborted schedule update." << "\n";
            clearCin();
            return;
        }
    }

    std::cout << "Schedule updated. Current schedule: " << schedulesByDeviceId[id] << "\n";
}

// ================= USAGE STATS =================
void SmartHomeController::showUsageStats() const {
    std::cout << "\n====================================\n";
    std::cout << " DAILY ENERGY USAGE (ESTIMATED)\n";
    std::cout << "====================================\n";

    double total = 0.0;
    for (const auto& d : devices) {
        double kwh = d->dailyKwh();
        total += kwh;
        std::cout << d->getName() << " : "
                  << std::fixed << std::setprecision(2)
                  << kwh << " kWh/day\n";
    }

    std::cout << "------------------------------------\n";
    std::cout << "TOTAL: " << total << " kWh/day\n";
}

// ================= SAVE =================
void SmartHomeController::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out)
        throw InvalidOperation("Could not open file.");

    out << "[DEVICES]\n";
    for (const auto& d : devices)
        out << d->serialize() << "\n";

    out << "[SCHEDULES]\n";
    for (const auto& s : schedulesByDeviceId)
        out << "SCH|" << s.first << "|" << s.second.serialize() << "\n";
}

// ================= LOAD (HUMAN READABLE) =================
void SmartHomeController::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in)
        throw InvalidOperation("Could not open file.");

    devices.clear();
    schedulesByDeviceId.clear();

    std::string line;
    bool readingDevices = false;

    while (getline(in, line)) {
        if (line == "[DEVICES]") {
            readingDevices = true;
            continue;
        }
        if (line == "[SCHEDULES]") {
            readingDevices = false;
            continue;
        }
        if (readingDevices && !line.empty()) {
            devices.push_back(SmartDevice::deserialize(line));
        }
    }

    // -------- HUMAN READABLE SUMMARY --------
    std::cout << "\n====================================\n";
    std::cout << " SYSTEM LOADED SUCCESSFULLY\n";
    std::cout << "====================================\n";

    for (const auto& d : devices) {
        if (d->category() == DeviceCategory::Thermostat) {
            const Thermostat* t = dynamic_cast<const Thermostat*>(d.get());
            if (t) {
                std::cout << "Thermostat: " << t->getName() << "\n";
                std::cout << "  Set Temp   : " << t->getSetTemp() << " F\n";
                std::cout << "  Runtime    : " << t->getRuntime() << " hours/day\n";
                std::cout << "  Power Draw : " << t->getPowerKw() << " kW\n";
                std::cout << "  Usage      : "
                          << t->dailyKwh() << " kWh/day\n\n";
            }
        } else {
            std::cout << *d << "\n\n";
        }
    }
}