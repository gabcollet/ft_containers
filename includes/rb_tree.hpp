/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:39:04 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/07 12:52:42 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "rb_tree_node.hpp"
#include "rb_tree_iterator.hpp"
#include "pair.hpp"

#include <iostream>
#include <limits>

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
        typedef compare                                         value_compare;
        typedef typename alloc::template rebind<node>::other    node_alloc;
        typedef rb_tree_iterator<value_type>                    iterator;
        typedef rb_tree_const_iterator<value_type>              const_iterator;
        typedef size_t                                          size_type;
        typedef ptrdiff_t                                       difference_type;

        //Default constructor
        rb_tree() : _rootN(), _endN(_rootN) 
        {
            _endN = construct_node();
        }

        //Parameterized constructor
        rb_tree(value_type val)
        {
            construct_root(val);
        }

        //Copy constructor
        rb_tree(const rb_tree& other) : _rootN(), _endN(_rootN)
        {
            const_iterator first = other.begin();
            const_iterator last = other.end();
            for (; first != last; ++first)
                insert(*first);
        }

        rb_tree& operator=(const rb_tree& other)
        {
            if (this == &other) {
                return *this;
            }
            rb_tree tmp(other);
            swap(tmp);
            return *this;
        }

        pair<iterator, bool> insert(const value_type& val)
        {
            if (!_rootN)
            {
                construct_root(val);
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
                construct_root(val);
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

        void deleteNode(iterator first, iterator last)
        {
            while (first != last){
                first = deleteNode(first);
            }
        }
        
        iterator deleteNode(iterator first)
        {
            iterator ret(first);
            ++ret;
            deleteNode(first.base()->data);
            return ret;
        }

        template<typename Key>
        bool deleteNode(const Key& val)
        {
            pair<node_pointer,bool> p = find_node(_rootN, val);
            if (!p.second)
                return false;
            node_pointer node = p.first;
            //case with two child
            if (node->left && node->right)
            {
                exchange_node(node, minValueNode(node->left));
                if (node->left){
                    node_pointer tmp = copyBranch(node, LEFT);
                    fixdelete(tmp);
                }
                fixdelete(node);
            }
            //case with one child
            else if (node->left || node->right)
            {
                node_pointer tmp;
                if (node->left)
                    tmp = copyBranch(node, LEFT);
                else
                    tmp = copyBranch(node, RIGHT);
                fixdelete(tmp);
            }
            else
            //if there is a sister fix for rbtree
            // if ((node == node->parent->right && node->parent->left) ||
            //     (node == node->parent->left && node->parent->right))
                fixdelete(node);
            remove_node(node);
            return true;
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
            node_pointer node = _endN;
            while (node && node->left){
                node = node->left;
            }
            return iterator(node);
        }

        const_iterator begin() const
        {
            node_pointer node = _endN;
            while (node && node->left){
                node = node->left;
            }
            return const_iterator(node);
        }

        template <typename Key>
        iterator find(const Key& k)
        {
            pair<node_pointer,bool> p = find_node(_rootN, k);
            if (!p.second)
                return end();
            return iterator(p.first);
        }
        
        template <typename Key>
        const_iterator find(const Key& k) const
        {
            pair<node_pointer,bool> p = find_node(_rootN, k);
            if (!p.second)
                return end();
            return const_iterator(p.first);
        }

        void swap(rb_tree& x)
        {
            std::swap(_rootN, x._rootN);
            std::swap(_endN, x._endN);
            std::swap(_node_alloc, x._node_alloc);
            std::swap(_alloc, x._alloc);
            std::swap(_comp, x._comp);
        }

        template <typename Key>
        bool count(const Key& k) const
        {
            return find_node(_rootN, k).second;
        }

        template <typename Key>
        iterator lower_bound (const Key& k)
        {
            return iterator(lbound(k));
        }
        
        template <typename Key>
        const_iterator lower_bound (const Key& k) const
        {
            return const_iterator(lbound(k));
        }
        
        template <typename Key>
        iterator upper_bound (const Key& k)
        {
            return iterator(ubound(k));
        }
        
        template <typename Key>
        const_iterator upper_bound (const Key& k) const
        {
            return const_iterator(ubound(k));
        }
        
        size_type max_size() const 
        {
            return std::min(_node_alloc.max_size(),
                            static_cast<size_type>(std::numeric_limits<difference_type>::max()));
        }

    private:
        node_pointer    _rootN;
        node_pointer    _endN;
        node_alloc      _node_alloc;
        alloc           _alloc;
        compare         _comp;

        void construct_root(value_type val)
        {
            _rootN = construct_node(val, NULL, black);
            if (!_endN)
                _endN = construct_node();
            _rootN->parent = _endN;
            _endN->left = _rootN;
        }

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

        void remove_node(node_pointer oldN)
        {
            //case with no child
            if (oldN->left == NULL && oldN->right == NULL)
            {
                if (oldN == _rootN){
                    _rootN = NULL;
                    _node_alloc.deallocate(_endN, 1);
                    _endN = NULL;
                }
                else if (oldN->parent && oldN->parent->left == oldN)
                    oldN->parent->left = NULL; 
                else if (oldN->parent && oldN->parent->right == oldN)
                    oldN->parent->right = NULL;
            }
            //case with one child
            else if ( oldN->parent->left == oldN && 
                oldN->left == NULL && oldN->right == NULL)
                oldN->parent->left = NULL;
                
            _alloc.destroy(&oldN->data);
            _node_alloc.deallocate(oldN, 1);
        }

        void exchange_node(node_pointer a, node_pointer b)
        {
            node tmp = *a;
            a->color = b->color;
            b->color = tmp.color;
            if (a == _rootN)
                _rootN = b;
            exchange_parent(a, b);
            exchange_child(a, b, tmp, LEFT);
            exchange_child(a, b, tmp, RIGHT);
            b->parent = tmp.parent;
        }
        
        void exchange_parent(node_pointer a, node_pointer b)
        {
            //change parent child
            if (a->parent->right == a)
                a->parent->right = b;
            else
                a->parent->left = b;
            if (b->parent == a)
                a->parent = b;
            else
                a->parent = b->parent;
            if (b->parent != a)
            {
                if (b->parent->right == b)
                    b->parent->right = a;
                else
                    b->parent->left = a;
            }
        }

        void exchange_child(node_pointer a, node_pointer b, node tmp, bool side)
        {
            //change left child
            if (side == LEFT)
            {
                a->left = b->left;
                if (a->left)
                    a->left->parent = a;
                if (tmp.left != b)
                    b->left = tmp.left;
                else
                    b->left = a;
                if (b->left)
                    b->left->parent = b;
            }
            //change right child
            if (side == RIGHT)
            {    
                a->right = b->right;
                if (a->right)
                    a->right->parent = a;
                if (tmp.right != b)
                    b->right = tmp.right;
                else
                    b->right = a;
                if (b->right)
                    b->right->parent = b;
                b->parent = tmp.parent;
            }
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
            _endN->left = _rootN;
        }

        void fixdelete(node_pointer node)
        {
            if ((node == node->parent->right && node->parent->left == NULL) ||
                (node == node->parent->left && node->parent->right == NULL))
                return;
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
                        if (sister->right && sister->left &&
                            sister->right->color == black) { //case 3.3
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
                        if (sister->left && sister->right &&
                            sister->left->color == black) { //case 3.3
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
                if (node.base() == _endN)
                    --node;
                iterator it(node);
                ++it;
                if (value_comp()(it.base()->data, val))
                    return find_parent(_rootN, val);
                return ft::make_pair(node.base(), true);
            } 
            return find_parent(_rootN, val);
        }

        template <typename Key>
        pair<node_pointer, bool> find_node(node_pointer node, const Key& val) const
        {
            if (!_rootN)
                return ft::make_pair(_endN, false);
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
                        return ft::make_pair(_endN, false);
                }
            }
        }

        template <typename Key>
        node_pointer lbound(const Key& val) const
        {
            if (!_rootN)
                return _endN;
            node_pointer tmp = _rootN;
            node_pointer pos = _endN;
            while (tmp != NULL)
            {
                if (!value_comp()(tmp->data, val))
                {
                    pos = tmp; 
                    tmp = tmp->left;
                }
                else
                    tmp = tmp->right;
            }
            return pos;
        }
        
        template <typename Key>
        node_pointer ubound(const Key& val) const
        {
            if (!_rootN)
                return _endN;
            node_pointer tmp = _rootN;
            node_pointer pos = _endN;
            while (tmp != NULL)
            {
                if (value_comp()(val, tmp->data))
                {
                    pos = tmp; 
                    tmp = tmp->left;
                }
                else
                    tmp = tmp->right;
            }
            return pos;
        }

        void right_rotate(node_pointer a)
        {
            node_pointer b = a->left;
            a->left = b->right;
            if (b->right)
                b->right->parent = a;
            b->parent = a->parent;
            if (a->parent == _endN)
            {
                _rootN = b;
                _endN->left = b;
            }
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
            {
                _rootN = b;
                _endN->left = b;
            }
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
            node_pointer child;
            if (side == RIGHT){
                child = node->right;
                node->right = NULL;
            }
            else{
                child = node->left;
                node->left = NULL;
            }
            if (_rootN == node)
                _rootN = child; 
           
            // fonction pour transferer les couleurs
            //! le child right est pas sence avoir de child left
            node_pointer tmp = child;
            tmp->color = tmp->parent->color;
            while (tmp->left || tmp->right)
            {
                if (tmp->left)
                    tmp = tmp->left;
                else if (tmp->right)
                    tmp = tmp->right;
                tmp->color = tmp->parent->color;
            }
            // child->color = black;
            
            child->parent = node->parent;         
            if (node->parent->left == node)
                node->parent->left = child;
            else
                node->parent->right = child;
            // node->parent = NULL;
            return child;
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
