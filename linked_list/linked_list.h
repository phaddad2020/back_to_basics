/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Linked List implementation                          *
 *                                                                  *
 *******************************************************************/

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdint.h>
#include <iostream>
#include <string>
#include <memory>

#include "exceptions.h"

/// <summary>
/// A simple linked list class implemented using smart pointers
/// </summary>
template<typename data_t>
class LinkedList
{
public:
    struct node_s
    {
        data_t data;
        std::unique_ptr<node_s> next;

        node_s(const data_t &val)
            : data(val)
        {
            next = nullptr;
        }

        ~node_s()
        {
            //BLOG(eLogDebug) << "Node with data [" << data << "] destroyed";
        }
    };

    /// <summary>
    /// Initializes a new instance of the LinkedList class
    /// </summary>
    LinkedList()
    {
        head = nullptr;
    }

    /// <summary>
    /// Since we are using smart pointers we don't need to actually destroy anything
    /// </summary>
    ~LinkedList()
    {
    }

    /// <summary>
    /// Check if the linked list is empty
    /// </summary>
    /// <returns>TRUE if empty; FALSE if not</returns>
    bool Empty() const
    {
        return (head == nullptr);
    }

    /// <summary>
    /// Insert data into the linked list at the head
    /// </summary>
    /// <param>val</param> The data value to insert
    void InsertHead(const data_t& val)
    {
        auto new_node = std::make_unique<node_s>(val);
        if (head == nullptr)
        {
            head = std::move(new_node);
        }
        else
        {
            new_node->next = std::move(head);
            head = std::move(new_node);
        }
        BLOG(eLogInfo) << "Value [" << val << "] added to list.";
    }

    /// <summary>
    /// Insert data into the linked list at the tail
    /// </summary>
    /// <param>val</param> The data value to insert
    void InsertTail(const data_t& val)
    {
        if (Empty())
        {
            InsertHead(val);
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
        BLOG(eLogInfo) << "Value [" << val << "] added to list.";
    }

    /// <summary>
    /// Delete a data value if found in the list. Unless the all flag is specified then only
    /// the first found occurence of the data will be deleted
    /// </summary>
    /// <param>val</param> The data value to delete
    /// <param>all</param> Flag indicating whether all occurences should be deleted or not
    ///                    This is false by default
    void Delete(const data_t& val, bool all = false)
    {
        if (Empty())
        {
            throw EmptyContainerException { };
        }

        // First we need to check possibilities surrounding the head
        while (head->data == val)
        {
            BLOG(eLogInfo) << "Found data [" << val << "] removing...";
            std::unique_ptr<node_s> tmp = std::move(head->next);
            head.reset();
            head = std::move(tmp);

            if (!all)
                return;
        }

        node_s* next_node = head.get();
        while (next_node->next != nullptr)
        {
            if (next_node->next->data == val)
            {
                BLOG(eLogInfo) << "Found data [" << val << "] removing...";
                next_node->next = std::move(next_node->next->next);

                if (!all)
                    return;
            }
            next_node = next_node->next.get();
        }
    }

    /// <summary>
    /// Print the linked list from head to tail
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
