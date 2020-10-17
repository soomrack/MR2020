#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27027"
#define ADDR "localhost"
//string addr;

namespace Dannie {
    int a[3][3];
    int stolb;
    int str;
    SOCKET sock;
    int side;
}
void sozdpole(){  //создаем поле
    using namespace Dannie;
    int i=0;
    int j=0;
    while (i<3){
        while (j<3){
            a[i][j]=1;
            j++;
        }
        i++;
        j=0;
        sock = INVALID_SOCKET;
    }
}
void vvodstolb(){ // ввод столбика
    using namespace Dannie;
    printf("Vvedite stolbets\n");
    scanf("%d", &stolb);
    stolb=stolb-1;
}
void vvodstr(){ // ввод строчки
    using namespace Dannie;
    printf("Vvedite stroku\n");
    scanf("%d", &str);
    str=str-1;
}
int perevod () { // кодировка столбика и строчки в одно число
                // чтобы передать оба данных одним разом
    using namespace Dannie;
    int per = (stolb+1) * 10 + str;
    return per;
}
int vozvrat (int message) { // расшифровка закодированных чисел
    using namespace Dannie;
    str = message % 10;
    stolb = ((message - str) / 10)-1;
}
void vivodpolya(){ //вывод поля игроку
    using namespace Dannie;
    int i=0;
    int j=0;
    while (i<3){
        printf("|");
        while (j<3) {
            if (a[i][j] == 1)
                printf(" ");
            if (a[i][j] == 2)
                printf("X");
            if (a[i][j] == 0)
                printf("O");
            printf("|");
            j++;
        }
        printf("\n");
        i++;
        j=0;
    }
}
void korrpole(int side){ //изменение поля согласно введенным данным
    using namespace Dannie;
    B:  vvodstolb();
    vvodstr();
    if ((a[str][stolb]!=1) | (stolb>2) | (str>2) | (stolb<0) | (str<0)) {
        printf("Vvedite korrektnye dannye\n");
        vivodpolya();
        goto B;
    }
    if (side % 2 == 0)
        a[str][stolb]= 2;
    if (side % 2 == 1)
        a[str][stolb]=0;
}
void korrpole2 (int side){ // изменение поля при получении данных
    using namespace Dannie;
    if (side % 2 == 0)
        a[str][stolb]= 2;
    if (side % 2 == 1)
        a[str][stolb]=0;
}
int w (){ //проверка победы игрока 1
    using namespace Dannie;
    int pw1=0;
    if ((a[0][0]==2) && (a[0][1]==2) && (a[0][2]==2))
        pw1=1;
    if ((a[1][0]==2) && (a[1][1]==2) && (a[1][2]==2))
        pw1=1;
    if ((a[2][0]==2) && (a[2][1]==2) && (a[2][2]==2))
        pw1=1;
    if ((a[0][0]==2) && (a[1][0]==2) && (a[2][0]==2))
        pw1=1;
    if ((a[0][1]==2) && (a[1][1]==2) && (a[2][1]==2))
        pw1=1;
    if ((a[0][2]==2) && (a[1][2]==2) && (a[2][2]==2))
        pw1=1;
    if ((a[0][0]==2) && (a[1][1]==2) && (a[2][2]==2))
        pw1=1;
    if ((a[2][0]==2) && (a[1][1]==2) && (a[0][2]==2))
        pw1=1;
    return pw1;
}
int l(){ //проверка победы игрока 2
    using namespace Dannie;
    int pw2=0;
    if ((a[0][0]==0) && (a[0][1]==0) && (a[0][2]==0))
        pw2=1;
    if ((a[1][0]==0) && (a[1][1]==0) && (a[1][2]==0))
        pw2=1;
    if ((a[2][0]==0) && (a[2][1]==0) && (a[2][2]==0))
        pw2=1;
    if ((a[0][0]==0) && (a[1][0]==0) && (a[2][0]==0))
        pw2=1;
    if ((a[0][1]==0) && (a[1][1]==0) && (a[2][1]==0))
        pw2=1;
    if ((a[0][2]==0) && (a[1][2]==0) && (a[2][2]==0))
        pw2=1;
    if ((a[0][0]==0) && (a[1][1]==0) && (a[2][2]==0))
        pw2=1;
    if ((a[2][0]==0) && (a[1][1]==0) && (a[0][2]==0))
        pw2=1;
    return pw2;
}
void nichya() { // проверка ничьи
    using namespace Dannie;
    if (side == 11) {
        printf("Pobedila drujba!");
        exit(0);
    }
}
void proverkaw1() { //Если игрок 1 победил
    int p1w = w();
    if (p1w == 1) {
        printf("Igrok 1 pobedil!\n");
        exit(0);
    }
}
void proverkaw2(){ //Если игрок 2 победил
    int p2w = l();
    if (p2w == 1) {
        printf("Igrok 2 pobedil!\n");
        exit(0);
    }
}
void proverkontsa(){ //Все условия конца игры собранные воедино
    proverkaw1();
    proverkaw2();
    nichya();
}
void game(int player)  // Как проходит игра
{                     // player проверяет, какой игрок начинает 1, а какой 2
    C: using namespace Dannie;
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];
    if (player == 1) { // Игрок делает ход, передает данные, переходит в режим их получения
        side++;
        proverkontsa();
        printf("Vash hod!\n");
        vivodpolya();
        korrpole(side);
        int message = perevod();
        send(sock, recvbuf, message, 0);
        player = 2;
    }
    if (player == 2) {// Игрок получает данные, выводит себе поле и переходит в режим их передачи
        vivodpolya();
        side++;
        proverkontsa();
        printf("Hod opponenta...\n");
        A: int poluch=0;
        poluch = recv(sock, recvbuf, recvbuflen, 0);
        if (poluch == 0)
            goto A;
        vozvrat(poluch);
        korrpole2(side);
        vivodpolya();
        player = 1;
        goto C;
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
    using namespace Dannie;
    sozdpole();
    sock = ClientSocket;
    int player = 1;
    side = 1;
    game(player);
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
                printf("Yay!\n"); iResult = 0;}
        }
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0); //
    using namespace Dannie;
    sozdpole();
    sock = ConnectSocket;
    int player = 2;
    side = 1;
    game(player);
}

void startServer()
{
    printf("Podojdite drugogo igroka\n");
    server();
}
void startClient()
{
    printf("Jdite podklyucheniya hosta");
    client();
}
void menu() {// Выбор сервера и клиента
    int number;
    printf("Vi gotovi sigrat v krestiki-noliki po seti?\n");
    printf("Viberite rol'\n");
    printf("1 - Server \n");
    printf("2 - Client \n");
    scanf("%d", &number);
    D:
    if (number > 2 || number < 1) {
        printf("Vvedite korrektnie dannie");
        goto D;
    }
    if (number == 1)
        startServer();
    if (number == 2)
        startClient();
}
int __cdecl main(void) {
    menu();

    return 0;
}