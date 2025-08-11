  # Keylogger Project
  # C++ | Client–Server Architecture

OVERVIEW
--------
This project implements a basic keylogger using a client–server
model in C++. The client program (`client.cpp`) captures 
keyboard input and sends it to the server (`server.cpp`),
which logs the received keystrokes to a file.

⚠ DISCLAIMER:
This software is intended strictly for authorized
and educational purposes, such as academic study or
internal security testing. Unauthorized use on
machines or networks you do not own or have consent
to test is unlawful and unethical.

FEATURES
--------
- **Client (client.cpp):**
  - Captures keyboard input from the local machine.
  - Transmits keystroke data to the server over the network.

- **Server (server.cpp):**
  - Listens for incoming client connections.
  - Receives and logs keystroke data into a log file (e.g., `logs.txt`).
  - Optionally supports multiple clients if extended.

REQUIREMENTS
------------
- C++ compiler (GCC/Clang or MSVC).
- Standard C++ libraries plus any OS-specific APIs for key capturing
  (e.g., WinAPI functions on Windows, `X11` or `evdev` on Linux).
- Network sockets support (`<winsock2.h>` for Windows or `<sys/socket.h>`
  and related headers for Linux).
- Basic familiarity with network programming and OS-level input capture.

COMPILATION & USAGE
-------------------
1. Open your terminal or IDE in the project directory.
2. Compile the server:
   - On Linux/Mac:
     ```
     g++ server.cpp -o server
     ```
   - On Windows (MSVC):
     ```
     cl server.cpp /Fe:server.exe
     ```
3. Compile the client:
   - On Linux/Mac:
     ```
     g++ client.cpp -o client
     ```
   - On Windows (MSVC):
     ```
     cl client.cpp /Fe:client.exe
     ```
4. Run the server (make sure it's listening and accessible over the network):
5. Run the client to start capturing and sending keystrokes:
6. Server records received keystrokes into `logs.txt` (or similarly named file).

FILE STRUCTURE
--------------
- `server.cpp` — Handles receiving keystrokes from client(s)
and writing them to a log file.
- `client.cpp` — Captures local keystrokes and sends them
to the server over the network.
- `logs.txt` — Output file where the server stores logged
keystrokes.

