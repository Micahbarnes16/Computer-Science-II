// Program Name: StereoReceiver.h
// Date: 11/10/2025
// Author: Micah Barnes
// Purpose: Defines a simple StereoReceiver class with basic validation and exception handling.

#ifndef STEREO_RECEIVER_H
#define STEREO_RECEIVER_H

#include <string>
#include <stdexcept>
using namespace std;

class StereoReceiver {
private:
    string manufacturer;
    string model;
    string serialNumber;
    int wattage;
    int channels;
    string band;
    double frequency;
    int volume;
    bool power;
    string inputSource;
    string soundMode;

public:
    StereoReceiver(string man, string mod, string sn, int w, int ch);

    void setBand(string b);
    void setFrequency(double f);
    void setVolume(int v);
    void setInputSource(string s);
    void setSoundMode(string m);
    void powerOn();
    void powerOff();

    void displayInfo();
};

#endif
