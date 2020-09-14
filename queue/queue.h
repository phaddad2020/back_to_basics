/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Queue implementation                                *
 *                                                                  *
 *******************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdint.h>
#include <iostream>
#include <string>
#include <memory>

#include "exceptions.h"
#include "logger.h"

template<typename data_t>
class Queue
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
    /// Initializes a new instance of the Queue class
    /// </summary>
    Queue()
    {
        head = nullptr;
    }

    /// <summary>
    /// Since we are using smart pointers we don't need to actually destroy anything
    /// </summary>
    ~Queue()
    {
    }

    /// <summary>
    /// Check if the queue is empty
    /// </summary>
    /// <returns>TRUE if empty; FALSE if not</returns>
    bool Empty() const
    {
        return (head == nullptr);
    }

    /// <summary>
    /// Enqueue data onto the queue which will be at the tail
    /// </summary>
    /// <param>val</param> The data value to enqueue
    void Enqueue(const data_t& val)
    {
        if (Empty())
        {
            head = std::make_unique<node_s>(val);
            return;
        }

        auto new_node = std::make_unique<node_s>(val);
        node_s* curr = head.get();
        while (curr != nullptr)
        {
            if (curr->next == nullptr)
            {
                curr->next = std::move(new_node);
            }
            curr = curr->next.get();
        }
        BLOG(eLogInfo) << "Value [" << val << "] added to queue.";
    }

    /// <summary>
    /// Dequeue data from the queue which will be the head since we are adding
    /// to the tail the first data queued in will be at the head
    /// </summary>
    /// <return>The head data of the queue</return>
    data_t Dequeue()
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
    /// Print the queue from head to tail
    /// </summary>
    void Print(std::ostream& out = std::cout)
    {
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


