//*************************************************************
//  Program Name: StereoReceiver.cpp
//  Date: 11/10/2025
//  Author: Micah Barnes
//  Purpose: Implements the StereoReceiver class and its methods. Includes validation checks and throws exceptions for invalid input values.
//*************************************************************

#include "StereoReceiver.h"
#include <iostream>
using namespace std;

StereoReceiver::StereoReceiver(string man, string mod, string sn, int w, int ch) {
    if (man.empty()) throw invalid_argument("Manufacturer not provided.");
    if (mod.empty()) throw invalid_argument("Model not provided.");
    if (sn.empty()) throw invalid_argument("Serial number not provided.");
    if (w <= 0) throw invalid_argument("Invalid wattage value.");
    if (ch <= 0) throw invalid_argument("Invalid number of channels.");

    manufacturer = man;
    model = mod;
    serialNumber = sn;
    wattage = w;
    channels = ch;
    band = "FM";
    frequency = 99.9;
    volume = 5;
    power = false;
    inputSource = "AUX";
    soundMode = "Stereo";
}

void StereoReceiver::setBand(string b) {
    if (b != "AM" && b != "FM")
        throw invalid_argument("Invalid band. Must be AM or FM.");
    band = b;
}

void StereoReceiver::setFrequency(double f) {
    if (band == "FM" && (f < 87.5 || f > 108.0))
        throw invalid_argument("Invalid FM frequency (87.5 - 108.0).");
    if (band == "AM" && (f < 520 || f > 1710))
        throw invalid_argument("Invalid AM frequency (520 - 1710).");
    frequency = f;
}

void StereoReceiver::setVolume(int v) {
    if (v < 0 || v > 10)
        throw invalid_argument("Volume must be between 0 and 10.");
    volume = v;
}

void StereoReceiver::setInputSource(string s) {
    if (s.empty()) throw invalid_argument("Input source not provided.");
    inputSource = s;
}

void StereoReceiver::setSoundMode(string m) {
    if (m.empty()) throw invalid_argument("Sound mode not provided.");
    soundMode = m;
}

void StereoReceiver::powerOn() { power = true; }
void StereoReceiver::powerOff() { power = false; }

void StereoReceiver::displayInfo() {
    cout << "\n--- Stereo Info ---\n";
    cout << "Manufacturer: " << manufacturer << endl;
    cout << "Model: " << model << endl;
    cout << "Serial: " << serialNumber << endl;
    cout << "Wattage: " << wattage << endl;
    cout << "Channels: " << channels << endl;
    cout << "Band: " << band << endl;
    cout << "Frequency: " << frequency << endl;
    cout << "Volume: " << volume << endl;
    cout << "Power: " << (power ? "On" : "Off") << endl;
    cout << "Input: " << inputSource << endl;
    cout << "Mode: " << soundMode << endl;
}
