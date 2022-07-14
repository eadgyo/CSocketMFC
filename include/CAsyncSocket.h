#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "types.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include "debug.h"  
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "structures.h"

#define CHECK_READ if (this->nShutdown == 0 || this->nShutdown == 2) return 0; 
#define CHECK_SEND if (this->nShutdown == 1 || this->nShutdown == 2) return 0; 

class CAsyncSocket
{
private:
    /**
     * @brief File descriptor on socket 
     * 
     */
    SOCKET fdsocket = -1;
    struct sockaddr_in serv_addr;
    long lEvent = 0;
    int nShutdown = -1;
    
public:
    CAsyncSocket(/* args */);
    CAsyncSocket(const CAsyncSocket& socket);
    ~CAsyncSocket();

    int getSocket()
    {
        return fdsocket;
    };

    /**
     * @brief Set the Accept Blocking object
     * 
     * @param mode
     */
    void AddMode(int mode);
    

    /**
     * @brief Set the Accept Blocking object
     * 
     * @param mode
     */
    void RemoveMode(int mode);

    /**
     * @brief Set mode
     * 
     * @param mode 
     * @return true 
     * @return false 
     */
    int IOCtl(int command, int mode);
    
    

    /**
     * @brief Accept a connection on a socket
     * 
     * @param rConnectedSocket 
     * @param lpSockAddr 
     * @param lpSockAddrLen 
     * @return true 
     * @return false 
     */
    virtual bool Accept(CAsyncSocket& rConnectedSocket, sockaddr * lpSockAddr = nullptr, socklen_t * lpSockAddrLen = nullptr);
    
    /**
     * @brief Attaches handle to CAsyncObject
     * 
     * @param fdsocket file descriptor of the socket
     * @return true 
     * @return false 
     */
    bool Attach(SOCKET fdsocket, const sockaddr* lpSockAddr=nullptr, socklen_t *lpSockAddrLen=nullptr);

    /**
     * @brief Associates a local address with the socket
     * 
     * @param nSocketPort 
     * @return true 
     * @return false 
     */
    bool Bind(uint nSocketPort, string *straddr = nullptr);

    /**
     * @brief Associates a local address with the socket
     * 
     * @param nSocketPort 
     * @return true 
     * @return false 
     */
    bool Bind(const sockaddr* lpSockAddr, socklen_t *lpSockAddrLen);


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
     * @brief Establishes a connection to a peer socket. 
     * 
     * @return connection success
     */
    void Init(string strHostAddress, uint nHostPort);

    /**
     * @brief Create socket addr in
     * 
     * @param strHostAddress 
     * @param nHostPort 
     * @return sockaddr_in 
     */
    sockaddr_in CreateSockAddrIn(string strHostAddress, uint nHostPort);
    
    /**
     * @brief Create socket
     * 
     * @param SocketType 
     * @return true 
     * @return false 
     */
    bool Socket(int SocketType=SOCK_STREAM, long lEvent=0, int nProtocolType=0, int nAddressFormat=AF_INET);

    /**
     * @brief Create socket and attach to address
     * 
     * @param nSocketPort 
     * @param SocketType 
     * @param lEvent 
     * @param straddr 
     * @return true 
     * @return false 
     */
    bool Create(uint nSocketPort=0, int SocketType = SOCK_STREAM, long lEvent = 0, string *straddr = nullptr);

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
     * @brief Receives data from socket
     * 
     * @param buffer 
     * @param nBufferLen 
     * @param flags
     * @return int 
     */
    virtual int Receive(char* buffer, int nBufferLen, int flags);

    /**
     * @brief Receives data from socket
     * 
     * @param buffer 
     * @param nBufferLen 
     * @param flags
     * @return int 
     */
    virtual int ReceiveFrom(char* buffer, int nBufferLen, string& socketAddress, uint& socketPort, int flags = 0);
    
    /**
     * @brief Receives data from socket
     * 
     * @param buffer 
     * @param nBufferLen 
     * @param flags
     * @return int 
     */
    virtual int ReceiveFrom(char* buffer, int nBufferLen, sockaddr* lpSockAddr, socklen_t *lpSockAddrLen, int flags = 0);
    

    /**
     * @brief Construct a new Send object
     * 
     * @param buffer data to be transmitted
     * @param nBufferLen length of data in buffer
     * @return int 
     */
    virtual int Send(const char* buffer, int nBufferLen);
    
    /**
     * @brief Construct a new Send object
     * 
     * @param buffer data to be transmitted
     * @param nBufferLen length of data in buffer
     * @param flags used flags to send
     * @return int 
     */
    virtual int Send(const char* buffer, int nBufferLen, int flags);
    

    /**
     * @brief SendTo data from socket
     * 
     * @param buffer 
     * @param nBufferLen 
     * @param flags
     * @return int 
     */
    virtual int SendTo(char* buffer, int nBufferLen, string socketAddress, uint socketPort, int flags = 0);
    
    /**
     * @brief SendTo data from socket
     * 
     * @param buffer 
     * @param nBufferLen 
     * @param flags
     * @return int 
     */
    virtual int SendTo(char* buffer, int nBufferLen, sockaddr* lpSockAddr, socklen_t lpSockAddrLen, int flags = 0);
    


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
    virtual bool SetSockOpt( int optname =  SO_REUSEADDR | SO_REUSEPORT, int optVal = 1, int level = SOL_SOCKET);

    /**
     * @brief Disable sends receives or both on the socket
     * 
     * @param nHow 0=receivers, 1=sends , 2=both
     * @return true 
     * @return false 
     */
    bool ShutDown(int nHow = 1);

    /**
     * @brief Clone object
     * 
     * @return CAsyncSocket 
     */
    CAsyncSocket& operator=(const CAsyncSocket& socket);

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

