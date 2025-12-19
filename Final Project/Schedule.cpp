/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Schedule implementation with validation and operator overloading.
*/

#include "Schedule.h"
#include "Exceptions.h"
#include <sstream>
#include <iomanip>
#include <cctype>

static void validateMinutes(int m) {
    if (m < 0 || m > 24 * 60) {
        throw ValidationError("Time must be between 00:00 and 24:00.");
    }
}

void Schedule::addWindow(int startMin, int endMin) {
    validateMinutes(startMin);
    validateMinutes(endMin);

    if (endMin <= startMin) {
        throw ValidationError("End time must be after start time.");
    }

    windows.push_back({startMin, endMin});
}

Schedule Schedule::operator+(const Schedule& other) const {
    Schedule combined;
    for (const auto& w : windows) combined.windows.push_back(w);
    for (const auto& w : other.windows) combined.windows.push_back(w);
    return combined;
}

std::string Schedule::serialize() const {
    // Format: start-end,start-end  (minutes)
    std::ostringstream oss;
    for (size_t i = 0; i < windows.size(); i++) {
        oss << windows[i].startMin << "-" << windows[i].endMin;
        if (i + 1 < windows.size()) oss << ",";
    }
    return oss.str();
}

Schedule Schedule::deserialize(const std::string& text) {
    Schedule s;
    if (text.empty()) return s;

    std::istringstream iss(text);
    std::string token;
    while (std::getline(iss, token, ',')) {
        auto dash = token.find('-');
        if (dash == std::string::npos) continue;
        int start = std::stoi(token.substr(0, dash));
        int end   = std::stoi(token.substr(dash + 1));
        s.addWindow(start, end);
    }
    return s;
}

std::ostream& operator<<(std::ostream& os, const Schedule& s) {
    if (s.windows.empty()) {
        os << "(no schedule)";
        return os;
    }
    for (size_t i = 0; i < s.windows.size(); i++) {
        os << minutesToTime(s.windows[i].startMin) << " - " << minutesToTime(s.windows[i].endMin);
        if (i + 1 < s.windows.size()) os << ", ";
    }
    return os;
}

int parseTimeToMinutes(const std::string& hhmm) {
    // Accept "H:MM" or "HH:MM"
    int h = 0, m = 0;
    char colon = '\0';
    std::istringstream iss(hhmm);
    iss >> h >> colon >> m;

    if (!iss || colon != ':') {
        throw ValidationError("Time format must be HH:MM (example: 07:30).");
    }
    if (h < 0 || h > 24 || m < 0 || m > 59) {
        throw ValidationError("Time is out of range.");
    }
    if (h == 24 && m != 0) {
        throw ValidationError("24:00 is allowed, but 24:xx is not.");
    }
    return h * 60 + m;
}

std::string minutesToTime(int minutes) {
    if (minutes < 0) minutes = 0;
    if (minutes > 24 * 60) minutes = 24 * 60;

    int h = minutes / 60;
    int m = minutes % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << h
        << ":" << std::setw(2) << std::setfill('0') << m;
    return oss.str();
}