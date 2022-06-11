/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:43 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/11 12:22:51 by gcollet          ###   ########.fr       */
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
            _clear_vector();
        }

        //assignment operator
        vector& operator= (const vector& x)
        {
            if (&x == this || x.size() == 0)
                return *this;
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
                if (oldStart != NULL)
                    _alloc.deallocate(oldStart - size(), oldCapacity);
            }
        }

        void resize (size_type n, value_type val = value_type())
        {
            const size_type len = size();
            if (n < len)
                erase(begin() + n, end());
            else if (n > len)
                insert(end(), n - len, val);
        }

        //* ============================ Modifier =============================
       
        template <class InputIterator>
        void assign (InputIterator first,
                     typename enable_if<!is_integral<InputIterator>::value, InputIterator>::_type last)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            _range_assign(first, last, category());
        }

        void assign (size_type n, const value_type& val)
        {
            _clear_vector();
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
            if (n <= 0)
                return;
            if (capacity() - size() < n) {
                size_type new_cap = (!empty()) ? get_newcap(size() + n) : capacity() + n;
                pointer new_start = _alloc.allocate(new_cap);
                pointer new_end = _range_construct(new_start, _start, position.base());
                new_end = _range_construct(new_end, new_end + n, val);
                new_end = _range_construct(new_end, position.base(), _end);
                _clear_vector();
                _start = new_start;
                _end = new_end;
                _capacity = _start + new_cap;
            } 
            else 
            {
                iterator cpy_end = _move_right(position, n);
                for (; position != cpy_end; ++position) {
                    if (position.base() < _end) {
                        *position = val;
                    } else
                        _alloc.construct(position.base(), val);
                }
                _end += n;
            }
        }

        template <typename InputIterator>
        void insert (iterator position, InputIterator first,
                     typename enable_if<!is_integral<InputIterator>::value, InputIterator>::_type last)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            _range_insert(position, first, last, category());
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
        
        template <typename Iter>
        pointer _range_construct(pointer dest, Iter start, Iter end) {

            for (; start != end; ++dest, (void)++start)
                _alloc.construct(dest, *start);
            return dest;
        }

        pointer _range_construct(pointer dest, const_pointer end, const_reference value) {
            for (; dest != end; ++dest) 
                _alloc.construct(dest, value);  
            return dest;
        }

        template < typename InputIterator >
        void _range_assign(InputIterator first, InputIterator last, std::input_iterator_tag)
        {
            clear();
            for (; first != last; ++first)
                push_back(*first);
        }

        template <typename ForwardIterator>
        void _range_assign(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
        {
            const size_type n = std::distance(first, last);
            if (n < size()) 
            {
                iterator it = std::copy(first, last, begin());
                erase(it, end());
            }
            else 
            {
                ForwardIterator it = first;
                std::advance(it, size());
                std::copy(first, it, begin());
                insert(end(), it, last);
            }
        }
        
        template < typename InputIterator >
        void _range_insert (iterator position, InputIterator first, InputIterator last, 
                            std::input_iterator_tag)
        {
            if (position == end()){
                for (; first != last; ++first)
                    push_back(*first);
            } 
            else if (first != last) 
            {
                vector tmp(first, last);
                insert(position, tmp.begin(), tmp.end());
            }
        }

        template < typename ForwardIterator >
        void _range_insert (iterator pos, ForwardIterator first, ForwardIterator last, 
                            std::forward_iterator_tag)
        {
            if (first == last)
                return;
            size_type n = std::distance(first, last);
            if (capacity() - size() < n) {
                size_type new_cap = (!empty()) ? get_newcap(size() + n) : capacity() + n;
                pointer new_start = _alloc.allocate(new_cap);
                pointer new_end = _range_construct(new_start, _start, pos.base());
                new_end = _range_construct(new_end, first, last);
                new_end = _range_construct(new_end, pos.base(), _end);
                _clear_vector();
                _start = new_start;
                _end = new_end;
                _capacity = _start + new_cap;
            } 
            else 
            {
                iterator cpy_end = _move_right(pos, n);
                for (; first != last; ++first, ++pos) {
                    if (pos < end()) {
                        *pos = *first;
                    } else
                        _alloc.construct(pos.base(), *first);
                }
                _end += n;
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

        iterator _move_right(iterator& pos, size_type& n) 
        {
            iterator cpy = end() - 1;
            iterator dest = cpy + n;
            if (_start != _end) 
            {
                if (_end == _capacity)
                    cpy = end();
                for (; dest != pos && cpy >= pos; --cpy, --dest) 
                {
                    if (dest < end())
                        *dest = *cpy;
                    else
                        _alloc.construct(dest.base(), *cpy);
                }
            }
            return ++dest;
        }

        void _clear_vector()
        {
            clear();
            if (_start != NULL)
                _alloc.deallocate(_start, capacity());
        }

        size_type get_newcap(const size_type& total_elems) 
        {
            size_type new_cap = capacity();

            if (new_cap >= max_size() / 2)
                return max_size();

            return std::max(total_elems, new_cap * 2);
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
