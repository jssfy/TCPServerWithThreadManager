//
//  ThreadManagerImpl.cpp
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#include "ThreadManagerImpl.h"
#include "ThreadImpl.h"

ThreadManagerPtr ThreadManagerImpl::msThreadManagerPtr(nullptr);
std::mutex ThreadManagerImpl::msThreadManagerMutex;


ThreadManagerImpl::ThreadManagerImpl()
{
    
}

ThreadManagerImpl::~ThreadManagerImpl()
{
    // TODO
//    StopAll();
    msThreadManagerPtr = nullptr;
}

ThreadManagerPtr ThreadManager::DefaultThreadManager()
{
    return ThreadManagerImpl::DefaultThreadManager();
}

ThreadManagerPtr ThreadManagerImpl::DefaultThreadManager()
{
    if (!msThreadManagerPtr.get())
    {
        std::lock_guard<std::mutex> lGuard(msThreadManagerMutex);
        if (!msThreadManagerPtr.get())
            msThreadManagerPtr = ThreadManagerPtr(new ThreadManagerImpl());
    }
    return msThreadManagerPtr;
}

ThreadPtr ThreadManagerImpl::CreateThread(TaskPtr iTask)
{
    ThreadPtr lNewThread = ThreadPtr(new ThreadImpl(std::move(iTask)));
    // ThreadFactoryImpl::DefaultThreadFactory()->CreateThread(std::move(iTask));
    hAddThread(lNewThread);
    // start the thread automatically
    lNewThread->Start();
    return lNewThread;
}

void ThreadManagerImpl::hAddThread(ThreadPtr iThread)
{
    std::lock_guard<std::mutex> lGuard(mAllThreadsLock);
//    decltype(mAllThreads) lAllThreads;
//    lAllThreads.swap(mAllThreads);
//    for (auto& lThread : lAllThreads)
//    {
////        if (lThread && lThread->GetStatus() != Thread::Status::kStop)
//        {
//            mAllThreads.push_back(lThread);
//        }
//    }
    
    mAllThreads.push_back(std::move(iThread));
}


void ThreadManagerImpl::StopAll()
{
    {
        std::lock_guard<std::mutex> lGuard(mAllThreadsLock);
        for (auto& lrThread : mAllThreads)
        {
            lrThread->Stop();
        }
    }
    
//    {
//        std::lock_guard<std::mutex> lGuard(mAllThreadPoolsLock);
//        for (auto& lrThreadPool : mAllThreadPools)
//        {
//            lrThreadPool->Stop();
//        }
//    }
}

