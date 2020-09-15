/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Global utility to read integer data values from a   *
 *              given file in a specific format and return a newly  *
 *              constructed array with that data. This is not very  *
 *              generic and only intended for use with tests in     *
 *              this workspace                                      *
 *                                                                  *
 *******************************************************************/

#ifndef __READ_FILE_VALUES_H__
#define __READ_FILE_VALUES_H__

#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <iostream>
#include <fstream>

#include "logger.h"

/// <summary>
/// Singleton class which reads in a file creates memory for the data array
/// and returns it. The expected file format should just be a single integer
/// per new line
/// <summary>
class ReadFileValues
{
public:
    static long* ConstructArrayData(const char* filename, size_t *arr_size)
    {
        if (!filename)
        {
            BLOG(eLogError) << "Filename passed in is NULL.";
            return nullptr;
        }

        std::ifstream in_file(filename, std::ios::in);

        if (in_file.is_open())
        {
            size_t size = 0;
            std::string line = "";
            while (!in_file.eof())
            {
                std::getline(in_file, line);
                size++;
            }

            // Common mistake here, don't forget clear to reset the state otherwise seekg doesn't work
            in_file.clear();
            in_file.seekg(0);   // Go back to start of file

            *arr_size = size;
            long *data_array = new long[size];
            int data_ctr = 0;

            while (!in_file.eof())
            {
                std::getline(in_file, line);
                long val = parseValue(line.c_str());
                data_array[data_ctr] = val;
                data_ctr++;
            }

            in_file.close();

            return data_array;
        }
        else
        {
            BLOG(eLogError) << "Unable to open file [" << filename << "].";
            return nullptr;
        }
    }

private:
    static long parseValue(const char *txt)
    {
        long val;
        char* end_ptr;
        errno = 0;
        val = strtol(txt, &end_ptr, 10);
        if (errno == ERANGE)
        {
            if (val == LONG_MIN)
            {
                BLOG(eLogError) << "value [" << txt << "] causes an underflow.";
                return 0;
            }

            if (val == LONG_MAX)
            {
                BLOG(eLogError) << "value [" << txt << "] causes an overflow.";
                return 0;
            }
        }
        else if (errno != 0 && val == 0)
        {
            BLOG(eLogError) << "Some other error occured parsing value [" << txt << "].";
        }

        return val;
    }
};

#endif

