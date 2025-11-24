//*************************************************************
//  Program Name: main.cpp
//  Date: 11/10/2025
//  Author: Micah Barnes
//  Purpose: Demonstrates use of the StereoReceiver class, including constructor, mutators, and exception handling with user input and display output.
//*************************************************************

#include "StereoReceiver.h"
#include <iostream>
using namespace std;

int main() {
    try {
        string manufacturer, model, serial;
        string wattageStr, channelsStr;
        string band;
        string freqStr, volumeStr;
        string inputSource, soundMode;

        cout << "Enter manufacturer: ";
        getline(cin, manufacturer);
        cout << "Enter model: ";
        getline(cin, model);
        cout << "Enter serial number: ";
        getline(cin, serial);

        cout << "Enter wattage (integer): ";
        getline(cin, wattageStr);
        cout << "Enter number of channels (integer): ";
        getline(cin, channelsStr);

        cout << "Enter band (AM or FM): ";
        getline(cin, band);
        cout << "Enter frequency (numeric): ";
        getline(cin, freqStr);

        cout << "Enter volume (0-10): ";
        getline(cin, volumeStr);

        cout << "Enter input source: ";
        getline(cin, inputSource);
        cout << "Enter sound mode: ";
        getline(cin, soundMode);

        int wattage = stoi(wattageStr);
        int channels = stoi(channelsStr);
        double frequency = stod(freqStr);
        int volume = stoi(volumeStr);

        StereoReceiver s(manufacturer, model, serial, wattage, channels);
        s.powerOn();
        s.setBand(band);
        s.setFrequency(frequency);
        s.setVolume(volume);
        s.setInputSource(inputSource);
        s.setSoundMode(soundMode);
        s.displayInfo();
    } catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
