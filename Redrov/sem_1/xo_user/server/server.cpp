#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "xoEngine.cpp" //import cpp fuile from previous assignment. Not all the methods are used

using namespace std;

int server(){

    // create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1){
        cerr << "Can't create a socket";
        return -1;
    }

    // bind to the IP and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1){
        cerr << "Cant' bind to IP/PORT";
        return -2;
    }

    // mark the socket for listening in
    if (listen(listening, SOMAXCONN) == -1){
        cerr << "Can't lesten";
        return -3;
    }

    // Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    
    if (clientSocket == -1){
        cerr << "Problem with client";
        return -4;
    }

    //close socket
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), 
                            host, NI_MAXHOST, svc, NI_MAXSERV, 0);
    
    if (result){
        cout << host << "connected on" << svc << endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << "connected on " << ntohs(client.sin_port) << endl;\
    }

    // while receiving display message, echo message
    char buf[4096];
    while(true){
        //clear the buf
        memset(buf, 0, 4096);
        // wait for message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);

        if (bytesRecv == -1){
            cerr << "There was a connection issue";
            break;
        }

        if (bytesRecv == 0){
            cout << "The client disconnected";
            break;
        } 

        if (check_end()) {
            break;
        }
        
        insert_move('X', buf[0] - 48, buf[1] - 48);

        if (check_end()) {
            break;
        }
        
        //display message
        cout << "Received: " << string(buf, 0, bytesRecv) << endl;

        //resend message
        string turn;
        cin >> turn;
        insert_move('O', buf[0] - 48, buf[1] - 48);
        send(clientSocket, turn.c_str(), turn.size() + 1, 0);
    }

    close(clientSocket);

    return 0;

}

int main(){

    init_table();

    server();

    return 0;
}   