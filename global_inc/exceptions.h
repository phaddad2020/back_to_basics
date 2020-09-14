/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Global utility exceptions                           *
 *                                                                  *
 *******************************************************************/

#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

class EmptyContainerException : std::exception
{
public:
    EmptyContainerException() { };

    const char* what() const noexcept override
    {
        return "Container is Empty";
    }
};



#endif

