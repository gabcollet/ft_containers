/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:45 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/17 14:28:59 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <functional>
#include "iterator.hpp"
#include "rb_tree_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"

namespace ft
{
    template< typename Key, 
              typename T, 
              typename Compare = std::less<Key>,
              typename Allocator = std::allocator<ft::pair<const Key, T> > > 
    class map
    {
        //* =========================== Member types ==========================

    public:
        typedef Key                                         key_type;
        typedef T                                           mapped_type;
        typedef ft::pair<const Key, T>                      value_type;
        typedef size_t                                      size_type;
        typedef ptrdiff_t                                   difference_type;
        typedef Compare                                     key_compare;
        typedef Allocator                                   allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef ft::rb_tree_iterator<value_type>            iterator;
        typedef ft::rb_tree_iterator<value_type>            const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        
         //* ======================== Member functions ========================
        
        //empty constructor
        explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) :
            _tree() {}

        //range constructor
        template<class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {}

        //copy constructor
        map(const map& other) {}

        //destructor
        ~map() {}

        //assignement operator
        map& operator= (const map& x) {}
        
    private:
        rb_tree      _tree;
    };
}
