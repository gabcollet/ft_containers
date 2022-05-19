/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:39:04 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/19 15:53:43 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "rb_tree_node.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

#define RED "\033[31;1m"
#define END "\033[0m"

namespace ft
{
    template < typename compare, typename value_type >
    class rb_tree
    {
        
    public:
        typedef rb_tree_node<value_type>        node;
        typedef rb_tree_node<value_type>*       node_pointer;

        //Default constructor
        rb_tree() { _rootN = new node(); }

        //Parameterized constructor
        rb_tree(value_type elem) { _rootN = new node(elem); }

        void insert(value_type val)
        {
            if (!_rootN->data)
            {
                _rootN->data = val;
                _rootN->color = black;
                return;
            }
            node_pointer newnode = new node;
            node_pointer tmp = _rootN;
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
            newnode->data = val;
            newnode->parent = tmp;
            newnode->left = NULL;
            newnode->right = NULL;
            if (comp(val, tmp->data))
                tmp->left = newnode;
            else
                tmp->right = newnode;
            fixinsert(newnode);
        }

        void remove()
        {
            
        }

        void treePrint()
        {
            if (_rootN) {
                _printTree(_rootN, "", true);
                std::cout << std::endl;
            }
        }

    private:
        node_pointer _rootN;
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
                std::string sColor = root->color?"BLACK":"RED";
                if (sColor == "BLACK")
                    std::cout << root->data << std::endl;
                else
                    std::cout << RED << root->data << END << std::endl;
                _printTree(root->right, indent, true);
                _printTree(root->left, indent, false);
            }
        }
    };
}
