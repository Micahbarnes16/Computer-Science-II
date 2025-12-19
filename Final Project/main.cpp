/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Program entry point for the menu-driven smart home controller.
*/

#include "SmartHomeController.h"
#include <iostream>

int main() {
    try {
        SmartHomeController controller;
        controller.run();
    } catch (const std::exception& ex) {
        std::cout << "FATAL ERROR: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}