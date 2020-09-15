/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Sort algorithms implementation                      *
 *                                                                  *
 *******************************************************************/

#ifndef __SELECTION_SORT_H__
#define __SELECTION_SORT_H__

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"

/// <summary>
/// Singleton class to perform a selection sort which modifies the original
/// array passed in
/// </summary>
class SelectionSort
{
public:
    static void Sort(long *array, size_t arr_size)
    {
        if (!array || arr_size == 0)
        {
            BLOG(eLogError) << "Array data passed in is null.";
            return;
        }

        int m_idx;

        // Outer loop per index
        for (size_t i = 0; i < arr_size - 1; ++i)
        {
            // Set this as possible minimum index
            m_idx = i;

            // Loop through sub-array from i+1 to n
            for (size_t j = i + 1; j < arr_size; ++j)
            {
                // Check for the smallest index
                if (array[j] < array[m_idx])
                    m_idx = j;
            }

            // Swap smallest found with current index
            std::swap(array[m_idx], array[i]);
        }
    }
};

#endif

