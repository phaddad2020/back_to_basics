/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Utility program to generate a random array of data  *
 *              and output it to a stream                           *
 *                                                                  *
 *******************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cstring>

#include "logger.h"

BLOG_INITIALISE(eLogDebug)

void print_usage(const char* program)
{
    fprintf(stderr, "Usage: %s [min] [max] [filename] [-v]\n", program);
    fprintf(stderr, "\tmin and max must be integers where max > min and neither are 0\n");
    fprintf(stderr, "\tfilename is optional, if none provided will print out to console\n");
    fprintf(stderr, "\t-v [verbose] is optional and will print out array data\n");
}

long parse_value(const char* arg)
{
    long val;
    char* end_ptr;
    errno = 0;
    val = strtol(arg, &end_ptr, 10);
    if (errno == ERANGE)
    {
        if (val == LONG_MIN)
        {
            BLOG(eLogError) << "value [" << arg << "] causes an underflow.";
            return 1;
        }

        if (val == LONG_MAX)
        {
            BLOG(eLogError) << "value [" << arg << "] causes an overflow.";
            return 1;
        }
    }
    else if (errno != 0 && val == 0)
    {
        BLOG(eLogError) << "Some other error occured parsing value [" << arg << "].";
    }

    return val;
}

void print_array(long* arr, long arr_size)
{
    if (!arr || arr_size <= 0)
        return;

    for (int i = 0; i < arr_size - 1; ++i)
    {
        fprintf(stdout, "array[%d]: %lu\n", i, arr[i]);
    }
}

void randomize_array(long* arr, long arr_size)
{
    if (!arr || arr_size <= 0)
        return;

    // Initialize a random seed using time
    srand(time(NULL));

    for (long i = arr_size - 2; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        print_usage(argv[0]);
        return 1;
    }

    BLOG(eLogInfo) << "Generate Random Array Data Utility...";

    long min = 0;
    long max = 0; 
    long* array = nullptr;
    const char* filename = nullptr;
    bool verbose = false;

    min = parse_value(argv[1]);
    max = parse_value(argv[2]);

    if (min == 0 || max == 0)
    {
        BLOG(eLogError) << "Couldn't parse both min and max values, exiting...";
        return 1;
    }

    if (argc >= 4)
    {
        filename = argv[3];
    }

    if (argc == 5)
    {
        if (strcmp(argv[4], "-v") == 0)
            verbose = true;
    }

    BLOG(eLogInfo) << "Generating random array from [" << min << "] to [" << max << "]...";
    BLOG(eLogInfo) << "Using filename [" << filename << "] for output...";

    long array_size = max - min + 2;
    array = new long[array_size];
    if (!array)
    {
        BLOG(eLogError) << "Unable to allocate memory for array of size [" << max << "].";
        BLOG(eLogError) << "Exiting...";
        return 1;
    }

    long ctr = min;
    for (long i = 0; i < array_size - 1; ++i)
    {
        array[i] = ctr;
        ctr++;
    }

    array[array_size - 1] = -1; // Terminator

    if (verbose)
        print_array(array, array_size);

    randomize_array(array, array_size);

    print_array(array, array_size);

    if (filename != nullptr)
    {
        std::ofstream out_file(filename, std::ios::out);
        if (out_file.is_open())
        {
            for (long i = 0; i < array_size - 1; ++i)
            {
                out_file << array[i];
                out_file << "\n";
            }

            out_file.close();
        }
        else
        {
            BLOG(eLogError) << "File [" << filename << "] could not be opened for writing!";
            BLOG(eLogError) << "Exiting...";
            if (array)
                delete array;
            return 1;
        }
    }

    if (array)
        delete array;

    return 0;
}

