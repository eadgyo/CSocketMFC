#include <iostream>
#include <string>
#include "CAsyncSocket.h"

int main(int argc, char *argv[])
{
    LOG_INFO("Starting client");

    CAsyncSocket asyncSocket;
    asyncSocket.Socket(SOCK_DGRAM); // TCP
    
    asyncSocket.SetSockOpt();
    asyncSocket.Bind(4001);

    CAsyncSocket clientSocket = asyncSocket;
    LOG_INFO("Accepting first client");

    char reception[255];
    LOG_INFO("Starting exchange");

    //asyncSocket.Accept(clientSocket);
    clientSocket.ReceiveFrom(reception, sizeof(reception));
    std::cout << "\t\t\t\tClient: " << reception << std::endl;


    std::cout << ">>" << "Bonjour Ronan!" << std::endl;
    clientSocket.SendTo("Bonjour Ronan!", sizeof("Bonjour Ronan!"));

   
    clientSocket.ReceiveFrom(reception, sizeof(reception));
    std::cout << "\t\t\t\tClient: " << reception << std::endl;

    sleep(2);
    std::cout <<">>" << "Ca va ?" << std::endl;
    clientSocket.SendTo("Ca va ?", sizeof("Ca va ?"));

    clientSocket.ReceiveFrom(reception, sizeof(reception));
    std::cout << "\t\t\t\tClient: " << reception << std::endl;

    std::cout <<">>" << "EXIT" << std::endl;
    clientSocket.SendTo("EXIT", sizeof("EXIT"));


    clientSocket.ShutDown();
    clientSocket.Close();
    asyncSocket.Close();
    
    return 0;
}