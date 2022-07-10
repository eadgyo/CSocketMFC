#include "CAsyncSocket.h"

CAsyncSocket::CAsyncSocket()
{
}

CAsyncSocket::CAsyncSocket(const CAsyncSocket& socket) : fdsocket(socket.fdsocket), lEvent(socket.lEvent), nShutdown(socket.nShutdown) 
{
    memcpy(&serv_addr, &socket.serv_addr, sizeof(serv_addr));
}


CAsyncSocket::~CAsyncSocket()
{

}

bool CAsyncSocket::Attach(SOCKET fdsocket, const sockaddr* lpSockAddr, socklen_t *lpSockAddrLen)
{
    LOG_DEBUG("Attaching " << fdsocket);
    
    if (fdsocket >= 0)
    {
        LOG_DEBUG("Attaching socket from " << this->fdsocket << " to " << fdsocket);
        this->fdsocket = fdsocket;
    }
    
    if (lpSockAddr != nullptr)
    {
        LOG_DEBUG("Attaching sockaddr!")
        THROW_IF(sizeof(serv_addr) < (*lpSockAddrLen));
        memcpy(&serv_addr, lpSockAddr, *lpSockAddrLen);
    }

    return true;
}

bool CAsyncSocket::Create(uint nSocketPort, int SocketType, long lEvent, string *straddr)
{
    LOG_DEBUG("Creating socket binding and attaching !");

    THROW_IF(!Socket(SocketType, lEvent));
    THROW_IF(!Bind(nSocketPort, straddr));
    return true;
}


bool CAsyncSocket::Socket(int SocketType, long lEvent, int nProtocolType, int nAddressFormat)
{
    LOG_DEBUG("Creating socket");
    this->lEvent = lEvent;
    THROW_IF((fdsocket = socket(nAddressFormat, SocketType, nProtocolType)) == -1);
    return true;
}

bool CAsyncSocket::SetSockOpt(int optname, int optVal, int level)
{
    LOG_DEBUG("Set socket option");
    THROW_IF(setsockopt(fdsocket, level, optname, &optVal, sizeof(optVal)) != 0);
    return true;
}

bool CAsyncSocket::Bind(uint nSocketPort, string *straddr)
{
    LOG_DEBUG("Attaching to " << nSocketPort);

    serv_addr.sin_family = AF_INET;
    if (straddr == nullptr)
    {
        serv_addr.sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        serv_addr.sin_addr.s_addr = inet_addr(straddr->c_str());
    }
    serv_addr.sin_port = htons(nSocketPort);

    THROW_IF(bind(fdsocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0);
    return true;
}

bool CAsyncSocket::Bind(const sockaddr* lpSockAddr, socklen_t *lpSockAddrLen)
{
    THROW_IF(bind(fdsocket, (struct sockaddr *) &lpSockAddr, *lpSockAddrLen) < 0);
    Attach(-1, lpSockAddr, lpSockAddrLen);
    return true;
}


bool CAsyncSocket::Listen(uint nConnectionBacklog)
{
    THROW_IF(listen(fdsocket, nConnectionBacklog) != 0);
    return true;
}

int CAsyncSocket::Receive(char* buffer, int nBufferLen)
{
    CHECK_READ;

    int len = 0;
    len = read(fdsocket, buffer, nBufferLen);
    LOG_DEBUG("Receive " << buffer << " with length " << len);
    return len;
}

int CAsyncSocket::Receive(char* buffer, int nBufferLen, int flags)
{
    CHECK_READ;

    int len = 0;
    len = recv(fdsocket, buffer, nBufferLen, flags);
    LOG_DEBUG("Receive " << buffer << " with length " << len);
    return len;
}

int CAsyncSocket::ReceiveFrom(char* buffer, int nBufferLen, string& socketAddress, uint& socketPort, int flags)
{
    CHECK_READ;

    int len = 0;
    struct sockaddr_in client;
    socklen_t size = sizeof(client);

    len = recvfrom(fdsocket, buffer, nBufferLen, flags, (struct sockaddr*)&client, &size);
    LOG_DEBUG("Receive " << buffer << " with length " << len << " from " << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port));
    
    socketAddress = inet_ntoa(client.sin_addr);
    socketPort = ntohs(client.sin_port);

    return len;
}


int CAsyncSocket::ReceiveFrom(char* buffer, int nBufferLen, sockaddr* lpSockAddr, socklen_t *lpSockAddrLen, int flags)
{
    CHECK_READ;
    
    int len = 0;
    len = recvfrom(fdsocket, buffer, nBufferLen, flags, (struct sockaddr*)lpSockAddr, lpSockAddrLen);
    LOG_DEBUG("Receive " << buffer << " with length " << len << " from " << inet_ntoa(((struct sockaddr_in*)lpSockAddr)->sin_addr) << ":" << ntohs(((struct sockaddr_in*)lpSockAddr)->sin_port));
    return len;
}

