//
//  TCPConnectionServerTask.cpp
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#include "TCPConnectionServerTask.h"

#include <thread>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "TimeUtils.h"

const int MAXSIZE = 1024;

TCPConnectionServerTask::TCPConnectionServerTask(int iAcceptFd):mAcceptFd(iAcceptFd)
{
    
}

TCPConnectionServerTask::~TCPConnectionServerTask()
{
    
}

void TCPConnectionServerTask::operator()(void* ipArg)
{
    
    std::cout << "TCPConnectionServerTask tid: " << std::this_thread::get_id() << std::endl;
    
    close (mAcceptFd);
//    char buffer[MAXSIZE];
//    memset(buffer,0,MAXSIZE);
//    if( ( read(mAcceptFd,buffer,MAXSIZE)) < 0 ) {
//        close(mAcceptFd);
//        
//        throw("Read() error!");
//    } else {
//        close(mAcceptFd);
//        
//        printf("Received message: %s\n",buffer);
//        //                break;
//    }
    
    sleep(10);
    
    std::cout << "child exit at " << TimeUtils::SystemNowInSeconds() << std::endl;
}

void TCPConnectionServerTask::Stop()
{
//    if (mHttpClientPtr.get())
//    {
//        mHttpClientPtr->CancelRequest();
//    }
}