//
//  TCPServer.h
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#ifndef __HelloCPP__TCPServer__
#define __HelloCPP__TCPServer__

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXSIZE 1024

class TcpServer
{
private:
    int socket_fd, accept_fd;
    sockaddr_in myserver;
    sockaddr_in remote_addr;
    
    void hInteractWithClient(int iAcceptFd);
    
public:
    TcpServer(int listen_port);
    ~TcpServer();
    int recv_msg();
};

#endif /* defined(__HelloCPP__TCPServer__) */
