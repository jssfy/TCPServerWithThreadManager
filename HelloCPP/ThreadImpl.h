//
//  ThreadImpl.h
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#ifndef __HelloCPP__ThreadImpl__
#define __HelloCPP__ThreadImpl__

#include "Thread.h"
#include "Task.h"

class ThreadImpl : public Thread
{
public:
    virtual ~ThreadImpl();
    
    ThreadImpl(const ThreadImpl&) = delete;
    const ThreadImpl operator=(const ThreadImpl&) = delete;
    
protected:
//    virtual Thread::Status GetStatus();
    virtual void Start();
    virtual void Stop();
    virtual ID GetID();
    virtual void Suspend();	// not implemented
    virtual void Detach();	// not implemented
    virtual void Join();	// not implemented
    virtual bool IsJoinable();
    
//private:
public:
    // we can only use ThreadFactoryImpl class to create a thread
//    friend class ThreadFactoryImpl;
    explicit ThreadImpl(StartRoutine iStartRoutine, void* ipArgs = nullptr);
    explicit ThreadImpl(TaskPtr&& iTask);
    explicit ThreadImpl(std::function<void()>&& irFunc);
private:
    void hStart();
    
    StartRoutine mStartRoutine;
    void* mpArgs;
    std::function<void()> mFunc;
    TaskPtr mTask;
    
    // We use std::thread introduced from c++11 as the thread entity
    std::thread mThread;
    
    // use spin lock to protect status
//    SpinLock mStatusLock;
    Thread::Status mStatus;
};
#endif /* defined(__HelloCPP__ThreadImpl__) */
