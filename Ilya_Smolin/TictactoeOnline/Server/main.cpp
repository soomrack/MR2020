#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <stddef.h>

#pragma warning(disable: 4996)

SOCKET Connections[100]; //Массив сокетов
int Counter = 0;

void ClientHandler (int index){
    char msg[256];
    while (true){
        recv(Connections[index], msg,sizeof(msg), 0);
        for (int i = 0; i < Counter; i++) {
            if(i == index){
                continue;
            }
            send (Connections[i], msg, sizeof(msg), 0);
        }
    }
}
int main(int argc, char* argv[]) {
    //WSAStartup
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if(WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    for (int i = 0; i < 100; i++) {
        newConnection = accept(sListen, (SOCKADDR *) &addr, &sizeofaddr);

        if (newConnection == 0) {
            std::cout << "Error #2\n";
        } else {
            std::cout << "Client Connected!\n";
            Connections[i] = newConnection;
            Counter++;
            CreateThread (0,0,(LPTHREAD_START_ROUTINE)ClientHandler,(LPVOID)(i),0,0); //СОздание многопоточности
        }

    }

    system("pause");
    return 0;
}
