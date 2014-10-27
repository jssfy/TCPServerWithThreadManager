//
//  ThreadImpl.cpp
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#include "ThreadImpl.h"


ThreadImpl::ThreadImpl(Thread::StartRoutine iStartRoutine, void* ipArgs)
: mStartRoutine(iStartRoutine),
mpArgs(ipArgs),
mTask(nullptr),
mFunc(nullptr),
mStatus(Thread::Status::kInit)
{
    
}

ThreadImpl::ThreadImpl(TaskPtr&& iTask)
: mStartRoutine(nullptr),
mpArgs(nullptr),
mTask(std::forward<TaskPtr>(iTask)),
mFunc(nullptr),
mStatus(Thread::Status::kInit)
{
    
}

ThreadImpl::ThreadImpl(std::function<void()>&& irFunc)
: mStartRoutine(nullptr),
mpArgs(nullptr),
mTask(nullptr),
mFunc(std::forward<std::function<void()>>(irFunc)),
mStatus(Thread::Status::kInit)
{
    
}

ThreadImpl::~ThreadImpl()
{
    Stop();
    mStartRoutine = nullptr;
    mpArgs = nullptr;
    mTask = nullptr;
    mFunc = nullptr;
}


void ThreadImpl::Start()
{
//    {
//        SpinLock::ScopeGuard lGuard(mStatusLock);
//        if (mStatus != Thread::Status::kInit)
//            return;
//        mStatus = Thread::Status::kRunning;
//    }
    mThread = std::thread(std::mem_fn(&ThreadImpl::hStart), this);
}

void ThreadImpl::hStart()
{
    if (mStartRoutine)
    {
        mStartRoutine(mpArgs);
    }
    else if (mTask)
    {
        (*(mTask.get()))();
    }
    else if (mFunc)
    {
        mFunc();
    }
    
//#ifdef ANDROID
//    JniHelper::ReleaseEnv();
//#endif
}

void ThreadImpl::Stop()
{
//    {
//        SpinLock::ScopeGuard lGuard(mStatusLock);
//        if (mStatus != Thread::Status::kRunning && mStatus != Thread::Status::kPause)
//            return;
//        mStatus = Thread::Status::kStop;
//    }
    if (mTask)
    {
        mTask->Stop();
    }
    if (mThread.joinable())
    {
        mThread.join();
    }
}

Thread::ID ThreadImpl::GetID()
{
    return mThread.get_id();
}

void ThreadImpl::Suspend()	// not implemented
{
}

void ThreadImpl::Detach()	// not implemented
{
#if 0
    if (mThread.joinable())
    {
        mThread.detach();
    }
#endif
}

void ThreadImpl::Join()		// not implemented
{
#if 0
    if (mThread.joinable())
    {
        mThread.join();
    }
#endif
}

bool ThreadImpl::IsJoinable()
{
    return mThread.joinable();
}

