/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Binary Tree implementation                          *
 *                                                                  *
 *******************************************************************/

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdint.h>
#include <iostream>
#include <string>
#include <memory>

#include "exceptions.h"
#include "logger.h"

template<typename data_t>
class BinaryTree
{
public:
    struct node_s
    {
        data_t data;
        std::unique_ptr<node_s> left;
        std::unique_ptr<node_s> right;

        node_s(const data_t& val)
            : data(val)
        {
            left = nullptr;
            right = nullptr;
        }
    };

    /// <summary>
    /// Initializes a new instance of the BinaryTree class.
    /// </summary>
    BinaryTree()
    {
        root = nullptr;
    }

    /// <summary>
    /// Since we are using smart pointers we don't need to actually destroy anything
    /// </summary>
    ~BinaryTree()
    {
    }

    /// <summary>
    /// Insert data into a new node on the tree
    /// </summary>
    /// <param>val</param> The data to insert
    void Insert(const data_t& val)
    {
        if (root == nullptr)
        {
            root = std::make_unique<node_s>(val);
            BLOG(eLogDebug) << "New node [" << val << "] added as root";
        }
        else
        {
            insertNode(root.get(), val);
        }
    }

    /// <summary>
    /// Remove a data and node from the tree
    /// </summary>
    /// <param>val</param> The data to remove
    void Remove(const data_t& val)
    {
        if (root == nullptr)
        {
            throw EmptyContainerException { };
        }

        removeNode(root, val);
    }

    /// <summary>
    /// Get the maximum value data in this tree
    /// <summary>
    /// <returns>The maximum value data in tree</returns>
    const data_t& GetMaxData() const
    {
        if (root == nullptr)
        {
            throw EmptyContainerException { };
        }

        return getMaxNode(root.get());
    }

    /// <summary>
    /// Get the minimum value data in this tree
    /// <summary>
    /// <returns>The minimum value data in tree</returns>
    const data_t& GetMinData() const
    {
        if (root == nullptr)
        {
            throw EmptyContainerException { };
        }

        return getMinNode(root.get());
    }

    /// <summary>
    /// Traverse the tree in order and print contents
    /// <summary>
    void InOrderTraversal(std::ostream& out = std::cout) const
    {
        if (root == nullptr)
        {
            out << "Binary Tree is empty!" << std::endl;
        }

        traverseInOrder(out, root.get());

        out << std::endl;
    }

private:
    
    /// <summary>
    /// Recursive function to find a spot to insert node on binary tree
    /// <summary>
    /// <param>root</param> The root node to search from
    /// <param>val</param> The data to insert
    void insertNode(node_s* root, const data_t& val)
    {
        if (val < root->data)
        {
            if (root->left)
            {
                insertNode(root->left.get(), val);
            }
            else
            {
                root->left = std::make_unique<node_s>(val);
                BLOG(eLogDebug) << "New node [" << val << "] added to left leaf";
            }
        }
        else if (val > root->data)
        {
            if (root->right)
            {
                insertNode(root->right.get(), val);
            }
            else
            {
                root->right = std::make_unique<node_s>(val);
                BLOG(eLogDebug) << "New node [" << val << "] added to right leaf";
            }
        }
        else
        {
            BLOG(eLogWarning) << "This data already exists! Ignoring....";
            return;
        }
    }

    /// <summary>
    /// Recursive function to remove a data node from the tree
    /// </summary>
    /// <param>root_ref</param>Reference to the root node to search from
    /// <param>val</param>The data to search for and remove
    void removeNode(std::unique_ptr<node_s> &root_ref, const data_t& val)
    {
        // Lets search for the node we need to remove
        if (val < root_ref->data)
        {
            removeNode(root_ref->left, val);
        }
        else if (val > root_ref->data)
        {
            removeNode(root_ref->right, val);
        }
        else    // We have found the right node
        {
            // Check if this is a leaf node
            if (root_ref->left == nullptr && root_ref->right == nullptr)
            {
                BLOG(eLogInfo) << "Removing leaf node...";
                root_ref.reset();
            }

            // If there is a right child
            if (root_ref->left == nullptr)
            {
                BLOG(eLogInfo) << "Removing right child...";
                std::unique_ptr<node_s> tmp_node = std::move(root_ref->right);
                root_ref.reset();
                root_ref = std::move(tmp_node);
                return;
            }
            else if (root_ref->right == nullptr)
            {
                BLOG(eLogInfo) << "Removing left child...";
                std::unique_ptr<node_s> tmp_node = std::move(root_ref->left);
                root_ref.reset();
                root_ref = std::move(tmp_node);
                return;
            }

            // If we reached here then this node has 2 children
            BLOG(eLogInfo) << "Removing node with two children...";
            auto temp_node = detachRight(root_ref->left);
            temp_node->right = std::move(root_ref->right);
            std::unique_ptr<node_s> &temp_left = getLeft(temp_node);
            temp_left->left = std::move(root_ref->left);
            root_ref.reset();
            root_ref = std::move(temp_node);
        }
    }

    /// <summary>
    /// Recursive function to travel down the right most side of the binary tree to
    /// find the maximum value node
    /// </summary>
    /// <param>root</param>The node to search from
    /// <returns>The data of the right most node</returns>
    const data_t& getMaxNode(node_s* root) const
    {
        if (root->right)
            return getMaxNode(root->right.get());

        return root->data;
    }

    /// <summary>
    /// Recursive function to travel down the left most side of the binary tree to
    /// find the minimum value node
    /// </summary>
    /// <param>root</param>The node to search from
    /// <returns>The data of the left most node</returns>
    const data_t& getMinNode(node_s* root) const
    {
        if (root->left)
            return getMinNode(root->left.get());

        return root->data;
    }

    /// <summary>
    /// Recursive function to travese in order the binary tree while printing out
    /// the data contents
    /// <summary>
    /// <param>out</param>The output stream to use
    /// <param>root</param>The node to traverse from
    void traverseInOrder(std::ostream& out, node_s* root) const
    {
        if (root->left)
            traverseInOrder(out, root->left.get());

        out << root->data << " --> ";

        if (root->right)
            traverseInOrder(out, root->right.get());
    }

    /// <summary>
    /// This function will traverse the right nodes recursively until the final
    /// node so we can detach and return its contents
    std::unique_ptr<node_s> detachRight(std::unique_ptr<node_s> &node_ref)
    {
        if (node_ref->right)
            detachRight(node_ref->right);

        return std::move(node_ref);
    }

    /// <summary>
    /// This function will travese the left nodes recursively until the final
    /// node reference is found and then returned
    /// <summary>
    std::unique_ptr<node_s>& getLeft(std::unique_ptr<node_s> &node_ref)
    {
        if (node_ref->left)
            getLeft(node_ref->left);

        return node_ref;
    }

    std::unique_ptr<node_s> root;

};

#endif

