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
#include <cstring>

#include "logger.h"
#include "timer.h"
#include "read_file_values.h"

#include "selection_sort.h"
#include "bubble_sort.h"
#include "merge_sort.h"

BLOG_INITIALISE(eLogDebug)
TIMER_INIT

void print_usage(const char *program)
{
    fprintf(stderr, "Usage: %s <filename>\n", program);
}

void print_array(long* arr, size_t size)
{
    if (!arr || size == 0)
        return;

    for (size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << ", ";
    }

    std::cout << std::endl;
}

typedef enum sort_type_e
{
    SELECTION_SORT  = 0,
    BUBBLE_SORT,
    MERGE_SORT,
} SortType_e;

const char* convert_sort_type_to_str(int s_type)
{
    switch (s_type)
    {
    case SELECTION_SORT:
        return "Selection Sort";
    case BUBBLE_SORT:
        return "Bubble Sort";
    case MERGE_SORT:
        return "Merge Sort";
    default:
        return "Unknown Sort";
    }
}

int main(int argc, char* argv[])
{
    BLOG(eLogInfo) << "Sorting algorithms implementation test program...";

    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    // Selection sort by default
    int sort_type = SELECTION_SORT;

    if (argc == 3)
    {
        if (strcmp(argv[2], "-b") == 0)
        {
            sort_type = BUBBLE_SORT;
        }

        if (strcmp(argv[2], "-m") == 0)
        {
            sort_type = MERGE_SORT;
        }
    }

    BLOG(eLogInfo) << "Sort method selected [" << convert_sort_type_to_str(sort_type) << "]...";
    BLOG(eLogInfo) << "Reading from file [" << argv[1] << "]...";

    size_t array_size;
    long *array = ReadFileValues::ConstructArrayData(argv[1], &array_size);

    if (!array)
    {
        BLOG(eLogError) << "Could not create data array. Exiting...";
        return 1;
    }

    BLOG(eLogInfo) << "File read and array created of size [" << array_size << "]...";

    b_timer_t start_time = Timer::GetTimer();
    switch (sort_type)
    {
    case SELECTION_SORT:
        SelectionSort::Sort(array, array_size);
        break;
    case BUBBLE_SORT:
        BubbleSort::Sort(array, array_size);
        break;
    case MERGE_SORT:
        MergeSort::Sort(array, 0, array_size - 1);
    default:
        break;
    }
    b_timer_t end_time = Timer::GetTimer();
    b_timer_t diff = end_time - start_time;

    //print_array(array, array_size);

    BLOG(eLogInfo) << "Time to sort: " << diff << "us, " << TIMER_MSEC(diff) << "ms, " << TIMER_SEC(diff) << "secs";

    delete array;

    return 0;
}


