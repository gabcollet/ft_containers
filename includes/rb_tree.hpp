/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:39:04 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/24 18:43:03 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "rb_tree_node.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include <sys/qos.h>

#define RED "\033[31;1m"
#define YELLOW "\033[93;1m"
#define END "\033[0m"

enum {LEFT, RIGHT};

namespace ft
{
    template < typename compare, typename value_type, 
                typename alloc = std::allocator<value_type> >
    class rb_tree
    {
        
    public:
        typedef rb_tree_node<value_type>                        node;
        typedef rb_tree_node<value_type>*                       node_pointer;
        typedef typename alloc::template rebind<node>::other    node_alloc;

        //Default constructor
        rb_tree() { _rootN = NULL; }

        //Parameterized constructor
        rb_tree(value_type val)
        {
            _rootN = _node_alloc.allocate(1);
            _alloc.construct(&_rootN->data, val);
            _rootN->color = black;
            _rootN->left = NULL;
            _rootN->right = NULL;
            _rootN->parent = NULL;
        }

        void insert(value_type val)
        {
            if (!_rootN)
            {
                _rootN = _node_alloc.allocate(1);
                _alloc.construct(&_rootN->data, val);
                _rootN->color = black;
                _rootN->left = NULL;
                _rootN->right = NULL;
                _rootN->parent = NULL;
                return;
            }
            node_pointer newnode = _node_alloc.allocate(1);
            node_pointer tmp = _rootN;
            //Find node position
            while (true)
            {
                if (comp(tmp->data, val))
                {
                    if (tmp->right == NULL)
                        break;
                    tmp = tmp->right;
                }
                else if (comp(val, tmp->data))
                {
                    if (tmp->left == NULL)
                        break;
                    tmp = tmp->left;
                }
                else
                    return;
            }
            _alloc.construct(&newnode->data, val);
            newnode->parent = tmp;
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->color = red;
            if (comp(val, tmp->data))
                tmp->left = newnode;
            else
                tmp->right = newnode;
            fixinsert(newnode);
        }

        void deleteNode(value_type val)
        {
            if (val == _rootN->data)
                return;

            node_pointer node = _rootN;
            //Find node with value
            while (true)
            {
                if (node->data == val)
                    break;
                if (node->right && comp(node->data, val))
                    node = node->right;
                else if (node->left && comp(val, node->data))
                    node = node->left;
                else
                    return;
            }
            
            node_pointer tmp = node;
            //case with two child
            if (node->left && node->right)
            {
                tmp = minValueNode(node->left);
                node->data = tmp->data;
                if (tmp->parent != node)
                    tmp->parent->right = NULL;
                if (tmp->left)
                    tmp = copyBranch(tmp, LEFT);
            }
            //case with only one child
            else if (node->left || node->right)
            {    
                if (node->left)
                    tmp = copyBranch(tmp, LEFT);
                else
                    tmp = copyBranch(tmp, RIGHT);
            }
            //case with no child
            else //!ca fuck ici avant d'aller dans fixdelete 
            {
                if (tmp->parent->left == tmp)
                    tmp->parent->left = NULL; 
                else if (tmp->parent->right == tmp)
                    tmp->parent->right = NULL;
            }

                fixdelete(tmp);
            
            if (tmp->parent->left == tmp && 
                tmp->left == NULL && tmp->right == NULL)
                tmp->parent->left = NULL;
                
            _alloc.destroy(&tmp->data);
            _node_alloc.deallocate(tmp, 1);
        }

        void treePrint()
        {
            if (_rootN) 
            {
                _printTree(_rootN, "", true);
                std::cout << std::endl;
            }
        }

    private:
        node_pointer _rootN;
        node_alloc _node_alloc;
        alloc _alloc;
        compare comp;

        void fixinsert(node_pointer newnode)
        {
            // Red/Black Property: Every node is colored, either red or black.
            // Root Property: The root is black.
            // Leaf Property: Every leaf (NIL) is black.
            // Red Property: If a red node has children then, the children are always black.
            // Depth Property: For each node, any simple path from this node to any of its descendant leaf has the same black-depth (the number of black nodes).
            // https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
            
            node_pointer uncle;
            
            while (newnode->parent->color == red){
                if (newnode->parent == newnode->parent->parent->right){
                    uncle = newnode->parent->parent->left;
                    if (uncle && uncle->color == red){
                        uncle->color = black;
                        newnode->parent->color = black;
                        newnode->parent->parent->color = red;
                        newnode = newnode->parent->parent;
                    }
                    else {
                        if (newnode == newnode->parent->left){
                            newnode = newnode->parent;
                            right_rotate(newnode);
                        }
                        newnode->parent->color = black;
                        newnode->parent->parent->color = red;
                        left_rotate(newnode->parent->parent);
                    }
                }
                else {
                    uncle = newnode->parent->parent->right;
                    if (uncle && uncle->color == red){
                        uncle->color = black;
                        newnode->parent->color = black;
                        newnode->parent->parent->color = red;
                        newnode = newnode->parent->parent;
                    }
                    else {
                        if (newnode == newnode->parent->right){
                            newnode = newnode->parent;
                            left_rotate(newnode);
                        }
                        newnode->parent->color = black;
                        newnode->parent->parent->color = red;
                        right_rotate(newnode->parent->parent);
                    }
                }
                if (newnode == _rootN)
                    break;
            }
            _rootN->color = black;
        }

