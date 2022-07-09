#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "types.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>

class CAsyncSocket
{
private:
    /**
     * @brief File descriptor on socket 
     * 
     */
    SOCKET fdsocket;
    std::vector<sockaddr> socks;
public:
    CAsyncSocket(/* args */);
    ~CAsyncSocket();

    /**
     * @brief Accept a connection on a socket
     * 
     * @param rConnectedSocket 
     * @param lpSockAddr 
     * @param lpSockAddrLen 
     * @return true 
     * @return false 
     */
    virtual bool Accept(CAsyncSocket& rConnectedSocket, string * lpSockAddr = nullptr, int * lpSockAddrLen = nullptr);
    
    /**
     * @brief Attaches handle to CAsyncObject
     * 
     * @param fdsocket file descriptor of the socket
     * @return true 
     * @return false 
     */
    bool Attach(SOCKET fdsocket);

    /**
     * @brief Associates a local address with the socket
     * 
     * @param nSocketPort 
     * @param strAddr 
     * @return true 
     * @return false 
     */
    bool Bind(uint nSocketPort, string strAddr);

    /**
     * @brief Close the socket 
     */
    virtual void Close();

    /**
     * @brief Establishes a connection to a peer socket. 
     * 
     * @return connection success
     */
    bool Connect(string strHostAddress, uint nHostPort);

    /**
     * @brief Create socket
     * 
     * @param nSocketPort 
     * @param SocketType 
     * @param socketAddress 
     * @return true 
     * @return false 
     */
    bool Create(uint nSocketPort, int SocketType = 0, string * socketAddress = nullptr);

    /**
     * @brief Detach socket
     * 
     * @return SOCKET 
     */
    SOCKET detach(); 

    /**
     * @brief listens for incoming connection requests
     * 
     * @param nConnectionBacklog 
     * @return true 
     * @return false 
     */
    bool Listen(uint nConnectionBacklog = 5);

    /**
     * @brief Receives data from socket
     * 
     * @param buffer 
     * @param nBufferLen 
     * @return int 
     */
    virtual int Receive(char* buffer, int nBufferLen);

    /**
     * @brief Construct a new Send object
     * 
     * @param buffer data to be transmitted
     * @param nBufferLen length of data in buffer
     * @return int 
     */
    virtual int Send(const char* buffer, int nBufferLen);
    
    /**
     * @brief Set the Sock Option
     * 
     * @param optname 
     * @param optVal 
     * @param optlen 
     * @param level 
     * @return true 
     * @return false 
     */
    virtual bool SetSockOpt( int optname, int *optVal, int optlen, int level = SOL_SOCKET);

    /**
     * @brief Disable sends receives or both on the socket
     * 
     * @param nHow 0=receivers, 1=sends , 2=both
     * @return true 
     * @return false 
     */
    bool ShutDown(int nHow = 1);

    // ---------- EVENT ----------
    /**
     * @brief Called by the framework to notify a listening socket 
     *        that it can accept pending connection
     * 
     * @param nErrorCode 
     */
    virtual void OnAccept(int nErrorCode);

    /**
     * @brief Called by the framework to notify a listening socket 
     *        that it can closed by its process
     * @param nErrorCode 
     */
    virtual void OnClose(int nErrorCode);


    /**
     * @brief Called by the framework to notify a listening socket 
     *        that its connection attemp is completed
     * @param nErrorCode 
     */
    virtual void OnConnect(int nErrorCode);

    /**
     * @brief Called by the framework to notify a listening socket 
     *        the receiving socket that the sending socket has out-of-band data to send.
     * @param nErrorCode 
     */
    virtual void OnOutOfBandData(int nErrorCode);
};

