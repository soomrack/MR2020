#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

SOCKET Connection;

char msg_input[256];
char msg_output[256];

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

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";

	
	// прин€ть первое сообщение от сервера
	recv(Connection, msg_input, sizeof(msg_input), NULL);
	std::cout << msg_input << std::endl;
	Sleep(10);

	// цикл прин€ти€ от 2го и отправки 2му клиенту
	while (true) {
		// прин€ть
		recv(Connection, msg_input, sizeof(msg_input), NULL);
		std::cout << msg_input << std::endl;
		Sleep(10);

		// отправить
		std::cin.getline(msg_output, sizeof(msg_output));
		send(Connection, msg_output, sizeof(msg_output), NULL);
		Sleep(10);
	}

	system("pause");
	return 0;
}
