#include <iostream>
#include <string>
#include "CAsyncSocket.h"

int main(int argc, char *argv[])
{
    LOG_INFO("Starting client!");
    CAsyncSocket asyncSocket;
    asyncSocket.Socket(SOCK_DGRAM); // TCP
    
    //LOG_INFO("Connecting to 127.0.0.1:4001");
    struct sockaddr_in client;
    socklen_t lenClient = sizeof(client);
    struct sockaddr* pClient = (struct sockaddr*)&client;

    client = asyncSocket.CreateSockAddrIn("127.0.0.1", 4001);

    //LOG_INFO("Connection Success !!");
    char msg0[] = "Bonjour Nathan!";
    std::cout <<">>" << msg0  << std::endl;
    asyncSocket.SendTo(msg0, sizeof(msg0), pClient, lenClient);
    
    char buffer[255];
    asyncSocket.ReceiveFrom(buffer, sizeof(buffer), pClient, &lenClient);
    std::cout << "\t\t\t\tServer: " << buffer << std::endl;

    char msg[] = "Mieux en UDP!";
    std::cout <<">>" << msg  << std::endl;
    asyncSocket.SendTo(msg, sizeof(msg), pClient, lenClient);
    sleep(2);
    asyncSocket.ReceiveFrom(buffer, sizeof(buffer), pClient, &lenClient);
    std::cout << "\t\t\t\tServer: " << buffer << std::endl;
    sleep(2);
    char msg2[] = "Tres bien!";
    std::cout << ">>" << msg2 << std::endl;
    asyncSocket.SendTo(msg2, sizeof(msg2), pClient, lenClient);
    asyncSocket.ReceiveFrom(buffer, sizeof(buffer), pClient, &lenClient);
    std::cout << "\t\t\t\tServer: " << buffer << std::endl;
    sleep(2);
    //asyncSocket.ShutDown();
    //asyncSocket.Close();

    return 0;
}