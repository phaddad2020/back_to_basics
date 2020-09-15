/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Sort algorithms implementation                      *
 *                                                                  *
 *******************************************************************/

#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"

/// <summary>
/// Singleton class to perform a merge sort which modifies the original
/// array passed in however due to the nature of the algorithm itself we
/// do use temporary array memory on the stack in the process
/// </summary>
class MergeSort
{
public:
    static void Sort(long *array, int low, int high)
    {
        if (!array)
            return;

        if (low < high)
        {
            int mid = low + (high - low) / 2;

            Sort(array, low, mid);  // Sort lower half (recursively until low >= high, which is the new mid)
            Sort(array, mid + 1, high); // Sort higher half (recursively until low >= high, which is the new mid)

            merge(array, low, mid, high);   // Finally merge back
        }
    }

private:
    // Merge the two sub arrays
    static void merge(long *array, int low, int mid, int high)
    {
        if (!array)
            return;

        // First we split the array into two low and high
        int arr1_size = mid - low + 1;
        int arr2_size = high - mid;

        long low_arr[arr1_size];
        long high_arr[arr2_size];

        for (int i = 0; i < arr1_size; ++i)
            low_arr[i] = array[low + i];
        for (int i = 0; i < arr2_size; ++i)
            high_arr[i] = array[mid + 1 + i];

        // Now that we have split the arrays we need to merge them back but this
        // time we do it while sorting
        int x = 0, y = 0, z = low;
        while (x < arr1_size && y < arr2_size)
        {
            if (low_arr[x] <= high_arr[y])
            {
                array[z] = low_arr[x];
                x++;
            }
            else
            {
                array[z] = high_arr[y];
                y++;
            }
            z++;
        }

        // Copy any remaining elements
        while (x < arr1_size)
        {
            array[z] = low_arr[x];
            x++;
            z++;
        }

        while (y < arr2_size)
        {
            array[z] = high_arr[y];
            y++;
            z++;
        }
    }

};

#endif
