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

    struct sockaddr_in client;
    socklen_t lenClient = sizeof(client);
    struct sockaddr* pClient = (struct sockaddr*)&client;
    asyncSocket.CreateSockAddrIn("127.0.0.1", 4001);

    LOG_INFO("Accepting first client");

    char reception[255];
    LOG_INFO("Starting exchange");

    asyncSocket.ReceiveFrom(reception, sizeof(reception), (struct sockaddr*)&client, &lenClient);
    std::cout << "\t\t\t\tClient: " << reception << std::endl;


    std::cout << ">>" << "Bonjour Ronan!" << std::endl;
    asyncSocket.SendTo("Bonjour Ronan!", sizeof("Bonjour Ronan!"), pClient, lenClient);

   
    asyncSocket.ReceiveFrom(reception, sizeof(reception), pClient, &lenClient);
    std::cout << "\t\t\t\tClient: " << reception << std::endl;

    sleep(2);
    std::cout <<">>" << "Ca va ?" << std::endl;
    asyncSocket.SendTo("Ca va ?", sizeof("Ca va ?"), pClient, lenClient);

    asyncSocket.ReceiveFrom(reception, sizeof(reception), pClient, &lenClient);
    std::cout << "\t\t\t\tClient: " << reception << std::endl;

    std::cout <<">>" << "EXIT" << std::endl;
    asyncSocket.SendTo("EXIT", sizeof("EXIT"), pClient, lenClient);

    asyncSocket.Close();
    
    return 0;
}