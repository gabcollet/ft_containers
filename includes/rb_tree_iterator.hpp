/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:49:46 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/30 16:59:23 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "rb_tree_node.hpp"
#include <iterator>


//! valider ou creer une version const pour l'iterator
namespace ft
{
    template < typename value_type >
    class rb_tree_iterator 
    {
    
    public: 
        typedef rb_tree_node<value_type>            node;
        typedef rb_tree_node<value_type>*           node_pointer;
        typedef rb_tree_iterator<value_type>        iterator;
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

        reference operator*() { return _ptr_node->data; }
        
        pointer operator->() { return &(_ptr_node->data); }

        iterator& operator++()
        {
            increment();
            return *this;
        }
        
        iterator operator++(int) { return iterator(increment()); }
        
        iterator& operator--()
        {
            decrement();
            return *this;
        }
        
        iterator operator--(int) { return iterator(decrement()); }

        bool operator== (const iterator& it) { return _ptr_node == it._ptr_node; }

        bool operator!= (const iterator& it) { return _ptr_node != it._ptr_node; }

        node* base() {return _ptr_node;}
        
    private:
        node* _ptr_node;
        
        void increment(){
            if (_ptr_node->right){
                _ptr_node = _ptr_node->right;
                while (_ptr_node->left)
                    _ptr_node = _ptr_node->left;
            }
            else{
                node* tmp = _ptr_node;
                _ptr_node = _ptr_node->parent;
                if (_ptr_node->right == tmp)
                    _ptr_node = _ptr_node->parent;
            }
        }

        void decrement(){
            if (_ptr_node->left){
                _ptr_node = _ptr_node->left;
                while (_ptr_node->right)
                    _ptr_node = _ptr_node->right;
            }
            else{
                node* tmp = _ptr_node;
                _ptr_node = _ptr_node->parent;
                if (_ptr_node->left == tmp)
                    _ptr_node = _ptr_node->parent;
            }
        }
    };
}
