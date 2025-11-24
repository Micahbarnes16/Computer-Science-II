//***************************************************************
// Program Name: Main.cpp
// Author: [Micah Barnes]
// Date: [11/3/2025]
// Purpose: Create and use a StereoReceiver class to manage
//          basic stereo information and settings.
//***************************************************************

#include <iostream>
#include <string>
using namespace std;

class StereoReceiver {
private:
    string manufacturer;
    string model;
    string serialNumber;
    int wattage;
    int channels;
    string band;      // AM or FM
    double frequency; // station
    int volume;       // 0 - 10
    bool power;       // on/off
    string inputSource;  // my own attribute
    string soundMode;    // my own attribute

public:
    // Constructor
    StereoReceiver(string man, string mod, string sn, int w, int ch) {
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

    // Accessors
    string getManufacturer() { return manufacturer; }
    string getModel() { return model; }
    string getSerialNumber() { return serialNumber; }
    int getWattage() { return wattage; }
    int getChannels() { return channels; }
    string getBand() { return band; }
    double getFrequency() { return frequency; }
    int getVolume() { return volume; }
    bool getPower() { return power; }
    string getInputSource() { return inputSource; }
    string getSoundMode() { return soundMode; }

    // Mutators
    void powerOn() { power = true; }
    void powerOff() { power = false; }

    void setVolume(int v) {
        if (v >= 0 && v <= 10)
            volume = v;
        else
            cout << "Volume must be between 0 and 10.\n";
    }

    void setBand(string b) {
        if (b == "AM" || b == "FM")
            band = b;
        else
            cout << "Invalid band. Must be AM or FM.\n";
    }

    void setFrequency(double f) {
        if (f >= 80.0 && f <= 108.0)
            frequency = f;
        else
            cout << "Frequency out of range.\n";
    }

    void setInputSource(string s) { inputSource = s; }
    void setSoundMode(string m) { soundMode = m; }

    // Display receiver info
    void displayInfo() {
        cout << "\n--- Stereo Receiver Information ---\n";
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Model: " << model << endl;
        cout << "Serial Number: " << serialNumber << endl;
        cout << "Wattage: " << wattage << "W\n";
        cout << "Channels: " << channels << endl;
        cout << "Band: " << band << endl;
        cout << "Frequency: " << frequency << endl;
        cout << "Volume: " << volume << endl;
        cout << "Power: " << (power ? "On" : "Off") << endl;
        cout << "Input Source: " << inputSource << endl;
        cout << "Sound Mode: " << soundMode << endl;
    }
};

int main() {
    string manufacturer, model, serial;
    int wattage, channels;

    cout << "Enter manufacturer: ";
    getline(cin, manufacturer);
    cout << "Enter model: ";
    getline(cin, model);
    cout << "Enter serial number: ";
    getline(cin, serial);

    cout << "Enter wattage: ";
    cin >> wattage;
    while (wattage <= 0) {
        cout << "Please enter a positive number: ";
        cin >> wattage;
    }

    cout << "Enter number of channels: ";
    cin >> channels;
    while (channels <= 0) {
        cout << "Please enter a positive number: ";
        cin >> channels;
    }

    // Create receiver object
    StereoReceiver myReceiver(manufacturer, model, serial, wattage, channels);
    myReceiver.displayInfo();

    // Turn on and let user modify
    myReceiver.powerOn();
    cout << "\nStereo is now ON.\n";

    string band;
    cout << "Enter band (AM/FM): ";
    cin >> band;
    myReceiver.setBand(band);

    double freq;
    cout << "Enter frequency (80.0 - 108.0): ";
    cin >> freq;
    myReceiver.setFrequency(freq);

    int vol;
    cout << "Enter volume (0-10): ";
    cin >> vol;
    myReceiver.setVolume(vol);

    string input, mode;
    cout << "Enter input source (AUX, CD, Bluetooth, etc.): ";
    cin >> input;
    myReceiver.setInputSource(input);

    cout << "Enter sound mode (Stereo, Surround, etc.): ";
    cin >> mode;
    myReceiver.setSoundMode(mode);

    myReceiver.displayInfo();

    myReceiver.powerOff();
    cout << "\nStereo is now OFF.\n";

    return 0;
}
