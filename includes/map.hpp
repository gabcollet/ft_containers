/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:45 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/30 15:08:00 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <functional>
#include <iterator>
#include <algorithm>
#include <sys/_types/_key_t.h>
#include "iterator.hpp"
#include "rb_tree_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"

namespace ft
{

    template<typename Key, typename T, typename Compare>
    class map_value_compare
    {
    
    public:
        map_value_compare() : _comp() {}
        
        map_value_compare(Compare c) : _comp(c) {}
        
        const Compare& key_comp() const { return _comp; }

        bool operator() (const T& x, const T& y) const
        {
            return _comp(x.first, y.first);
        }

        bool operator() (const T& x, const Key& y) const
        {
            return _comp(x.first, y);    
        }

        bool operator() (const Key& x, const T& y) const
        {
            return _comp(x, y.first);
        }

        void swap (map_value_compare& y)
        {
            std::swap(_comp, y._comp);
        }

    private:
        Compare _comp;
    };
    
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
        typedef ft::pair<const Key, mapped_type>            value_type;
        typedef size_t                                      size_type;
        typedef ptrdiff_t                                   difference_type;
        typedef Compare                                     key_compare;
        typedef Allocator                                   allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef ft::rb_tree_iterator<value_type>            iterator;
        typedef ft::rb_tree_iterator<const value_type>      const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        
        //* ======================== Member functions =========================
        
        //empty constructor
        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type()) :
            _tree(), _comp(comp), _alloc(alloc) {}

        //range constructor
        template<class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
            _tree(), _comp(comp), _alloc(alloc)
        {
            for (; first != last; ++first)
                _tree.insert(*first);
        }

        /* //copy constructor
        map(const map& other) {}

        //destructor
        ~map() {}

        //assignement operator
        map& operator= (const map& x) {} */
        
        //* ========================== Element access =========================

        mapped_type& operator[] (const key_type& k)
        {
            return insert(ft::make_pair(k, mapped_type())).first->second;
        }

        /* mapped_type& at (const key_type& k)
        {
            //see also operator []
            //see also find
        }

        const mapped_type& at (const key_type& k)
        {
            
        } */
        
        //* ============================ Iterators ============================

        iterator end() {return _tree.end();}

        const_iterator end() const {return _tree.end();}
        
        //* ============================ Modifiers ============================
        
        pair<iterator, bool> insert (const value_type& val)
        {
            return _tree.insert(val);
        }

        iterator insert (iterator hint, const value_type& val)
        {
            return _tree.insert(hint, val);
        }

        /* template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            
        } */
        
    private:
        typedef map_value_compare<key_type, value_type, key_compare> _map_compare;
        
        rb_tree<_map_compare, value_type>   _tree;
        key_compare                         _comp;
        allocator_type                      _alloc;
    };
}
