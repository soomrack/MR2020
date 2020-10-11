#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <stddef.h>

#pragma warning(disable: 4996)

SOCKET Connection;

void ClientHandler() {
    char msg[256];
    while(true) {
        recv(Connection, msg, sizeof(msg), 0);
        std::cout << msg << std::endl;
    }
}

int main(int argc, char* argv[]) {
    //WSAStartup
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    Connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(Connection, (SOCKADDR *) &addr, sizeof(addr)) != 0) {
        std::cout << "Error: failed connect to server.\n";
        return 1;
    }
    std::cout << "Connected!\n";

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE) ClientHandler, 0, 0, 0);

    char msg1[256];
    while (true) {
        std::cin.getline(msg1, sizeof(msg1));
        send(Connection, msg1, sizeof(msg1), 0);
        Sleep(10);
    }

    system("pause");
    return 0;
}