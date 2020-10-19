#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)
char msg[9] = {'-','-','-','-','-','-','-','-','-'};
int cellnumber;

SOCKET Connection;

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

	std::cout << "Enter number of the cell if numbers of cells is\n";
	std::cout << "1	2	3\n";
	std::cout << "4	5	6\n";
	std::cout << "7	8	9\n\n";
	std::cin >> cellnumber;
	msg[cellnumber - 1] = 'x';
	send(Connection, msg, sizeof(msg), NULL);

	while (true) {
		recv(Connection, msg, sizeof(msg), NULL);

		std::cout << "Field\n";
		std::cout << msg[0] << "	" << msg[1] << "	" << msg[2] << "\n";
		std::cout << msg[3] << "	" << msg[4] << "	" << msg[5] << "\n";
		std::cout << msg[6] << "	" << msg[7] << "	" << msg[8] << "\n\n";
			
		std::cout << "Enter number of the cell if numbers of cells is\n";
		std::cout << "1	2	3\n";
		std::cout << "4	5	6\n";
		std::cout << "7	8	9\n\n";

		if ((msg[0] == '0' && msg[1] == '0' && msg[2] == '0')
			|| (msg[3] == '0' && msg[4] == '0' && msg[5] == '0')
			|| (msg[6] == '0' && msg[7] == '0' && msg[8] == '0')
			|| (msg[0] == '0' && msg[3] == '0' && msg[6] == '0')
			|| (msg[1] == '0' && msg[4] == '0' && msg[7] == '0')
			|| (msg[2] == '0' && msg[5] == '0' && msg[8] == '0')
			|| (msg[0] == '0' && msg[4] == '0' && msg[8] == '0')
			|| (msg[2] == '0' && msg[4] == '0' && msg[6] == '0'))
		{
			std::cout << "Oops, You have just lost!\n";
			std::cout << msg[0] << "	" << msg[1] << "	" << msg[2] << "\n";
			std::cout << msg[3] << "	" << msg[4] << "	" << msg[5] << "\n";
			std::cout << msg[6] << "	" << msg[7] << "	" << msg[8] << "\n\n";
			exit(0);
		}

		std::cin >> cellnumber;
		msg[cellnumber - 1] = 'x';

		if ((msg[0] == 'x' && msg[1] == 'x' && msg[2] == 'x')
			|| (msg[3] == 'x' && msg[4] == 'x' && msg[5] == 'x')
			|| (msg[6] == 'x' && msg[7] == 'x' && msg[8] == 'x')
			|| (msg[0] == 'x' && msg[3] == 'x' && msg[6] == 'x')
			|| (msg[1] == 'x' && msg[4] == 'x' && msg[7] == 'x')
			|| (msg[2] == 'x' && msg[5] == 'x' && msg[8] == 'x')
			|| (msg[0] == 'x' && msg[4] == 'x' && msg[8] == 'x')
			|| (msg[2] == 'x' && msg[4] == 'x' && msg[6] == 'x'))
		{
			std::cout << "Congratulations! You won this game!\n";
			std::cout << msg[0] << "	" << msg[1] << "	" << msg[2] << "\n";
			std::cout << msg[3] << "	" << msg[4] << "	" << msg[5] << "\n";
			std::cout << msg[6] << "	" << msg[7] << "	" << msg[8] << "\n\n";
			exit(0);
		}

		send(Connection, msg, sizeof(msg), NULL);
		Sleep(50);	
	}
	system("pause");
	return 0;
}