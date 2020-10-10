#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "ServerXO.h"
using namespace std;
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27027"
#define ADDR "localhost"
//string addr;



class Board
{
public:
	vector <vector <int>> game;
	int currentPlayer = 1;          //-1: "o"-AI   1: "x"-Human
	int winner = 0;
	SOCKET sock;				//client sock (for server)  //connect sock (for client)
	int side = 0;

	void reset()
	{
		game = { {0, 0, 0},
				 {0, 0, 0},
				 {0, 0, 0} };
		currentPlayer = 1;
		winner = 0;
		sock = INVALID_SOCKET;
	}

	void display()      //prints staff
	{
		cout << "State of the game:" << '\n';
		for (int a = 0; a < 3; a++)
		{

			for (int b = 0; b < 3; b++)
			{
				if (game[a][b] == -1 * side)
				{
					cout << " o ";
				}
				else if (game[a][b] == 1* side)
				{
					cout << " x ";
				}
				else { cout << " . "; }
			}

			cout << '\n';
		}
	}

	void begin()        //welcome message 
	{
		reset();
		cout << "Let the game begin! " << '\n';
		cout << "Use numbers to pick spot where to put your 'x'" << '\n';

		cout << " 1  2  3 " << '\n'
			 << " 4  5  6 " << '\n'
			 << " 7  8  9 " << '\n';
	}

	void makeTurn(int turn, int player)     //self-explainatory. No checks included
	{
		game[(turn - 1) / 3][(turn - 1) % 3] = 1 * player;
	}

	bool hasWinner()        //checks if there is winner already
	{
		bool flag = false;
		for (int a = 0; a < 3; a++)
		{
			int row = 0;
			for (int b = 0; b < 3; b++)
			{
				row += game[a][b];          //checking rows
			}

			if (abs(row) == 3) { flag = true; winner = copysign(1, row); break; }
		}
		for (int a = 0; a < 3; a++)
		{
			int column = 0;
			for (int b = 0; b < 3; b++)
			{
				column += game[b][a];           //checking columns
			}

			if (abs(column) == 3) { flag = true; winner = copysign(1, column); break; }
		}
		int diagL = 0;
		for (int a = 0; a < 3; a++)
		{
			diagL += game[a][a];

		}if (abs(diagL) == 3) { flag = true; winner = copysign(1, diagL); }
		int diagR = 0;
		for (int a = 0; a < 3; a++)
		{
			diagR += game[a][2 - a];

		}if (abs(diagR) == 3) { flag = true; winner = copysign(1, diagR); }

		return flag;
	}

	bool isFull()       //checks if all the cells are filled
	{
		bool flag = false;
		int counter = 0;

		for (int a = 0; a < 3; a++)
		{
			for (int b = 0; b < 3; b++)
			{
				counter += abs(game[a][b]);    //checking everything
			}
		}
		if (counter == 9) flag = true;

		return flag;
	}
};

bool checkUser(Board board, int turn)       //checking availability of the cell
{
	bool flag = false;

	if (turn <= 0 || turn >= 10)
	{
		cout << "Wrong coordinate" << '\n'; flag = false;
	}
	else if (abs(board.game[(turn - 1) / 3][(turn - 1) % 3]) == 1)
	{
		flag = false;
		cout << "Oops seems like this spot is already taken" << '\n';
	}
	else { flag = true; }

	return flag;
}

int translateTurn(int intTurn, Board State)
{
	int strTurn;    //ne str no pofig
	if (State.side == -1) strTurn = 200; else strTurn = 100;

	strTurn = strTurn + ((intTurn - 1) / 3)*10 + ((intTurn - 1) % 3);
	return strTurn;
}

int plr(int in)
{
	int plyr;
	if (in / 100 == 2) plyr = -1; else plyr = 1;
	int y = (in % 100) / 10;
	int x = in % 10;
	return 3 * y + x + 1;
}

void game(Board State, int player)  //-1: server-player, 1: client-player
{
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];

	if (State.hasWinner()) { cout << "Happy victory to " << State.winner * State.side; exit; }
	else if (State.isFull()) { cout << "Tie! "; exit; }
	else if (player == -1)
	{
		cout << "Your turn!" << '\n';

		int turn;
		int message;
		do
		{
			State.display();
			cin >> turn;
		} while (!checkUser(State, turn));
		State.makeTurn(turn, 1);
		cout << "New board's ";
		State.display();
		message = translateTurn(turn, State);
		send(State.sock, recvbuf, message, 0);
		cout << "Wait for your opponent..." << '\n';
		game(State, 1);
	}
	else
	{
		//listen(State.sock, SOMAXCONN);
		int inTurn = 0;
		do {
			inTurn = recv(State.sock, recvbuf, recvbuflen, 0);
			inTurn = plr(inTurn);
			if (checkUser(State, inTurn))   //unnecessary 
			{
				cout << "Turn recieved: " ;
				cout << inTurn << '\n';
				State.makeTurn(inTurn, -1);
				State.display();
				game(State, -1);
			}
		} while (inTurn > 0);
	}
}


void cleanShut(SOCKET ClientSocket)
{
	int iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();
}

int reciever(SOCKET ClientSocket, char* recvbuf, int recvbuflen)
{
	int iResult;
	do {
		
		int iSendResult;
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
			iResult = 0;
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);
}

int server()
{
	WSADATA wsaData;
	int iResult;


	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	printf("Addr resolved\n");
	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("Socket set\n");
	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);
	printf("Sync start\n");
	// Receive until the peer shuts down the connection
	reciever(ClientSocket, recvbuf, recvbuflen);

	Board Game;
	Game.reset();
	Game.sock = ClientSocket;
	Game.side = -1;
	game(Game, -1);
	// shutdown the connection since we're done
	cleanShut(ClientSocket);
	return 0;
}

int client()
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	const char *sendbuf = "x 1 3";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ADDR, DEFAULT_PORT, &hints, &result); //argv[1]
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL;ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);   
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);

	// Receive until the peer closes the connection
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			if (iResult == 5) {
				printf("Yay!"); iResult = 0;}
		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0); //

	Board Game;
	Game.reset();
	Game.sock = ConnectSocket;
	Game.side = 1;
	game(Game, 1);

}

void startServer()
{
	cout << "You are a game host. Wait for another player to join." << '\n';
	server();
}
void startClient()
{
	cout << "You are looking for a game on port: " << DEFAULT_PORT << '\n';
	client();
}

void startAI()
{

	//reserved for AI battles
}



void menu()
{
	int input = 0;
	cout << "Welcome to International Tic Tac Toe championsip!" << '\n';
	cout << "Pick your gamemode:" << '\n';
	cout << "1 - Host a game" << '\n';
	cout << "2 - Connect to a game" << '\n';
	cout << "3 - Train with AI" << '\n';
	do
	{
		cin >> input;
	} while ((input != 1 && input != 2 && input != 3));

	switch (input)
	{
		case 1:
			startServer();
			break;
		case 2:
			startClient();
			break;
		case 3:  
			startAI();
			break;
	}
}

int __cdecl main(void)
{
	menu();

	return 0;
}