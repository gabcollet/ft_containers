/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:39:04 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/18 18:18:08 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "rb_tree_node.hpp"
#include <iostream>
#include <string>

namespace ft
{
    template < typename value_type >
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
            // We insert K using an ordinary BST insertion operation.
            // We color K red.
            // We check if the insertion violated the red-black tree properties. If it did, we fix it.
            
            if (!_rootN->data)
            {
                _rootN->data = val;
                return;
            }
            node_pointer newnode = new node;
            node_pointer tmp = _rootN;
            
            while (tmp->left != nullptr && tmp->right != nullptr)
            {
                if (val > tmp->data)
                    tmp = tmp->right;
                else if (val < tmp->data)
                    tmp = tmp->left;
            }
            newnode->data = val;
            newnode->parent = tmp;
            newnode->left = nullptr;
            newnode->right = nullptr;
            
            if (val > tmp->data)
                tmp->right = newnode;
            else if (val < tmp->data)
                tmp->left = newnode;
        }

        void prettyPrint() 
        {
            if (_rootN) {
                _printHelper(_rootN, "", true);
            }
        }

    private:
        node_pointer _rootN;
        
        void _printHelper(node_pointer root, std::string indent, bool last) 
        {
		// print the tree structure on the screen
            if (root != nullptr) {
                std::cout<<indent;
                if (last) {
                    std::cout<<"R----";
                    indent += "     ";
                }
                else {
                    std::cout<<"L----";
                    indent += "|    ";
                }
                std::string sColor = root->color?"BLACK":"RED";
                std::cout<<root->data<<"("<<sColor<<")"<<std::endl;
                _printHelper(root->left, indent, false);
                _printHelper(root->right, indent, true);
            }
		        // cout<<root->left->data<<endl;
        }
    };
}
