/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:49:46 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/17 15:55:03 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include "rb_tree_node.hpp"
#include <cstddef>
#include <iterator>
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
        }        

        // ==
        // !=
        // ++
        // --
        
    private:
        node* _ptr_node;

        void increment(){
            
        }
    };
}