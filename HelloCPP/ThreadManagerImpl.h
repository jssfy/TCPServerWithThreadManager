//
//  ThreadManagerImpl.h
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#ifndef __HelloCPP__ThreadManagerImpl__
#define __HelloCPP__ThreadManagerImpl__

#include "ThreadManager.h"
#include "ThreadManagerImpl.h"
#include <vector>

class ThreadManagerImpl : public ThreadManager
{
public:
    static ThreadManagerPtr DefaultThreadManager();
    
    virtual ~ThreadManagerImpl();
    
    
    ThreadManagerImpl(const ThreadManagerImpl&) = delete;
    ThreadManagerImpl& operator=(const ThreadManagerImpl&) = delete;
protected:
    virtual ThreadPtr CreateThread(TaskPtr iTask);
    
private:
    static ThreadManagerPtr msThreadManagerPtr;
    static std::mutex msThreadManagerMutex;
    ThreadManagerImpl();
    std::mutex mAllThreadsLock;
    std::vector<ThreadPtr> mAllThreads;
    void hAddThread(ThreadPtr iThread);
    void StopAll();


};

#endif /* defined(__HelloCPP__ThreadManagerImpl__) */
