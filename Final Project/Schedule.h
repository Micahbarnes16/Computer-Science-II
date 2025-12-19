/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Schedule class for storing device usage windows, includes operator overloading.
*/

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <string>
#include <ostream>

struct TimeWindow {
    int startMin = 0; // minutes from 00:00
    int endMin   = 0; // minutes from 00:00
};

class Schedule {
private:
    std::vector<TimeWindow> windows;

public:
    void addWindow(int startMin, int endMin);
    const std::vector<TimeWindow>& getWindows() const { return windows; }

    // Combine schedules (operator overloading requirement)
    Schedule operator+(const Schedule& other) const;

    // Serialize/deserialize for file I/O
    std::string serialize() const;
    static Schedule deserialize(const std::string& text);

    friend std::ostream& operator<<(std::ostream& os, const Schedule& s);
};

int parseTimeToMinutes(const std::string& hhmm);   // "HH:MM" -> minutes
std::string minutesToTime(int minutes);            // minutes -> "HH:MM"

#endif