        void fixdelete(node_pointer node)
        {
            while (node != _rootN && node->color == black){
                if (node == node->parent->left){
                    node_pointer sister = node->parent->right;
                    if (sister->color == red){
                        sister->color = black;
                        node->parent->color = red;
                        left_rotate(node->parent);
                        sister = node->parent->right;
                    }
                    if (sister->left && sister->right &&
                        sister->left->color == black &&
                        sister->right->color == black){
                        sister->color = red;
                        node = node->parent;
                    }
                    else {
                        if (sister->right && sister->right->color == black) {
                            sister->left->color = black;
                            sister->color = red;
                            right_rotate(sister);
                            sister = node->parent->right;
                        }
                        sister->color = node->parent->color;
                        node->parent->color = black;
                        if (sister->right){
                            sister->right->color = black;
                            left_rotate(node->parent);
                        }
                        node = _rootN;
                    }
                }
                else {
                    node_pointer sister = node->parent->left;
                    if (sister->color == red){
                        sister->color = black;
                        node->parent->color = red;
                        right_rotate(node->parent);
                        sister = node->parent->left;
                    }
                    if (sister->right && sister->left &&
                        sister->right->color == black &&
                        sister->left->color == black){
                        sister->color = red;
                        node = node->parent;
                    }
                    else {
                        if (sister->left && sister->left->color == black) {
                            sister->right->color = black;
                            sister->color = red;
                            left_rotate(sister);
                            sister = node->parent->left;
                        }
                        sister->color = node->parent->color;
                        node->parent->color = black;
                        if (sister->left){
                            sister->left->color = black;
                            right_rotate(node->parent);
                        }
                        node = _rootN;
                    }
                }
            }
            node->color = black;
        }

        void right_rotate(node_pointer a)
        {
            node_pointer b = a->left;
            a->left = b->right;
            if (b->right)
                b->right->parent = a;
            b->parent = a->parent;
            if (a->parent == NULL)
                _rootN = b;
            else if (a == a->parent->right)
                a->parent->right = b;
            else
                a->parent->left = b;
            b->right = a;
            a->parent = b;
        }
        
        void left_rotate(node_pointer a)
        {
            node_pointer b = a->right;
            a->right = b->left;
            if (b->left)
                b->left->parent = a;
            b->parent = a->parent;
            if (a->parent == NULL)
                _rootN = b;
            else if (a == a->parent->left)
                a->parent->left = b;
            else
                a->parent->right = b;
            b->left = a;
            a->parent = b;
        }
        
        node_pointer minValueNode(node_pointer node)
        {
            node_pointer minNode = node;
            while (minNode && minNode->right)
                minNode = minNode->right;
            return minNode;
        }

        node_pointer copyBranch(node_pointer node, bool side)
        {
            node_pointer tmp = node;
            if (side == RIGHT)
            {
                while (tmp->right)
                {
                    tmp->data = tmp->right->data;
                    tmp = tmp->right;
                }
                tmp->parent->right = NULL;
            }
            if (side == LEFT)
            {
                while (tmp->left)
                {
                    tmp->data = tmp->left->data;
                    tmp = tmp->left;
                }
                tmp->parent->left = NULL;
            }
            return tmp;
        }

        void _printTree(node_pointer root, std::string indent, bool last) 
        {
            if (root != NULL) {
                std::cout << indent;
                if (root == _rootN){
                    std::cout << "-----";
                    indent += "     ";
                }
                else if (last) {
                    std::cout<< "R----";
                    indent += "|    ";
                }
                else {
                    std::cout << "L----";
                    indent += "     ";
                }
                // std::string sColor = root->color?"BLACK":"RED";
                if (root->color == black)
                    std::cout << root->data << std::endl;
                else if (root->color == red)
                    std::cout << RED << root->data << END << std::endl;
                else
                    std::cout << YELLOW << root->data << END << std::endl;;
                _printTree(root->right, indent, true);
                _printTree(root->left, indent, false);
            }
        }
    };
}
