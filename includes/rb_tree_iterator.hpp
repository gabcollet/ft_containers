/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:49:46 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/06 19:31:07 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include <cstddef>
#include "rb_tree_node.hpp"

namespace ft
{
    template < typename T >
    class rb_tree_const_iterator;

    template < typename T >
    class rb_tree_iterator 
    {
    
    public: 
        typedef T                                   value_type;
        typedef rb_tree_node<value_type>            node;
        typedef rb_tree_node<value_type>*           node_pointer;
        typedef rb_tree_iterator<value_type>        iterator;
        typedef rb_tree_const_iterator<value_type>  const_iterator;
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef ptrdiff_t                           difference_type;
        typedef value_type*                         pointer;
        typedef value_type&                         reference;
        
        //Default constructor
        rb_tree_iterator() : _ptr_node() {}

        //Copy constructor
        rb_tree_iterator(node_pointer elem) : _ptr_node(elem) {}

        //Destructor
        ~rb_tree_iterator() {}

        //Assignment iterator
        rb_tree_iterator& operator=(const rb_tree_iterator& other)
        {
            _ptr_node = other._ptr_node;
            return *this;
        }

        reference operator*() const { return _ptr_node->data; }
        
        pointer operator->() const { return &(_ptr_node->data); }

        iterator& operator++()
        {
            increment();
            return *this;
        }
        
        iterator operator++(int) 
        { 
            iterator it = *this;
            ++(*this);
            return it;
        }
        
        iterator& operator--()
        {
            decrement();
            return *this;
        }
        
        iterator operator--(int) 
        {
            iterator it = *this;
            --(*this);
            return it;
        }

        bool operator== (const iterator& it) const
        { 
            return _ptr_node == it._ptr_node; 
        }
        
        bool operator== (const const_iterator& it) const
        { 
            return _ptr_node == it.base(); 
        }

        bool operator!= (const iterator& it) const 
        { 
            return _ptr_node != it._ptr_node; 
        }
        
        bool operator!= (const const_iterator& it) const 
        { 
            return _ptr_node != it.base(); 
        }

        node* base() {return _ptr_node;}
        
        const node* base() const {return _ptr_node;}
        
    private:
        node* _ptr_node;
        
        node* increment(){
            if (_ptr_node->right){
                _ptr_node = _ptr_node->right;
                while (_ptr_node->left)
                    _ptr_node = _ptr_node->left;
            }
            else{
                node* tmp = _ptr_node;
                _ptr_node = _ptr_node->parent;
                while (_ptr_node->right == tmp)
                {
                    tmp = _ptr_node;
                    _ptr_node = _ptr_node->parent;
                }
            }
            return _ptr_node;
        }

        node* decrement(){
            if (_ptr_node->left){
                _ptr_node = _ptr_node->left;
                while (_ptr_node->right)
                    _ptr_node = _ptr_node->right;
            }
            else{
                node* tmp = _ptr_node;
                _ptr_node = _ptr_node->parent;
                while (_ptr_node->left == tmp)
                {
                    tmp = _ptr_node;
                    _ptr_node = _ptr_node->parent;
                }
            }
            return _ptr_node;
        }
    };

    template < typename T >
    class rb_tree_const_iterator 
    {
    
    public: 
        typedef T                                   value_type;
        typedef rb_tree_node<value_type>            node;
        typedef rb_tree_node<value_type>*           node_pointer;
        typedef rb_tree_iterator<value_type>        iterator;
        typedef rb_tree_const_iterator<value_type>  const_iterator;
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef ptrdiff_t                           difference_type;
        typedef const value_type*                   pointer;
        typedef const value_type&                   reference;
        
        //Default constructor
        rb_tree_const_iterator() : _ptr_node() {}

        //Iterator constructor
        rb_tree_const_iterator(iterator it) : _ptr_node(it.base()) {}

        //Copy constructor
        rb_tree_const_iterator(node_pointer elem) : _ptr_node(elem) {}

        //Destructor
        ~rb_tree_const_iterator() {}

        //Assignment iterator
        rb_tree_const_iterator& operator=(const rb_tree_const_iterator& other)
        {
            _ptr_node = other._ptr_node;
            return *this;
        }

        reference operator*() const { return _ptr_node->data; }
        
        pointer operator->() const { return &(_ptr_node->data); }

        const_iterator& operator++()
        {
            increment();
            return *this;
        }
        
        const_iterator operator++(int)
        { 
            const_iterator it = *this;
            ++(*this);
            return it;
        }
        
        const_iterator& operator--()
        {
            decrement();
            return *this;
        }
        
        const_iterator operator--(int)
        { 
            const_iterator it = *this;
            --(*this);
            return it;
        }

        bool operator== (const iterator& it) const 
        { 
            return _ptr_node == it.base(); 
        }
        
        bool operator== (const const_iterator& it) const 
        { 
            return _ptr_node == it._ptr_node; 
        }

        bool operator!= (const iterator& it) const 
        { 
            return _ptr_node != it.base(); 
        }
        
        bool operator!= (const const_iterator& it) const 
        { 
            return _ptr_node != it._ptr_node; 
        }

        node* base() {return _ptr_node;}
        
        const node* base() const {return _ptr_node;}
        
    private:
        node* _ptr_node;
        
        node* increment(){
            if (_ptr_node->right){
                _ptr_node = _ptr_node->right;
                while (_ptr_node->left)
                    _ptr_node = _ptr_node->left;
            }
            else{
                node* tmp = _ptr_node;
                _ptr_node = _ptr_node->parent;
                while (_ptr_node->right == tmp)
                {
                    tmp = _ptr_node;
                    _ptr_node = _ptr_node->parent;
                }
            }
            return _ptr_node;
        }

        node* decrement(){
            if (_ptr_node->left){
                _ptr_node = _ptr_node->left;
                while (_ptr_node->right)
                    _ptr_node = _ptr_node->right;
            }
            else{
                node* tmp = _ptr_node;
                _ptr_node = _ptr_node->parent;
                while (_ptr_node->left == tmp)
                {
                    tmp = _ptr_node;
                    _ptr_node = _ptr_node->parent;
                }
            }
            return _ptr_node;
        }
    };
}
