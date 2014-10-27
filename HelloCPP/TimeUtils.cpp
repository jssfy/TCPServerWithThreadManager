//
//  TimeUtils.cpp
//  HelloCPP
//
//  Created by mstr on 10/27/14.
//  Copyright (c) 2014 jssfy. All rights reserved.
//

#include <chrono>

#include "TimeUtils.h"

int64_t TimeUtils::SystemNowInMicroseconds()
{
    return static_cast<int64_t>(std::chrono::time_point_cast<Microseconds>(Clock::now()).time_since_epoch().count());
}

int64_t TimeUtils::SystemNowInMilliseconds()
{
    return static_cast<int64_t>(std::chrono::time_point_cast<Milliseconds>(Clock::now()).time_since_epoch().count());
}

int64_t TimeUtils::SystemNowInSeconds()
{
    return static_cast<int64_t>(std::chrono::time_point_cast<Seconds>(Clock::now()).time_since_epoch().count());
}
