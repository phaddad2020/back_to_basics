/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Stack implementation                                *
 *                                                                  *
 *******************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stdint.h>
#include <iostream>
#include <string>
#include <memory>

#include "exceptions.h"
#include "logger.h"

template<typename data_t>
class Stack
{
public:
    struct node_s
    {
        data_t data;
        std::unique_ptr<node_s> next;

        node_s(const data_t& val)
            : data(val)
        {
            next = nullptr;
        }
    };

    /// <summary>
    /// Initializes a new instance of the Stack class
    /// </summary>
    Stack()
    {
        head = nullptr;
    }

    /// <summary>
    /// Since we are using smart pointers we don't need to actually destroy anything
    /// </summary>
    ~Stack()
    {
    }

    /// <summary>
    /// Check if the stack is empty
    /// </summary>
    /// <returns>TRUE if empty; FALSE if not</returns>
    bool Empty() const
    {
        return (head == nullptr);
    }

    /// <summary>
    /// Push data onto the stack which will be the head
    /// </summary>
    /// <param>val</param> The data value to push
    void Push(const data_t& val)
    {
        auto new_node = std::make_unique<node_s>(val);
        if (Empty())
        {
            head = std::move(new_node);
        }
        else
        {
            new_node->next = std::move(head);
            head = std::move(new_node);
        }
        BLOG(eLogInfo) << "Value [" << val << "] pushed onto stack.";
    }

    /// <summary>
    /// Pop data from the stack which will be the head
    /// </summary>
    /// <return>The head data of the stack</return>
    data_t Pop()
    {
        if (Empty())
        {
            throw EmptyContainerException { };
        }

        data_t data_return = std::move(head->data);
        head = std::move(head->next);

        return data_return;
    }

    /// <summary>
    /// Print the stack from head to tail
    /// </summary>
    void Print(std::ostream& out = std::cout)
    {
        if (Empty())
        {
            out << "Stack is empty!" << std::endl;
        }

        node_s* curr = head.get();

        while (curr != nullptr)
        {
            out << "[" << curr->data << "] -> ";
            curr = curr->next.get();
        }

        out << std::endl;
    }

private:
    std::unique_ptr<node_s> head;
};

#endif

