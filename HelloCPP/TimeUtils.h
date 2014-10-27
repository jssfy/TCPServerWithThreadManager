//
//  TimeUtils.h
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#ifndef __HelloCPP__TimeUtils__
#define __HelloCPP__TimeUtils__

#include <stdint.h> // int64_t


class TimeUtils
{
public:
    /**
     * get the current system time with microsecond precision
     * @return the timestamp value
     */
    static int64_t SystemNowInMicroseconds();

    /**
     * get the current system time with millisecond precision
     * @return the timestamp value
     */
    static int64_t SystemNowInMilliseconds();

    /**
     * get the current system time with second precision
     * @return the timestamp value
     */
    static int64_t SystemNowInSeconds();
    
private:
    typedef std::chrono::microseconds Microseconds;
    typedef std::chrono::milliseconds Milliseconds;
    typedef std::chrono::seconds Seconds;
    typedef std::chrono::system_clock Clock;
};

#endif /* defined(__HelloCPP__TimeUtils__) */
