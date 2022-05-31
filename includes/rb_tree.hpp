/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:39:04 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/31 15:50:13 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "rb_tree_node.hpp"
#include "rb_tree_iterator.hpp"
#include "pair.hpp"
#include <iostream>
#include <functional>
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
        typedef rb_tree_iterator<value_type>                    iterator;
        typedef rb_tree_const_iterator<value_type>              const_iterator;

        //Default constructor
        rb_tree() : _rootN(), _endN(_rootN) {}

        //Parameterized constructor
        rb_tree(value_type val)
        {
            _rootN = construct_node(val, NULL, black);
            _endN = construct_node();
            _rootN->parent = _endN;
            _endN->left = _rootN;
        }

        pair<iterator, bool> insert(const value_type& val)
        {
            if (!_rootN)
            {
                *this = rb_tree(val);
                return ft::make_pair(_rootN, true);
            }
            pair<node_pointer,bool> p = find_parent(_rootN, val);
            if (!p.second)
                return p;
            node_pointer tmp = p.first;  
            node_pointer newnode = construct_node(val, tmp, red);
            if (value_comp()(val, tmp->data))
                tmp->left = newnode;
            else
                tmp->right = newnode;
            fixinsert(newnode);
            return ft::make_pair(newnode, true);
        }
        
        iterator insert(iterator pos, const value_type& val)
        {
            if (!_rootN)
            {
                *this = rb_tree(val);
                return iterator(_rootN);
            }
            pair<node_pointer,bool> p = find_parent(pos, val);
            if (!p.second)
                return iterator(p.first);
            node_pointer tmp = p.first;
            node_pointer newnode = construct_node(val, tmp, red);
            if (value_comp()(val, tmp->data))
            {
                if (tmp->left)
                {
                    tmp->left->parent = newnode;
                    newnode->left = tmp->left;
                }
                tmp->left = newnode;
            }
            else
            {
                if (tmp->right)
                {
                    tmp->right->parent = newnode;
                    newnode->right = tmp->right;
                }
                tmp->right = newnode;
            }
            fixinsert(newnode);
            return iterator(newnode);
        }

        void deleteNode(value_type val)
        {
            pair<node_pointer,bool> p = find_node(_rootN, val);
            if (!p.second)
                return;
            node_pointer node = p.first;
            node_pointer tmp = node;
            //case with two child
            if (node->left && node->right)
            {
                tmp = minValueNode(node->left);
                node->data = tmp->data;
                if (tmp->left)
                    tmp = copyBranch(tmp, LEFT);
            }
            //case with one child
            else if (node->left || node->right)
            {    
                if (node->left)
                    tmp = copyBranch(tmp, LEFT);
                else
                    tmp = copyBranch(tmp, RIGHT);
            }
            //if there is a sister fix for rbtree
            if ((tmp == tmp->parent->right && tmp->parent->left) ||
                (tmp == tmp->parent->left && tmp->parent->right))
                fixdelete(tmp);
            remove_node(tmp, node);
        }

        void treePrint()
        {
            if (_rootN) 
            {
                _printTree(_rootN, "", true);
                std::cout << std::endl;
            }
        }

        compare& value_comp()
        {
            return _comp;
        }
        
        const compare& value_comp() const
        {
            return _comp;
        }

        iterator end() {return iterator(_endN);}
        
        const_iterator end() const {return const_iterator(_endN);}

        iterator begin()
        {
            node_pointer node = _rootN;
            while (node->left){
                node = node->left;
            }
            return iterator(node);
        }

        const_iterator begin() const
        {
            node_pointer node = _rootN;
            while (node && node->left){
                node = node->left;
            }
            return const_iterator(node);
        }

        template <typename Key>
        iterator find (const Key& k)
        {
            pair<node_pointer,bool> p = find_node(_rootN, k);
            if (!p.second)
                return end();
            return iterator(p.first);
        }
        
        template <typename Key>
        const_iterator find (const Key& k) const
        {
            pair<node_pointer,bool> p = find_node(_rootN, k);
            if (!p.second)
                return end();
            return const_iterator(p.first);
        }

    private:
        node_pointer    _rootN;
        node_pointer    _endN;
        node_alloc      _node_alloc;
        alloc           _alloc;
        compare         _comp;

        node_pointer construct_node(value_type val, node_pointer parent, Color c)
        {
            node_pointer newnode = _node_alloc.allocate(1);
            _alloc.construct(&newnode->data, val);
            newnode->parent = parent;
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->color = c;
            return newnode;
        }

        node_pointer construct_node()
        {
            node_pointer newnode = _node_alloc.allocate(1);
            newnode->parent = NULL;
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->color = black;
            return newnode;
        }

        void remove_node(node_pointer tmp, node_pointer node)
        {
            //case with no child
            if (tmp->left == NULL && tmp->right == NULL)
            {
                if (tmp->parent->left == tmp)
                        tmp->parent->left = NULL; 
                else if (tmp->parent->right == tmp)
                    tmp->parent->right = NULL;
            }
            //case with one child
            if (tmp->parent->left == tmp && 
                tmp->left == NULL && tmp->right == NULL)
                tmp->parent->left = NULL;
            //case with two child
            if (tmp->parent != node)
                tmp->parent->right = NULL;
                
            _alloc.destroy(&tmp->data);
            _node_alloc.deallocate(tmp, 1);
        }

        void fixinsert(node_pointer newnode)
        {   
            node_pointer uncle;
            
            while (newnode->parent->color == red){
                if (newnode->parent == newnode->parent->parent->right){
                    uncle = newnode->parent->parent->left;
                    if (uncle && uncle->color == red){ //case 3.1
                        uncle->color = black;
                        newnode->parent->color = black;
                        newnode->parent->parent->color = red;
                        newnode = newnode->parent->parent;
                    }
                    else {
                        if (newnode == newnode->parent->left){ //case 3.3.1
                            newnode = newnode->parent;
                            right_rotate(newnode);
                        }
                        newnode->parent->color = black; //case 3.3.2
                        newnode->parent->parent->color = red;
                        left_rotate(newnode->parent->parent);
                    }
                }
                else {
                    uncle = newnode->parent->parent->right;
                    if (uncle && uncle->color == red){ //case 3.1
                        uncle->color = black;
                        newnode->parent->color = black;
                        newnode->parent->parent->color = red;
                        newnode = newnode->parent->parent;
                    }
                    else {
                        if (newnode == newnode->parent->right){ //case 3.3.1
                            newnode = newnode->parent;
                            left_rotate(newnode);
                        }
                        newnode->parent->color = black; //case 3.3.2
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
            //https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
            while (node != _rootN && node->color == black){
                //if node is left child
                if (node == node->parent->left){
                    node_pointer sister = node->parent->right;
                    if (sister->color == red){ //case 3.1
                        sister->color = black;
                        node->parent->color = red;
                        left_rotate(node->parent);
                        if (node->parent->right)
                            sister = node->parent->right;
                        else
                            break;
                    }
                    if ((sister->left && sister->right &&
                        sister->left->color == black &&
                        sister->right->color == black) ||
                        (sister->right == NULL && sister->left == NULL)){ //case 3.2
                        sister->color = red;
                        node = node->parent;
                    }
                    else {
                        if (sister->right && sister->right->color == black) { //case 3.3
                            sister->left->color = black;
                            right_rotate(sister);
                            sister->color = red;
                            sister = node->parent->right;
                        }
                        sister->color = node->parent->color; //case 3.4
                        node->parent->color = black;
                        if (sister->right){
                            sister->right->color = black;
                            left_rotate(node->parent);
                        }
                        node = _rootN;
                    }
                }
                //if node is right child
                else if (node == node->parent->right){
                    node_pointer sister = node->parent->left;
                    if (sister->color == red){ //case 3.1
                        sister->color = black;
                        node->parent->color = red;
                        right_rotate(node->parent);
                        if (node->parent->left)
                            sister = node->parent->left;
                        else
                            break;
                    }
                    if ((sister->right && sister->left &&
                        sister->right->color == black &&
                        sister->left->color == black) ||
                        (sister->right == NULL && sister->left == NULL)){ //case 3.2
                        sister->color = red;
                        node = node->parent;
                    }
                    else {
                        if (sister->left && sister->left->color == black) { //case 3.3
                            sister->right->color = black;
                            left_rotate(sister);
                            sister->color = red;
                            sister = node->parent->left;
                        }
                        sister->color = node->parent->color; //case 3.4
                        node->parent->color = black;
                        if (sister->left){
                            sister->left->color = black;
                            right_rotate(node->parent);
                        }
                        node = _rootN;
                    }
                }
                else 
                    return;
            }
            node->color = black;
        }

        template <typename Key>
        pair<node_pointer, bool> find_parent(node_pointer node, const Key& val) const
        {
            while (true)
            {
                if (value_comp()(node->data, val))
                {
                    if (node->right == NULL)
                        break;
                    node = node->right;
                }
                else if (value_comp()(val, node->data))
                {
                    if (node->left == NULL)
                        break;
                    node = node->left;
                }
                else
                    return ft::make_pair(node, false);
            }
            return ft::make_pair(node, true);
        }

        template <typename Key>
        pair<node_pointer, bool> find_parent(iterator node, const Key& val) const
        {
            if (value_comp()(node.base()->data, val))
            {
                if (node.base()->right && value_comp()(node.base()->right->data, val))
                    return find_parent(_rootN, val);
                return ft::make_pair(node.base(), true);
            } 
            return find_parent(_rootN, val);
        }

        template <typename Key>
        pair<node_pointer, bool> find_node(node_pointer node, const Key& val) const
        {
            while (true)
            {
                if (node->right && value_comp()(node->data, val))
                    node = node->right;
                else if (node->left && value_comp()(val, node->data))
                    node = node->left;
                else{
                    if (node->data == val)
                        return ft::make_pair(node, true);
                    else
                        break;
                }
            }
            return ft::make_pair(_endN, false);
        }

        void right_rotate(node_pointer a)
        {
            node_pointer b = a->left;
            a->left = b->right;
            if (b->right)
                b->right->parent = a;
            b->parent = a->parent;
            if (a->parent == _endN)
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
            if (a->parent == _endN)
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
    
    //overload == for key compare
    template <typename U, typename V>
    bool operator== (const pair<U,V>& lhs, const U& rhs)
    {
        return lhs.first == rhs;
    }
    
    template <typename U, typename V>
    bool operator== (const pair<U,V>& lhs, U& rhs)
    {
        return lhs.first == rhs;
    }
}
