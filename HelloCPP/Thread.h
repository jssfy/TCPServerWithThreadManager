//
//  Thread.h
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#ifndef HelloCPP_Thread_h
#define HelloCPP_Thread_h

#include <thread>

class Thread;
typedef std::shared_ptr<Thread> ThreadPtr;

class Thread
{
public:
    typedef void (*StartRoutine)(void* ipArgs);
    typedef std::thread::id ID;
    
    enum class Status
    {
        kInit = 0x0,
        kRunning = 0x1,
        kPause = 0x2,	// not implemented
        kStop = 0x4
    };
    
    virtual ~Thread() {}
    
    /**
     * Get the current status of the thread
     * @return	kInit		the thread has not started yet,
     *			kRunning	the thread is already running,
     *			kPause		the thread currently is paused, will support in the future
     *			kStop		the thread has already stopped
     */
//    virtual Status GetStatus() = 0;
    
    /**
     * after invoke this thread, the thread starts running
     */
    virtual void Start() = 0;
    
    /**
     * after this thread returns, the thread finsihes running
     */
    virtual void Stop() = 0;
    
    /**
     * get the thread ID
     * @return the thread ID
     */
    virtual ID GetID() = 0;
    
    /**
     * TODO
     * currently do nothing
     * May implement it in the future
     * pause the thread
     */
    virtual void Suspend() = 0;
    
    /**
     * TODO
     * currently do nothing
     * May implement it in the future
     * detach this thread, so this thread will become unjoinable
     */
    virtual void Detach() = 0;
    
    /**
     * TODO
     * currently do nothing
     * May implement it in the future
     * join the thread, wait until it finishes
     */
    virtual void Join() = 0;
    
    /**
     * check whether this thread is joinable
     * @return true/false
     */
    virtual bool IsJoinable() = 0;
};

#endif
