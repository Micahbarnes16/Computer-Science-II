/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Smart Home Device base implementation + factory deserializer.
*/

#include "SmartDevice.h"
#include "Exceptions.h"
#include "Light.h"
#include "Thermostat.h"
#include "Appliance.h"
#include <sstream>
#include <vector>

SmartDevice::SmartDevice(int id, const std::string& name) : id(id), name(name) {
    if (id <= 0) throw ValidationError("Device ID must be a positive integer.");
    if (name.empty()) throw ValidationError("Device name cannot be empty.");
}

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> parts;
    std::istringstream iss(s);
    std::string token;
    while (std::getline(iss, token, delim)) parts.push_back(token);
    return parts;
}

std::unique_ptr<SmartDevice> SmartDevice::deserialize(const std::string& line) {
    // Format: TYPE|...fields...
    // Light:      LIGHT|id|name|isOn|watt|hours|brightness
    // Thermostat: THERM|id|name|isOn|mode|setTemp|runtimeHours|powerKw
    // Appliance:  APPL|id|name|isOn|applianceType|powerKw|cycles|cycleHours
    auto parts = split(line, '|');
    if (parts.size() < 2) throw ValidationError("Bad device record in file.");

    const std::string& type = parts[0];

    if (type == "LIGHT") {
        if (parts.size() != 7) throw ValidationError("Bad LIGHT record.");
        return Light::fromParts(parts);
    }
    if (type == "THERM") {
        if (parts.size() != 8) throw ValidationError("Bad THERM record.");
        return Thermostat::fromParts(parts);
    }
    if (type == "APPL") {
        if (parts.size() != 8) throw ValidationError("Bad APPL record.");
        return Appliance::fromParts(parts);
    }

    throw ValidationError("Unknown device type in file: " + type);
}
