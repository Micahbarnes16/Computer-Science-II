/*
Name: Micah Barnes
Date: 12/08/2025
Course: CSCI 201 - Computer Science II
Assignment: Networking – State Lookup Client
Program: client.cpp
Description: TCP client that asks the user for a two letter state abbreviation, sends it to the server, and prints the full state name received.
*/

#include <iostream>
#include <string>
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

    string abbrev;
    cout << "Enter a 2-letter state abbreviation: ";
    cin >> abbrev;

    // Basic validation
    if (abbrev.size() != 2) {
        cout << "Invalid input. Must be exactly 2 letters.\n";
        return 1;
    }

    SOCKET sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == INVALID_SOCKET) {
        cerr << "Error creating socket\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);

    // Convert localhost string to binary IP
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (server_addr.sin_addr.s_addr == INADDR_NONE) {
        cerr << "Invalid server address\n";
        closesocket(sock_fd);
        WSACleanup();
        return 1;
    }

    // Establish connection
    if (connect(sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Connection failed\n";
        closesocket(sock_fd);
        WSACleanup();
        return 1;
    }

    // Send 2 bytes to server
    send(sock_fd, abbrev.c_str(), 2, 0);

    // Buffer for server response
    char buffer[256] = {0};
    int bytes = recv(sock_fd, buffer, 255, 0);

    if (bytes > 0)
        cout << "Server response: " << buffer << endl;
    else
        cout << "No response from server.\n";

    closesocket(sock_fd);
    WSACleanup();
    return 0;
}
