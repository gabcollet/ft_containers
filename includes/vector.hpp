/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:43 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/04 17:07:36 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <cstddef>
#include <algorithm>
#include <limits>
#include "iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		//* =========================== Member types ==========================

    public:
        typedef T   									    value_type;
        typedef Alloc                                       allocator_type;
        typedef size_t                                      size_type;
        typedef ptrdiff_t                                   difference_type;
        typedef value_type&                                 reference;
        typedef const value_type&                           const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef ft::normal_iterator<pointer, vector>        iterator;
        typedef ft::normal_iterator<const_pointer, vector>	const_iterator;
        typedef ft::reverse_iterator<iterator>      	    reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

        //* ========================= Member functions =========================
        
        //default constructor
        vector() : _alloc(), _start(), _end(), _capacity() {}

        //empty constructor
        explicit vector (const allocator_type& alloc) :
            _alloc(alloc), _start(), _end(), _capacity() {}

        //fill constructor
        explicit vector (size_type n, const value_type& val = value_type(),
                          const allocator_type& alloc = allocator_type()) :
            _alloc(alloc)
        {
            _fill_construct(n, val);
        }

        //range constructor
        template < typename InputIterator >
        vector (InputIterator first,
                typename enable_if<!is_integral<InputIterator>::value, InputIterator>::_type last,
                const allocator_type& alloc = allocator_type()) :
            _alloc(alloc), _start(), _end(), _capacity()
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            _range_construct(first, last, category());
        }

        //copy constructor
        vector (const vector& x) :
            _alloc(x._alloc), _start(), _end(), _capacity()
        {
            if (x.size() > 0)
            {
                typedef typename iterator_traits<vector::iterator>::iterator_category category;
                _range_construct(x._start, x._end, category());
            }
        }

        //destructor
        ~vector()
        {
            clear();
            _alloc.deallocate(_start, capacity());
        }

        //assignement operator
        vector& operator= (const vector& x)
        {
            if (&x == this || x.size() == 0)
                return *this;
            _alloc.deallocate(_start, capacity());
            assign(x.begin(), x.end());
            return *this;
        }

        allocator_type get_allocator() const {return _alloc;}

        //* ========================= Element access ==========================

        reference at (size_type n)
        {
            if (n >= size())
                throw std::out_of_range("at");
            return *(_start + n);
        }

        const_reference at (size_type n) const
        {
            if (n >= size())
                throw std::out_of_range("at");
            return *(_start + n);
        }

        reference front() {return reference(*_start);}

        const_reference front() const {return const_reference(*_start);}

        reference back() {return reference(*(_end - 1));}

        const_reference back() const {return reference(*(_end - 1));}

        reference operator[] (size_type n) {return *(_start + n);}

        const_reference  operator[] (size_type n) const {return *(_start + n);}

        value_type* data() {return pointer(_start);}

        const value_type* data() const {return pointer(_start);}

        //* ============================ Iterators ============================

        iterator begin() {return iterator(_start);}

        const_iterator begin() const {return const_iterator(_start);}

        reverse_iterator rbegin() {return reverse_iterator(end());}

        const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}

        iterator end() {return iterator(_end);}

        const_iterator end() const {return const_iterator(_end);}

        reverse_iterator rend() {return reverse_iterator(begin());}

        const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

        //* ============================ Capacity =============================

        bool empty() const {return (size() == 0) ? true : false;}

        size_type size() const {return _end - _start;}

        size_type max_size() const 
        {
            return std::min(_alloc.max_size(),
                    static_cast<size_type>(std::numeric_limits<difference_type>::max()));
        }

        size_type capacity() const {return _capacity - _start;}

        void reserve (size_type n)
        {
            if (n > max_size())
                throw std::length_error("vector::reserve");
            if (n > capacity()){
                pointer oldStart = _start;
                pointer oldEnd = _end;
                size_type oldCapacity = capacity();

                _start = _alloc.allocate(n);
                _end = _start;
                _capacity = _start + n;
                while (oldStart != oldEnd){
                    _alloc.construct(_end, *oldStart);
                    _alloc.destroy(oldStart);
                    _end++;
                    oldStart++;
                }
                _alloc.deallocate(oldStart - size(), oldCapacity);
            }
        }

        void resize (size_type n, value_type val = value_type())
        {
            if (n < size())
                assign(begin(), begin() + n);
            if (n > size())
                insert(end(), n - size(), val);
        }

        //* ============================ Modifier =============================
       
        template <class InputIterator>
        void assign (InputIterator first,
                     typename enable_if<!is_integral<InputIterator>::value, InputIterator>::_type last)
        {
            clear();
            typedef typename iterator_traits<vector::iterator>::iterator_category category;
            _range_construct(first, last, category());
        }

        void assign (size_type n, const value_type& val)
        {
            clear();
            _alloc.deallocate(_start, capacity());
            _fill_construct(n, val);
        }

        void clear() {erase(begin(), end());}

        void push_back (const value_type& val)
        {
            if (_end == _capacity)
                _newCapacity();           
            _alloc.construct(_end, val);
            _end++;
        }

        void pop_back() {erase(end() - 1);}

        iterator erase (iterator position)
        {
            if (position == end())
                return end();
            pointer ptr_first = position.base();
            _alloc.destroy(position.base());
            ++position;
            size_type size_right = _end - position.base();
            _move_right(ptr_first, size_right, position);
            _end = ptr_first + size_right;
            return iterator(ptr_first);
        }

        iterator erase (iterator first, iterator last)
        {
            pointer ptr_first = first.base();
            if (first != last){
                for (; first != last; ++first) {
                    _alloc.destroy(first.base());
                }
            }
            size_type size_right = _end - last.base();
            _move_right(ptr_first, size_right, last);
            _end = ptr_first + size_right;
            return iterator(ptr_first);
        }

        iterator insert (iterator position, const value_type& val)
        {
            difference_type dist = std::distance(position.base(), _end);           
            if (_end == _capacity)
                _newCapacity();
            pointer ptr_right = _end - dist;
            _move_right((ptr_right + 1), dist, (end() - dist));
            _alloc.construct(ptr_right, val); 
            _end += 1;
            return iterator(ptr_right);
        }

        void insert (iterator position, size_type n, const value_type& val)
        {
            difference_type dist = std::distance(position.base(), _end);
            if (size() + n > capacity())
                reserve(capacity() + n);
            pointer ptr_right = _end - dist;
            _move_right((ptr_right + n), dist, (end() - dist));
            for (size_type i = 0; i < n; i++){
                _alloc.construct(ptr_right + i, val);
            }
            _end += n;
        }

        template <typename InputIterator>
        void insert (iterator position, InputIterator first,
                     typename enable_if<!is_integral<InputIterator>::value, InputIterator>::_type last)
        {
            difference_type dist = std::distance(position.base(), _end);
            difference_type n = std::distance(first, last);
            if (size() + n > capacity())
                reserve(capacity() + n);
            pointer ptr_right = _end - dist;
            _move_right(ptr_right + n, dist, (end() - dist));
            _range_construct(ptr_right, first, last);
        }

        void swap (vector& x)
        {
            if (&x != this)
            {
                pointer tmp_s = x._start;
                pointer tmp_e = x._end;
                pointer tmp_c = x._capacity;
                
                x._start = _start;
                x._end = _end;
                x._capacity = _capacity;

                _start = tmp_s;
                _end = tmp_e;
                _capacity = tmp_c;
            }
        }

    private:
        allocator_type      _alloc;
        pointer             _start;
        pointer             _end;
        pointer             _capacity;

        //* ============================= Private =============================

        template < typename InputIterator >
        void _range_construct (InputIterator first, InputIterator last, std::input_iterator_tag)
        {
            for (; first != last; ++first)
                push_back(*first);
        }

        template < typename ForwardIterator >
        void _range_construct (ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
        {
            difference_type n = std::distance(first, last);
            _start = _alloc.allocate(n);
            _end = _start;
            _capacity = _start + n;
            for (; first != last; ++first){
                _alloc.construct(_end, *first);
                _end++;
            }
        }

        template < typename ForwardIterator >
        void _range_construct (pointer position, ForwardIterator first, ForwardIterator last)
        {
            for (; first != last; ++first, (void)++position){
                _alloc.construct(position, *first);
                _end++;
            }
        }

        void _fill_construct (size_type n, const value_type& val = value_type())
        {
            _start = _alloc.allocate(n);
            _end = _start;
            _capacity = _start + n;
            for (size_type i = 0; i != n; i++){
                _alloc.construct(_end, val);
                _end++;
            }
        }

        void _newCapacity()
        {
            size_type newCapacity;
            if (size() > 0)
                newCapacity = size() * 2;
            else
                newCapacity = 1;
            reserve(newCapacity);
        }

        void _move_right (pointer position, size_type dist, iterator content)
        {
            pointer tmp = _alloc.allocate(dist);
            for (size_type i = 0; i < dist; i++){
                _alloc.construct(tmp + i, *content.base());
                _alloc.destroy(content.base());
                ++content;
            }
            for (size_type i = 0; i < dist; i++){
                _alloc.construct(position + i, *(tmp + i));
                _alloc.destroy(tmp + i);
            }
            _alloc.deallocate(tmp, dist);
        }
	};

    //* ========================= Non-member function =========================

    template <typename T, typename Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < lhs.size(); i++){
            if (lhs[i] != rhs[i])
                return false;
        }
        return true;
    }

    template <typename T, typename Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T, typename Alloc>
    bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename T, typename Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template <typename T, typename Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    template <typename T, typename Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }
}
