//
//  Task.h
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#ifndef HelloCPP_Task_h
#define HelloCPP_Task_h

#include <memory>
#include <atomic>

class Task;
typedef std::shared_ptr<Task> TaskPtr;

class Task
{
public:
    /**
     * the destructor
     */
    virtual ~Task() {}
    
    /**
     * child class must override this operator
     * @param ipArg the caller can pass anything in it
     * @return
     */
    virtual void operator()(void* ipArg = nullptr) = 0;
    
    /**
     * the default implementation
     * child class can override this method
     * @return
     */
    virtual void Stop() { mbStop.store(true, std::memory_order_release); }
    
public:
    std::atomic<bool> mbStop {false};
    
};

#endif