CAsyncSocket& CAsyncSocket::operator=(const CAsyncSocket& socket)
{
    return * this;
}

int CAsyncSocket::Send(const char* buffer, int nBufferLen)
{
    CHECK_SEND;
    LOG_DEBUG("Send " << buffer << " with length " << nBufferLen);
    int len = 0;
    len = write(fdsocket, buffer, nBufferLen);
    LOG_DEBUG("Send " << len << " written");
    return len;
}

int CAsyncSocket::Send(const char* buffer, int nBufferLen, int flags)
{
    CHECK_SEND;
    LOG_DEBUG("Send " << buffer << " with length " << nBufferLen);

    int len = 0;
    len = send(fdsocket, buffer, nBufferLen, flags);
    LOG_DEBUG("Send " << len << " written");
    return len;
}


    

int CAsyncSocket::SendTo(char* buffer, int nBufferLen, string socketAddress, uint socketPort, int flags)
{
    CHECK_SEND;
    LOG_DEBUG("SendTo " << buffer << " with length " << nBufferLen << " to address " << socketAddress << ":" << socketPort);

    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(socketAddress.c_str());
    client.sin_port = htons(socketPort); 

    int len = 0;
    len = sendto(fdsocket, buffer, nBufferLen, flags, (struct sockaddr*)&client, sizeof(client));
    LOG_DEBUG("Send " << len << " written");
    return len;
}

int CAsyncSocket::SendTo(char* buffer, int nBufferLen, sockaddr* lpSockAddr, socklen_t lpSockAddrLen, int flags)
{
    CHECK_SEND;
    LOG_DEBUG("SendTo " << buffer << " with length " << nBufferLen);

    int len = 0;
    len = sendto(fdsocket, buffer, nBufferLen, flags, (struct sockaddr*)lpSockAddr, lpSockAddrLen);
    LOG_DEBUG("Send " << len << " written");
    return len;
}

void CAsyncSocket::AddMode(int mode)
{
    int flags = fcntl(fdsocket, F_GETFL, 0);
    flags |= mode;
    fcntl(fdsocket, F_SETFL, flags);
}

void CAsyncSocket::RemoveMode(int mode)
{
    int flags = fcntl(fdsocket, F_GETFL, 0);
    flags &= ~mode;
    fcntl(fdsocket, F_SETFL, flags);
}

int CAsyncSocket::IOCtl(int command, int mode)
{
    return fcntl(fdsocket, command, mode);
}



bool CAsyncSocket::Accept(CAsyncSocket& rConnectedSocket, sockaddr* lpSockAddr, socklen_t * lpSockAddrLen)
{
    struct sockaddr_in clientSock;
    socklen_t clientSockLen = sizeof(clientSock);

    sockaddr* l_lpSockAddr = lpSockAddr;
    socklen_t* l_lpSockAddrLen = lpSockAddrLen;
    if (lpSockAddr == nullptr || l_lpSockAddrLen == nullptr)
    {
        LOG_DEBUG("Creating clientSockLen");
        l_lpSockAddr = (struct sockaddr*)&clientSock;
        l_lpSockAddrLen = &clientSockLen;
    }
    else
    {
        LOG_DEBUG("Using lpSockAddr passed by argument");
    }

    int newfdsocket = accept(fdsocket, (struct sockaddr *) l_lpSockAddr, l_lpSockAddrLen);

    rConnectedSocket.Attach(newfdsocket, lpSockAddr);
    return true;
}

void CAsyncSocket::Init(string strHostAddress, uint nHostPort)
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(strHostAddress.c_str());
    serv_addr.sin_port = htons(nHostPort);
}

sockaddr_in CAsyncSocket::CreateSockAddrIn(string strHostAddress, uint nHostPort)
{
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(strHostAddress.c_str());
    client.sin_port = htons(nHostPort);
    return client;
}

bool CAsyncSocket::Connect(string strHostAddress, uint nHostPort)
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(strHostAddress.c_str());
    serv_addr.sin_port = htons(nHostPort);

    THROW_IF(connect(fdsocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0);
    return true;
}

void CAsyncSocket::Close()
{
    close(fdsocket);
}

bool CAsyncSocket::ShutDown(int nHow)
{
    nShutdown = nHow;
    return true;
}


void CAsyncSocket::OnAccept(int nErrorCode)
{
    LOG_DEBUG("OnAccept!");
}


void CAsyncSocket::OnClose(int nErrorCode)
{
    LOG_DEBUG("OnClose!");
}



void CAsyncSocket::OnConnect(int nErrorCode)
{
    LOG_DEBUG("OnConnect!");
}


void CAsyncSocket::OnOutOfBandData(int nErrorCode)
{
    LOG_DEBUG("OnConnect!");
}
