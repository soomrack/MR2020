#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <clocale>
#include <ctime>
#pragma warning(disable: 4996)

char pole[9] = { '-','-','-','-','-','-','-','-','-' };
int p; // Переменная для обозначения номера клеттке на поле игры.

int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Ошибка" << std::endl;
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
	int sizeofaddr1 = sizeof(addr1);
	addr1.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr1.sin_port = htons(1111);
	addr1.sin_family = AF_INET;

	SOCKET sListen1 = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen1, (SOCKADDR*)&addr1, sizeof(addr1));
	listen(sListen1, SOMAXCONN);

	SOCKET newConnection1;
	newConnection1 = accept(sListen1, (SOCKADDR*)&addr1, &sizeofaddr1);

	if (newConnection == 0) {
		std::cout << "Ошибка\n";
	}
	else {
		std::cout << "Пользователь1 подключён!\n";
	}

	if (newConnection1 == 0) {
		std::cout << "Ошибка\n";
	}
	else {
		std::cout << "Пользователь2 подключён!\n";
	}

	while (true) {
		recv(newConnection, pole, sizeof(pole), NULL);
		send(newConnection1, pole, sizeof(pole), NULL);
		recv(newConnection1, pole, sizeof(pole), NULL);
		send(newConnection, pole, sizeof(pole), NULL);
	}

	system("pause");
	return 0;
}
