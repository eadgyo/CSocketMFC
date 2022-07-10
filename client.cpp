#include <iostream>
#include <string>
#include "CAsyncSocket.h"

int main(int argc, char *argv[])
{
    LOG_INFO("Starting client!");
    CAsyncSocket asyncSocket;
    asyncSocket.Socket(SOCK_STREAM); // TCP
    
    LOG_INFO("Connecting to 127.0.0.1:4001");
    asyncSocket.Connect("127.0.0.1", 4001);

    LOG_INFO("Connection Success !!");
    
    char buffer[255];
    asyncSocket.Receive(buffer, sizeof(buffer));
    std::cout << "\t\t\t\tServer: " << buffer << std::endl;

    char msg[] = "Bonjour Nathan!";
    std::cout <<">>" << msg  << std::endl;
    asyncSocket.Send(msg, sizeof(msg));
    sleep(2);
    asyncSocket.Receive(buffer, sizeof(buffer));
    std::cout << "\t\t\t\tServer: " << buffer << std::endl;
    sleep(2);
    char msg2[] = "Tres bien!";
    std::cout << ">>" << msg2 << std::endl;
    asyncSocket.Send(msg2, sizeof(msg2));
    asyncSocket.Receive(buffer, sizeof(buffer));
    std::cout << "\t\t\t\tServer: " << buffer << std::endl;
    sleep(2);
    //asyncSocket.ShutDown();
    //asyncSocket.Close();

    return 0;
}