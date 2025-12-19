/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Enumerations used throughout the project.
*/

#ifndef ENUMS_H
#define ENUMS_H

#include <string>

enum class DeviceCategory { Light, Thermostat, Appliance };

enum class ThermostatMode { Off, Heat, Cool, Auto };

enum class ApplianceType { Washer, Dryer, Dishwasher, Oven, Microwave, Other };

inline std::string toString(DeviceCategory c) {
    switch (c) {
        case DeviceCategory::Light: return "Light";
        case DeviceCategory::Thermostat: return "Thermostat";
        case DeviceCategory::Appliance: return "Appliance";
        default: return "Unknown";
    }
}

inline std::string toString(ThermostatMode m) {
    switch (m) {
        case ThermostatMode::Off: return "Off";
        case ThermostatMode::Heat: return "Heat";
        case ThermostatMode::Cool: return "Cool";
        case ThermostatMode::Auto: return "Auto";
        default: return "Unknown";
    }
}

inline std::string toString(ApplianceType a) {
    switch (a) {
        case ApplianceType::Washer: return "Washer";
        case ApplianceType::Dryer: return "Dryer";
        case ApplianceType::Dishwasher: return "Dishwasher";
        case ApplianceType::Oven: return "Oven";
        case ApplianceType::Microwave: return "Microwave";
        case ApplianceType::Other: return "Other";
        default: return "Unknown";
    }
}

#endif