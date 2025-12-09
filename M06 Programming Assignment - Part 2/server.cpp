/*
Name: Micah Barnes
Date: 12/08/2025
Course: CSCI 201 - Computer Science II
Assignment: Networking – State Lookup Server
Program: server.cpp
Description: Single-threaded TCP server that receives a two letter state abbreviation from a client and returns the full state name.
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define close(fd) closesocket(fd)

using namespace std;

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return 1;
    }

    // State abbreviations to full names
    unordered_map<string, string> states = {
        {"AL","Alabama"}, {"AK","Alaska"}, {"AZ","Arizona"}, {"AR","Arkansas"},
        {"CA","California"}, {"CO","Colorado"}, {"CT","Connecticut"},
        {"DE","Delaware"}, {"FL","Florida"}, {"GA","Georgia"},
        {"HI","Hawaii"}, {"ID","Idaho"}, {"IL","Illinois"}, {"IN","Indiana"},
        {"IA","Iowa"}, {"KS","Kansas"}, {"KY","Kentucky"}, {"LA","Louisiana"},
        {"ME","Maine"}, {"MD","Maryland"}, {"MA","Massachusetts"},
        {"MI","Michigan"}, {"MN","Minnesota"}, {"MS","Mississippi"},
        {"MO","Missouri"}, {"MT","Montana"}, {"NE","Nebraska"}, {"NV","Nevada"},
        {"NH","New Hampshire"}, {"NJ","New Jersey"}, {"NM","New Mexico"},
        {"NY","New York"}, {"NC","North Carolina"}, {"ND","North Dakota"},
        {"OH","Ohio"}, {"OK","Oklahoma"}, {"OR","Oregon"}, {"PA","Pennsylvania"},
        {"RI","Rhode Island"}, {"SC","South Carolina"}, {"SD","South Dakota"},
        {"TN","Tennessee"}, {"TX","Texas"}, {"UT","Utah"}, {"VT","Vermont"},
        {"VA","Virginia"}, {"WA","Washington"}, {"WV","West Virginia"},
        {"WI","Wisconsin"}, {"WY","Wyoming"}
    };

    int server_fd, client_fd;
    sockaddr_in server_addr{}, client_addr{};
    int client_len = sizeof(client_addr);

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cerr << "Error creating socket\n";
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(5000);

    // Bind socket to port
    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Bind failed\n";
        return 1;
    }

    // Begin listening for clients
    if (listen(server_fd, 5) < 0) {
        cerr << "Listen failed\n";
        return 1;
    }

    cout << "Server running on port 5000...\n";

    // Service clients one at a time (single-threaded)
    while (true) {
        client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            cerr << "Error accepting client\n";
            continue;
        }

        cout << "Client connected.\n";

        char buffer[3] = {0};

        // Read exactly 2 bytes (state abbreviation)
        int bytes = recv(client_fd, buffer, 2, 0);
        if (bytes <= 0) {
            close(client_fd);
            continue;
        }

        string abbrev(buffer);
        for (char &c : abbrev) c = toupper(c); 

        string response;

        // Lookup state or send error
        if (states.count(abbrev))
            response = states[abbrev];
        else
            response = "ERROR: Invalid state abbreviation";

        // Send result back to client
        send(client_fd, response.c_str(), response.size(), 0);

        close(client_fd);
        cout << "Client disconnected.\n\n";
    }

    close(server_fd);
    WSACleanup();
    return 0;
}
