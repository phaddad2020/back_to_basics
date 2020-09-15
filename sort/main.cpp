/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Sort algorithms implementation                      *
 *                                                                  *
 *******************************************************************/

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"
#include "timer.h"
#include "read_file_values.h"

#include "selection_sort.h"

BLOG_INITIALISE(eLogDebug)
TIMER_INIT

void print_usage(const char *program)
{
    fprintf(stderr, "Usage: %s <filename>\n", program);
}

int main(int argc, char* argv[])
{
    BLOG(eLogInfo) << "Sorting algorithms implementation test program...";

    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    BLOG(eLogInfo) << "Reading from file [" << argv[1] << "]...";

    size_t big_array_size;
    long *big_array = ReadFileValues::ConstructArrayData(argv[1], &big_array_size);

    if (!big_array)
    {
        BLOG(eLogError) << "Could not create data array. Exiting...";
        return 1;
    }

    BLOG(eLogInfo) << "File read and array created of size [" << big_array_size << "]...";

    BLOG(eLogInfo) << "big_array[10]: " << big_array[10];
    BLOG(eLogInfo) << "big_array[999]: " << big_array[999];

    b_timer_t start_time = Timer::GetTimer();
    SelectionSort::Sort(big_array, big_array_size);
    b_timer_t end_time = Timer::GetTimer();
    b_timer_t diff = end_time - start_time;

    BLOG(eLogInfo) << "big_array[10]: " << big_array[10];
    BLOG(eLogInfo) << "big_array[999]: " << big_array[999];

    BLOG(eLogInfo) << "Time to sort: " << diff << "us, " << TIMER_MSEC(diff) << "ms, " << TIMER_SEC(diff) << "secs";

    delete big_array;

    return 0;
}


