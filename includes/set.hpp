/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:22:20 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/07 16:24:06 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "rb_tree_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"

namespace ft 
{
    
    template< class Key,
              class Compare = std::less<Key>,
              class Allocator = std::allocator<Key> > 
    class set
    {
        //* =========================== Member types ==========================

    public:
        typedef Key                                         key_type;
        typedef Key                                         value_type;
        typedef size_t                                      size_type;
        typedef ptrdiff_t                                   difference_type;
        typedef Compare                                     key_compare;
        typedef Compare                                     value_compare;
        typedef Allocator                                   allocator_type;
        typedef value_type&                                 reference;
        typedef const value_type                            const_reference;
        typedef typename Allocator::pointer                 pointer;
        typedef typename Allocator::const_pointer           const_pointer;
        typedef ft::rb_tree_const_iterator<value_type>      iterator;
        typedef ft::rb_tree_const_iterator<value_type>      const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        
        //* ========================= Member functions ==========================
        
        //empty constructor
        explicit set (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type()) :
            _tree(), _comp(comp), _alloc(alloc) {}
       
        //range constructor
        template <class InputIterator>
        set (InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type()) :
            _tree(), _comp(comp), _alloc(alloc)
        {
            insert(first, last);
        }

        //copy constructor
        set (const set& x) :
            _tree(x._tree), _comp(x._comp), _alloc(x._alloc) {}

        //destructor
        ~set() {}

        //assignment operator
        set& operator= (const set& x)
        {
            _tree = x._tree;
            return *this;
        }

        allocator_type get_allocator() const {return _alloc;}

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

        size_type size() const {return _tree.size();}

        size_type max_size() const 
        {
            return _tree.max_size();
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

        size_type erase(const value_type& k)
        {
            return _tree.deleteNode(k);
        }

        void erase(iterator first, iterator last)
        {
            return _tree.deleteNode(first, last);
        }

        void swap(set& x) {return _tree.swap(x._tree);}

        //* ============================= Lookup ==============================

        size_type count(const value_type& k) const
        {
            return _tree.count(k);
        }

        iterator find(const value_type& k) 
        {
            return _tree.find(k);
        }

        const_iterator find(const value_type& k) const
        {
            return _tree.find(k);
        }

        pair<iterator,iterator> equal_range(const value_type& k)
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        } 
        
        pair<const_iterator,const_iterator> equal_range(const value_type& k) const
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        iterator lower_bound (const value_type& k)
        {
            return _tree.lower_bound(k);
        }
        
        const_iterator lower_bound (const value_type& k) const
        {
            return _tree.lower_bound(k);
        }

        iterator upper_bound (const value_type& k)
        {
            return _tree.upper_bound(k);
        }
        
        const_iterator upper_bound (const value_type& k) const
        {
            return _tree.upper_bound(k);
        }

        //* ============================ Observer =============================
        
        key_compare key_comp() const {return _comp;}

        value_compare value_comp() const {return _tree.value_comp();}

    private:
        rb_tree<key_compare, value_type>    _tree;
        key_compare                         _comp;
        allocator_type                      _alloc;
    };
    
    template< class Key, class Compare, class Alloc >
    bool operator==(const ft::set<Key,Compare,Alloc>& lhs,
                    const ft::set<Key,Compare,Alloc>& rhs)
    {
        return lhs.size() == rhs.size() && 
               std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
	
    template< class Key, class Compare, class Alloc >
    bool operator!=(const ft::set<Key,Compare,Alloc>& lhs,
                    const ft::set<Key,Compare,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template< class Key, class Compare, class Alloc >
    bool operator<(const ft::set<Key,Compare,Alloc>& lhs,
                   const ft::set<Key,Compare,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template< class Key, class Compare, class Alloc >
    bool operator<=(const ft::set<Key,Compare,Alloc>& lhs,
                    const ft::set<Key,Compare,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template< class Key, class Compare, class Alloc >
    bool operator>(const ft::set<Key,Compare,Alloc>& lhs,
                   const ft::set<Key,Compare,Alloc>& rhs)
    {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    template< class Key, class Compare, class Alloc >
    bool operator>=(const ft::set<Key,Compare,Alloc>& lhs,
                    const ft::set<Key,Compare,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

    template< class Key, class Compare, class Alloc >
    void swap(ft::set<Key,Compare,Alloc>& lhs,
              ft::set<Key,Compare,Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
}
