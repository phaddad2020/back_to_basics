/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Sort algorithms implementation                      *
 *                                                                  *
 *******************************************************************/

#ifndef __BUBBULE_SORT_H__
#define __BUBBULE_SORT_H__

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"

/// <summary>
/// Singleton class to perform a bubble sort which modifies the original
/// array passed in
/// </summary>
class BubbleSort
{
public:
    static void Sort(long *array, size_t arr_size)
    {
        if (!array || arr_size == 0)
        {
            BLOG(eLogError) << "Array data passed in is null.";
            return;
        }

        uint32_t no_swap = 1;

        // Outer loop
        for (size_t i = 0; i < arr_size - 1; ++i)
        {
            no_swap = 1;

            // Inner loop check against next element
            for (size_t j = 0; j < arr_size - i - 1; ++j)
            {
                if (array[j] > array[j + 1])
                {
                    std::swap(array[j], array[j + 1]);
                    no_swap = 0;
                }
            }

            // If the inner loop had no swappage then break out, otherwise
            // this loop will continue and take more time then needed
            if (no_swap)
                break;
        }
    }
};

#endif
