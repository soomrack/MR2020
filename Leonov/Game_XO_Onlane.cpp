#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <clocale>
#include <ctime>
#pragma warning(disable: 4996)

char pole[9] = { '-','-','-','-','-','-','-','-','-' };
int p; // Переменная для обозначения номера клеттке на поле игры.

void computer_step()
{
	srand(time(0)); 
	p = 0 + rand() % 9;
	pole[p] = 'o';
};

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

	if (newConnection == 0) {
		std::cout << "Ошибка\n";
	}
	else {
		std::cout << "Пользователь подключён!\n";
	}

	while (true) {
		recv(newConnection, pole, sizeof(pole), NULL);
		computer_step();
		send(newConnection, pole, sizeof(pole), NULL);
	}

	system("pause");
	return 0;
}