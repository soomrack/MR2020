#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <clocale>
#pragma warning(disable: 4996)

using namespace std;

char pole[9] = { '-','-','-','-','-','-','-','-','-' };
int cellnumber;

void table()
{
	cout << "Номера клеток: \n";
	cout << "1 2 3 \n";
	cout << "4 5 6 \n";
	cout << "7 8 9 \n";
	cin >> cellnumber;
};

void writing() {
	cout << pole[0] << " " << pole[1] << " " << pole[2] << " \n";
	cout << pole[3] << " " << pole[4] << " " << pole[5] << " \n";
	cout << pole[6] << " " << pole[7] << " " << pole[8] << " \n";
};

SOCKET Connection;

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

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Ошибка подключения к серверу.\n";
		return 1;
	}
	std::cout << "Подключён!\n";

	void table();
	send(Connection, pole, sizeof(pole), NULL);

	while (true) {

		recv(Connection, pole, sizeof(pole), NULL);

		void writing();

		if (pole[0] == 'o' && pole[1] == 'o' && pole[2] == 'o' ||
			pole[3] == 'o' && pole[4] == 'o' && pole[5] == 'o' ||
			pole[6] == 'o' && pole[7] == 'o' && pole[8] == 'o' ||
			pole[0] == 'o' && pole[3] == 'o' && pole[6] == 'o' ||
			pole[1] == 'o' && pole[4] == 'o' && pole[7] == 'o' ||
			pole[2] == 'o' && pole[5] == 'o' && pole[8] == 'o' ||
			pole[0] == 'o' && pole[4] == 'o' && pole[8] == 'o' ||
			pole[6] == 'o' && pole[4] == 'o' && pole[2] == 'o')
		{
			cout << "Компектор победил \n";
			exit(0);
		}

		std::cin >> cellnumber;
		pole[cellnumber - 1] = 'x';

		if (pole[0] == 'x' && pole[1] == 'x' && pole[2] == 'x' ||
			pole[3] == 'x' && pole[4] == 'x' && pole[5] == 'x' ||
			pole[6] == 'x' && pole[7] == 'x' && pole[8] == 'x' ||
			pole[0] == 'x' && pole[3] == 'x' && pole[6] == 'x' ||
			pole[1] == 'x' && pole[4] == 'x' && pole[7] == 'x' ||
			pole[2] == 'x' && pole[5] == 'x' && pole[8] == 'x' ||
			pole[0] == 'x' && pole[4] == 'x' && pole[8] == 'x' ||
			pole[6] == 'x' && pole[4] == 'x' && pole[2] == 'x')
		{
			cout << "Игрок победил \n";
			exit(0);
		}

		send(Connection, pole, sizeof(pole), NULL);
		Sleep(50);
	}
	system("pause");
	return 0;
}
