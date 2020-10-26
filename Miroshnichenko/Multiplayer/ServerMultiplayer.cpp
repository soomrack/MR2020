#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

char msg[9] = { '-','-','-','-','-','-','-','-','-' };

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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	SOCKADDR_IN addr1;
	int sizeofaddr = sizeof(addr1);
	addr1.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr1.sin_port = htons(1111);
	addr1.sin_family = AF_INET;

	SOCKET sListen1 = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen1, (SOCKADDR*)&addr1, sizeof(addr1));
	listen(sListen1, SOMAXCONN);

	SOCKET newConnection1;
	newConnection1 = accept(sListen1, (SOCKADDR*)&addr1, &sizeofaddr);


	if (newConnection == 0) {
		std::cout << "Error #2\n";
	}
	else {
		std::cout << "Client Connected!\n";
	}

	if (newConnection1 == 0) {
		std::cout << "Error #2\n";
	}
	else {
		std::cout << "Client2 Connected!\n";
	}

	while (true) {
		recv(newConnection, msg, sizeof(msg), NULL);
		send(newConnection1, msg, sizeof(msg), NULL);
		recv(newConnection1, msg, sizeof(msg), NULL);
		send(newConnection, msg, sizeof(msg), NULL);
	}

	system("pause");
	return 0;