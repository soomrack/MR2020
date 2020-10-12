#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>


void s2buf(char (&buf)[4096], std::string sbuf){
    for (int i = 0; i < sbuf.length(); i++){
        buf[i] = sbuf[i];
    }
}


int main(int argc, char const *argv[])
{   
    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1){
        std::cerr << "Can't create a socket";
        return -1;
    }    
    
    // Binf the socket to a IP / port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    
    if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1){
        std::cerr << "Can't bind to IP/port";
        return -2;
    }

    // Mark the socket for listening in
    if (listen(listening, SOMAXCONN) == -1){
        std::cerr << "Can't listen!";
        return -3;
    } 

    // Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    if (clientSocket == -1){
        std::cerr << "Problem with client connecting!";
        return -4;
    }
    // Close the listening socket
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if (result){
        std::cout << host << " connected on " << svc << std::endl;

    } 
    else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << ntohs(client.sin_port) << std::endl;
    } 

    // While receving - desplay message, echo message
    char buf[4096];
    while (true){
        //Clear the buffer
        memset(buf, 0, 4096);
        // Wait for message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if (bytesRecv == -1){
            std::cerr << "These was a connetion issue" << std::endl;
            break;

        }

        if (bytesRecv == 0){
            std::cout << "The client disconnected" << std::endl;
            break;
        }
        
        // Display message
        std::cout << "Receinved: " << std::string(buf, 0, bytesRecv) << std::endl;
        

        memset(buf, 0, 4096);

        std::string message = "Hello World!";
        
        s2buf(buf, message);
        // Resend message
        send(clientSocket, buf, message.length() + 1, 0);

        
       
    }

    // Close socket
    close(clientSocket);
    

    return 0;
}
