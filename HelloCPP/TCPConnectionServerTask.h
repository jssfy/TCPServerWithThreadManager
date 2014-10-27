//
//  TCPConnectionServerTask.h
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#ifndef __HelloCPP__TCPConnectionServerTask__
#define __HelloCPP__TCPConnectionServerTask__

#include "Task.h"

class TCPConnectionServerTask : public Task
{
public:
    TCPConnectionServerTask(int iAcceptFd);
    virtual ~TCPConnectionServerTask();
    
    virtual void operator()(void* ipArg = nullptr);
    virtual void Stop();
    
private:
    int mAcceptFd;
//    HttpRequestPtr mHttpRequestPtr;
//    HttpClientPtr mHttpClientPtr;
};
#endif /* defined(__HelloCPP__TCPConnectionServerTask__) */
