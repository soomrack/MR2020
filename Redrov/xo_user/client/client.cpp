#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "xoEngine.cpp" //import cpp fuile from previous assignment. Not all the methods are used

using namespace std;

int client(){
     //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    //	Create a hint structure for the server we're connecting with
    int port = 54000;
    string ipAddress = "127.0.0.1"; //Enter ip address of the server

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    //	While loop:
    char buf[4096];
    string turn;


    do {
        //		Enter lines of text
        cout << "> ";
        cin >> turn;
        insert_move('O', buf[0] - 48, buf[1] - 48);

        //		Send to server
        int sendRes = send(sock, turn.c_str(), turn.size() + 1, 0);
        if (check_end()) {
            break;
        }
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);

        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
            insert_move('X', buf[0] - 48, buf[1] - 48);
            if (check_end()){
                break;
            }
        }
    } while(true);

    //	Close the socket
    close(sock);

    return 0;
}

int main(){

    init_table();

    client();  // Uncomment if started in client machine and change ip address in client function

    return 0;
}   