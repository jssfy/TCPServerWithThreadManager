//
//  TCPServer.cpp
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#include "TCPServer.h"
#include "TimeUtils.h"
#include "ThreadImpl.h"
#include "ThreadManager.h"
#include "TCPConnectionServerTask.h"

TcpServer::TcpServer(int listen_port) {
    
    if(( socket_fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0 ){
        throw "socket() failed";
    }
    
    memset(&myserver,0,sizeof(myserver));
    myserver.sin_family = AF_INET;
    myserver.sin_addr.s_addr = htonl(INADDR_ANY);
    myserver.sin_port = htons(listen_port);
    
    int opt = 1;
    setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    
    if( bind(socket_fd,(sockaddr*) &myserver,sizeof(myserver)) < 0 ) {
        perror("BIND");
        throw "bind() failed";
    }
    
    if( listen(socket_fd,10) < 0 ) {
        throw "listen() failed";
    }
}

TcpServer::~TcpServer()
{
    close(socket_fd);
}

void thread_func()
{
        
        std::cout << "thread_func tid: " << std::this_thread::get_id() << std::endl;
        
//        close (iAcceptFd);
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
        
        std::cout << "child exit in thread_func at " << TimeUtils::SystemNowInSeconds() << std::endl;
}

static const int MAXLINE = 1024;
template<typename T>
T max(const T a, const T b)
{
    return a>b?a:b;
}

void TcpServer::hInteractWithClient(int iAcceptFd)
{
    int			maxfdp1;
    fd_set		rset;
    char		sendline[MAXLINE] = "test";
    char        recvline[MAXLINE] = "hello";
    
    FILE *fp = stdin;
    
    FD_ZERO(&rset);
    for ( ; ; ) {
        
        
        memset(sendline, 0, MAXLINE*sizeof(char));
        memset(recvline, 0, MAXLINE*sizeof(char));
        
        FD_SET(fileno(fp), &rset);
        FD_SET(iAcceptFd, &rset);
        maxfdp1 = max(fileno(fp), iAcceptFd) + 1;
        select(maxfdp1, &rset, NULL, NULL, NULL);
        
        if (FD_ISSET(iAcceptFd, &rset)) {	/* socket is readable */
            if(read(iAcceptFd,recvline,MAXLINE) < 0)
            {
                perror("TcpServer::hInteractWithClient read fail");
            }
            else if (strcmp(recvline, "quit\r\n") == 0)
            {
                std::cout << "TcpServer::hInteractWithClient quitted on client input to quit!\n";
                return;
            }
            else
            {
                std::cout << "recved string size: " << strlen(recvline) << std::endl;
                fputs(recvline, stdout);
            }
        }
        
        if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
            if (fgets(sendline, MAXLINE, fp) == NULL)
                return;		/* all done */
            else if(strcmp(sendline, "quit\n") == 0)
            {
                std::cout << "TcpServer::hInteractWithClient quitted on server input to quit!\n";
                return;
            }
            else
            {
                std::cout << "input string size: " << strlen(sendline) << " " << sendline << (int)sendline[strlen(sendline)-1] << " " << (int)'\r' << std::endl;

            }
            if(write(iAcceptFd, sendline, strlen(sendline)) < 0)
            {
                perror("TcpServer::hInteractWithClient write fail");
            }
            else
            {
                
            }
//            Writen(sockfd, sendline, strlen(sendline));
        }
    }
}

int TcpServer::recv_msg() {
    
    while(true)
    {
        std::cout << "loop start at " << TimeUtils::SystemNowInSeconds() << " and thread id is " << std::this_thread::get_id() << std::endl;

        
        socklen_t sin_size = sizeof(struct sockaddr_in);
        
        std::cout << "to accept at " << TimeUtils::SystemNowInSeconds() << std::endl;
        if(( accept_fd = accept(socket_fd,(struct sockaddr*) &remote_addr,&sin_size)) == -1 )
        {
            std::cout << "pid: " << getpid() << " accept fail at " << TimeUtils::SystemNowInMilliseconds() << std::endl;
            perror("accept");

            continue;
            
        }
        printf("Received a connection from %s on port: %d with accpeted fd %d\n",(char*) inet_ntoa(remote_addr.sin_addr), remote_addr.sin_port, accept_fd);
        
        // create a thread and continue with other potential connections
//        TaskPtr task = TaskPtr(new TCPConnectionServerTask(accept_fd));
//        ThreadPtr thread = ThreadManager::DefaultThreadManager()->CreateThread(std::move(task));

        // stay with this connection until client asks to quit
        hInteractWithClient(accept_fd);
        close(accept_fd);
        
    }
    std::cout << "recv_msg end" << std::endl;

    
    return 0;
}