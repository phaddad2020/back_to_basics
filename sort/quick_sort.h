/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Sort algorithms implementation                      *
 *                                                                  *
 *******************************************************************/

#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"

/// <summary>
/// Singleton class to perform a merge sort which modifies the original
/// array passed. Very similar to merge sort except we can decide on the
/// pivot point. Quick sort algorithm is also not ideal for containers that
/// don't allow random access. For the purposes of this example we will use
/// the standard pivot point of the last element in the array
/// </summary>
class QuickSort
{
public:
    static void Sort(long *array, int low, int high)
    {
        if (low < high) // Recursive bad condition
        {
            int part_idx = partition(array, low, high); // At this point array[part_idx] is considered to be in the correct position

            Sort(array, low, part_idx - 1); // Sort before pivot
            Sort(array, part_idx + 1, high); // Sort after pivot
        }
    }

private:
    static int partition(long *array, int low, int high)
    {
        if (!array)
            return 0;

        int pivot = array[high];
        int idx = low - 1;

        for (int i = low; i <= high - 1; ++i)
        {
            if (array[i] < pivot)
            {
                idx++;
                std::swap(array[idx], array[i]);
            }
        }
        std::swap(array[idx + 1], array[high]);
        return (idx + 1);
    }
};

#endif
