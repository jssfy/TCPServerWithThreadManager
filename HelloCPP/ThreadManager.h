//
//  ThreadManager.h
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#ifndef HelloCPP_ThreadManager_h
#define HelloCPP_ThreadManager_h

#include <memory>

#include "Thread.h"
#include "Task.h"

class ThreadManager;
typedef std::shared_ptr<ThreadManager> ThreadManagerPtr;

class ThreadManager
{
public:
    
    
    static ThreadManagerPtr DefaultThreadManager();
    
    virtual ~ThreadManager() {}

    /**
     * create thread using functor object
     * @param iTask	the functor
     * @retrun the thread handler
     */
    virtual ThreadPtr CreateThread(TaskPtr iTask) = 0;
};

#endif
