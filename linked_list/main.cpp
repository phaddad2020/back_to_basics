/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Linked List implementation                          *
 *                                                                  *
 *******************************************************************/

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"
#include "linked_list.h"

BLOG_INITIALISE(eLogDebug)

int main(int argc, char* argv[])
{
    BLOG(eLogInfo) << "Linked List implementation test program...";

    LinkedList<int> integer_list;

    if (integer_list.Empty())
    {
        BLOG(eLogInfo) << "Linked List is empty";
    }

    // Insert some numbers in a list
    integer_list.Insert(10);
    integer_list.Insert(2);
    integer_list.Insert(5);
    integer_list.Insert(1);
    integer_list.Insert(8);
    integer_list.Insert(9);
    integer_list.Insert(9);
    integer_list.Insert(9);

    integer_list.Print();
    integer_list.Delete(9);
    integer_list.Print();
    integer_list.Delete(9, true);
    integer_list.Print();


    return 0;
}

