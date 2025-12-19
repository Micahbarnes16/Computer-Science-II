/*
Name: Micah Barnes
Date: 12/18/2025
Course: CSCI 201
Assignment: Final Project
Program: Smart Home Device Management System
Description: Custom exception types for validation and invalid operations.
*/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class ValidationError : public std::runtime_error {
public:
    explicit ValidationError(const std::string& msg) : std::runtime_error(msg) {}
};

class InvalidOperation : public std::runtime_error {
public:
    explicit InvalidOperation(const std::string& msg) : std::runtime_error(msg) {}
};

#endif