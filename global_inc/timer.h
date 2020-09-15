/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Global utility timer                                *
 *                                                                  *
 *******************************************************************/

#ifndef __TIMER_H__
#define __TIMER_H__

#include <iostream>
#include <stdint.h>
#include <time.h>

typedef uint64_t b_timer_t;

#define TIMER_INIT  int Timer::init_time = 0;

#define TIMER_MSEC(value)   (value / 1000)
#define TIMER_SEC(value)    (value / 1000000)

/// <summary>
/// Singleton timer class that gets time. This must be first initiailized at the
/// beginning of program execution using the MACRO define above.
/// </summary>
class Timer
{
public:
    static int init_time;

    /// <summary>
    /// Get the timer in microseconds
    /// </summary>
    static b_timer_t GetTimer()
    {
        struct timespec tp;
        b_timer_t new_tic;

        clock_gettime(CLOCK_MONOTONIC, &tp);
        if (!init_time)
            init_time = tp.tv_sec;

        new_tic = (b_timer_t) ((((b_timer_t) (tp.tv_sec - init_time) * 1000000) +
                              (tp.tv_nsec / 1000)));

        return new_tic;
    }

};

#endif


