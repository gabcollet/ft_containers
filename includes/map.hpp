/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:45 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/02 15:12:05 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <functional>
#include <iterator>
#include <algorithm>
#include <stdexcept>
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
        typedef ft::rb_tree_const_iterator<value_type>      const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        
        //* ========================= Member classes ==========================
        
        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
        
        public:
            typedef bool        result_type;
            typedef value_type  first_argument_type;
            typedef value_type  second_argument_type;

            value_compare(Compare c) : _comp(c) {}

            bool operator()(const value_type& lhs, const value_type& rhs) const
            {
                return _comp(lhs.first, rhs.first);
            }

        protected:
            Compare _comp;
        };
        
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
            _tree.insert(first, last);
        }

        //copy constructor
        map(const map& other) : 
            _tree(other._tree), _comp(other._comp), _alloc(other._alloc) {}

        //destructor
        ~map() {}

        //assignement operator
        map& operator= (const map& x) 
        {
            _tree = x._tree;
            return *this;
        }

        allocator_type get_allocator() const {return _alloc;}
        
        //* ========================== Element access =========================

        mapped_type& at (const key_type& k)
        {
            iterator it = _tree.find(k);
            if (it == _tree.end())
                throw std::out_of_range("at");
            return it.base()->data.second;
        }

        const mapped_type& at (const key_type& k) const
        {
            const_iterator it = _tree.find(k);
            if (it == _tree.end())
                throw std::out_of_range("at");
            return it.base()->data.second;
        }
        
        mapped_type& operator[] (const key_type& k)
        {
            return insert(ft::make_pair(k, mapped_type())).first->second;
        }
        
        //* ============================ Iterators ============================

        iterator begin() {return _tree.begin();}

        const_iterator begin() const {return _tree.begin();}

        reverse_iterator rbegin() {return reverse_iterator(end());}
        
        const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}

        iterator end() {return _tree.end();}

        const_iterator end() const {return _tree.end();}

        reverse_iterator rend() {return reverse_iterator(begin());}
        
        const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
        
        //* ============================ Capacity =============================

        bool empty() const {return (begin() == end()) ? true : false;}

        size_type size() const {return std::distance(begin(), end());}

        size_type max_size() const 
        {
            return std::min(_alloc.max_size(),
                            static_cast<size_type>(std::numeric_limits<difference_type>::max()));
        }
        
        //* ============================ Modifiers ============================
        
        void clear() {erase(begin(), end());}
        
        pair<iterator, bool> insert(const value_type& val)
        {
            return _tree.insert(val);
        }

        iterator insert(iterator hint, const value_type& val)
        {
            return _tree.insert(hint, val);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                _tree.insert(*first);
        }

        void erase(iterator position) 
        {
            _tree.deleteNode(position.base()->data);
            return; 
        }

        size_type erase(const key_type& k)
        {
            return _tree.deleteNode(k);
        }

        void erase(iterator first, iterator last)
        {
            return _tree.deleteNode(first, last);
        }

        void swap(map& x) {return _tree.swap(x._tree);}

        //* ============================= Lookup ==============================

        size_type count(const key_type& k) const
        {
            return _tree.count(k);
        }

        iterator find(const key_type& k) 
        {
            return _tree.find(k);
        }

        const_iterator find(const key_type& k) const
        {
            return _tree.find(k);
        }

        pair<iterator,iterator> equal_range(const key_type& k)
        {
            return make_pair(lower_bound(k), upper_bound(k));
        } 
        
        pair<const_iterator,const_iterator> equal_range(const key_type& k) const
        {
            return make_pair(lower_bound(k), upper_bound(k));
        }
        
        iterator lower_bound (const key_type& k)
        {
            return _tree.lower_bound(k);
        }
        
        const_iterator lower_bound (const key_type& k) const
        {
            return _tree.lower_bound(k);
        }

        iterator upper_bound (const key_type& k)
        {
            return _tree.upper_bound(k);
        }
        
        const_iterator upper_bound (const key_type& k) const
        {
            return _tree.upper_bound(k);
        }
        
        //* ============================= Lookup ==============================

        key_compare key_comp() const {return _comp;}

        value_compare value_comp() const {return value_compare();}
        
    private:
        typedef map_value_compare<key_type, value_type, key_compare> _map_compare;
        
        rb_tree<_map_compare, value_type>   _tree;
        key_compare                         _comp;
        allocator_type                      _alloc;
    };
    template< class Key, class T, class Compare, class Alloc >
    bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return lhs.size() == rhs.size() && 
               std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
	
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs,
                   const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs,
                   const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

    template< class Key, class T, class Compare, class Alloc >
    void swap(ft::map<Key,T,Compare,Alloc>& lhs,
              ft::map<Key,T,Compare,Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
}
