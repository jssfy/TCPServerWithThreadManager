//
//  DefaultDelete.h
//  HelloCPP
//
//  Created by mstr on 10/24/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#ifndef __HelloCPP__DefaultDelete__
#define __HelloCPP__DefaultDelete__

#include <stdio.h>
#include <stdlib.h>

template<typename T>
class CStackMemoryAlloctor
{
    mutable T* _ptr;
    
public:
    explicit CStackMemoryAlloctor(size_t size) throw() : _ptr(nullptr)
    {
        _ptr = (T*)malloc(size);
    }
    
    ~CStackMemoryAlloctor()
    {
        if (_ptr)
            free(_ptr);
    }
    
public:
    operator T*() const throw()
    {
        T* tmp = _ptr;
        _ptr = nullptr;
        return tmp;
    }
    
public:
    T* GetPtr() const throw()
    {
        return _ptr;
    }
};

#endif /* defined(__HelloCPP__DefaultDelete__) */
