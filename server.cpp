#include <iostream>
#include <string>
#include "CAsyncSocket.h"

int main(int argc, char *argv[])
{
    LOG_INFO("Starting client");

    CAsyncSocket asyncSocket;
    asyncSocket.Socket(SOCK_STREAM); // TCP
    
    asyncSocket.SetSockOpt();
    asyncSocket.Bind(4001);
    asyncSocket.Listen(1);
    CAsyncSocket clientSocket; 

    LOG_INFO("Accepting first client");
    asyncSocket.Accept(clientSocket);

    LOG_INFO("Starting exchange");

    std::cout << ">>" << "Bonjour Ronan!" << std::endl;
    clientSocket.Send("Bonjour Ronan!", sizeof("Bonjour Ronan!"));

    char reception[255];
    clientSocket.Receive(reception, sizeof(reception));
    std::cout << "\t\t\t\tClient: " << reception << std::endl;

    sleep(2);
    std::cout <<">>" << "Ca va ?" << std::endl;
    clientSocket.Send("Ca va ?", sizeof("Ca va ?"));

    clientSocket.Receive(reception, sizeof(reception));
    std::cout << "\t\t\t\tClient: " << reception << std::endl;

    std::cout <<">>" << "EXIT" << std::endl;
    clientSocket.Send("EXIT", sizeof("EXIT"));


    clientSocket.ShutDown();
    clientSocket.Close();
    asyncSocket.Close();
    
    return 0;
}