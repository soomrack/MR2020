#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <ctime>

#pragma warning(disable: 4996)

SOCKET Connection;

char msg_output[256];
char msg_input[256];
char board[10] = { '1','2','3','4','5','6','7','8','9','\n' }; 
bool board_bool[9] = { false, false, false, false, false, false, false, false, false }; // Заполненность поля
bool someone_won = false; // Выиграл ли кто-нибудь
int k = 0; // число ходов

void Start_game() {
	char Hello[256] = "Okey, let's start playing tic-tac-toe with your computer!\nHere is your options: \n _1_|_2_|_3_ \n _4_|_5_|_6_ \n  7 | 8 | 9  \nNow, make the first move!\n";
	// принять первое сообщение от сервера
	recv(Connection, msg_input, sizeof(msg_input), NULL);
	std::cout << msg_input << std::endl;
	Sleep(10);

	// наше первое сообщение 1ому клиенту
	send(Connection, Hello, sizeof(Hello), NULL);
	Sleep(10);
}

void Get_move() {
	// принять
	recv(Connection, msg_input, sizeof(msg_input), NULL);
	std::cout << msg_input << std::endl;
	Sleep(10);

	// обработать, проверить
	int msg_int = atoi(msg_input);
	while (msg_int > 9 || msg_int < 1 || board_bool[msg_int - 1] == true) {
		send(Connection, "Incorrect data. Choose the number between 1 and 9.\n", 51, NULL);
		recv(Connection, msg_input, sizeof(msg_input), NULL);
		msg_int = atoi(msg_input);
	}
	board_bool[msg_int - 1] = true; // сюда мы значится походили
	board[msg_int - 1] = 'x';
	k++;
}

void Get_random_move() { // Это функция (5) делает рандомные ходя за компьютер
	srand(static_cast<unsigned int>(time(0)));
	int random_move;
	random_move = rand() % 8;
	while (board_bool[random_move] == true) {
		random_move = rand() % 8;
	}
	board_bool[random_move] = true; // сюда мы значится походили
	board[random_move] = 'o';
	k++;
}

void Send_board() {
	send(Connection, board, sizeof(board), NULL);
	Sleep(10);
}

bool Сheck_won_bool() { // Эта функция (4) будет проверять, есть ли победитель
	int winners[8][3] = { {0,4,8},{2,4,6},{0,3,6},{1,4,7},{2,5,8},{0,1,2},{3,4,5},{6,7,8} };

	for (int i = 0; i < 8; i++) {
		int one = winners[i][0];
		int two = winners[i][1];
		int three = winners[i][2];
		if ((board_bool[one] == board_bool[two]) && (board_bool[one] == board_bool[three]) && (board_bool[one] == true)) {
			if ((board[one] == board[two]) && (board[one] == board[three])) {
				someone_won = true;
				send(Connection, "\nThe winner is ", 16, NULL);
				char winner[256] = { board[i] };
				send(Connection, winner, 1, NULL);
				return true;
			}
			else if (k == 9) {
				someone_won = true;
				send(Connection, "It's a draw!", 13, NULL);
				return true;
			} else return false;

		}
		else return false;
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

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";

	Start_game(); // показали поле
	// цикл принятия и отправки
	while (someone_won == false) {
		// принять и обработать
		Get_move();
		// проверка
		Сheck_won_bool();
		if (someone_won == false) {
			// ход ноликом (рандом)
			Get_random_move();
			Сheck_won_bool();
		}
		// отправить
		send(Connection, board, sizeof(board), NULL);
		Sleep(10);
	}
	system("pause");
	return 0;
}
