#pragma once
#include "types.h"
#include <string>
#include <iostream>
#include "CAsyncSocket.h"


using namespace std;

class CSocket : public CAsyncSocket
{

public:
    CSocket(/* args */);
    ~CSocket();

    /**
     * @brief Cancels a blocking call that is currently in progress.
     * 
     */
    void CancelBlockingCall();

    /**
     * @brief Determines whether a blocking call is in progress.
     * 
     * @return true 
     * @return false 
     */
    bool IsBlocking();

    /**
     * @brief 	Called to process pending messages while 
     *          waiting for a blocking call to complete.
     * 
     * @return true 
     * @return false 
     */
    virtual bool OnMessagePending();
};

