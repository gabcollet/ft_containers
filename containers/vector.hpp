/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:43 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/19 16:15:52 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <cstddef>
#include <iterator.hpp>

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		//* =========================== Member types ==========================

    public:
        typedef T   									value_type;
        typedef Alloc                                   allocator_type;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef typename allocator_type::pointer        pointer;
        typedef typename allocator_type::const_pointer  const_pointer;
        typedef typename ft::normal_iterator<pointer, vector> iterator;
        typedef typename ft::normal_iterator<const_pointer, vector>	const_iterator;
        typedef typename ft::reverse_iterator<pointer, vector>	reverse_iterator;
        typedef typename ft::reverse_iterator<const_pointer, vector> const_reverse_iterator;

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
            typedef typename iterator_traits<vector::iterator>::iterator_category category;
            _range_construct(x._start, x._end, category());
        }

        //destructor
        ~vector()
        {
            clear();
            if (_start != _end)
                _alloc.deallocate(_start, capacity());
        }

        //member overload
        vector& operator= (const vector& x)
        {
            if (&x == this)
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

        reverse_iterator rbegin() {return reverse_iterator(_end - 1);}

        const_reverse_iterator rbegin() const {return const_reverse_iterator(_end - 1);}

        iterator end() {return iterator(_end);}

        const_iterator end() const {return const_iterator(_end);}

        reverse_iterator rend() {return reverse_iterator(_start - 1);}

        const_reverse_iterator rend() const {return const_reverse_iterator(_start - 1);}

        //* ============================ Capacity =============================

        bool empty() const
        {
            if (size() == 0)
                return true;
            return false;
        }

        size_type size() const {return _end - _start;}

        size_type max_size() const {return _alloc.max_size();}

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
            _fill_construct(n, val);
        }

        void clear() {erase(begin(), end());}

        void push_back (const value_type& val)
        {
            if (_end == _capacity){
                size_type newCapacity;
                if (size() > 0)
                    newCapacity = size() * 2;
                else
                    newCapacity = 1;
                reserve(newCapacity);
            }
            _alloc.construct(_end, val);
            _end++;
        }

        iterator erase (iterator position)
        {
            if (position == end())
                return end();
            pointer ptr_first = position.base();
            _alloc.destroy(position.base());
            ++position;
            size_type size_right = _end - position.base();
            for (size_type i = 0; i < size_right; i++){
                _alloc.construct(ptr_first + i, *position.base());
                _alloc.destroy(position.base());
                ++position;
            }
            _end = ptr_first + size_right;
            return iterator(ptr_first);
        }

        iterator erase (iterator first, iterator last)
        {
//TODO faudrait que erase gere _capacity aussi
            pointer ptr_first = first.base();
            if (first != last){
                difference_type n = std::distance(first, last);
                for (; first != last; ++first) {
                    _alloc.destroy(first.base());
                }
                _alloc.deallocate(ptr_first, n);
            }
            else
                _alloc.deallocate(ptr_first, 1);
            size_type size_right = _end - last.base();
            for (size_type i = 0; i < size_right; i++){
                _alloc.construct(ptr_first + i, *last.base());
                _alloc.destroy(last.base());
                ++last;
            }
            _end = ptr_first + size_right;
            return iterator(ptr_first);
        }

        iterator insert (iterator position, const value_type& val)
        {
            //if (_end == _capacity){
            //                size_type newCapacity;
            //                if (size() > 0)
            //                    newCapacity = size() * 2;
            //                else
            //                    newCapacity = 1;
            //                reserve(newCapacity);
            //            }
            //! ca pourrais etre une method private

            //while sur un pointeur qui avance tout le contenue de 1
            //place l'element before position de depart du ptr
            //_end += 1;

        }

        void insert (iterator position, size_type n, const value_type& val)
        {

        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last)
        {

        }


    private:
        allocator_type      _alloc;
        pointer             _start;
        pointer             _end;
        pointer             _capacity;

        template < typename InputIterator >
        void _range_construct(InputIterator first, InputIterator last, std::input_iterator_tag)
        {
            for (; first != last; ++first)
                push_back(*first);
        }

        template < typename ForwardIterator >
        void _range_construct(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
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

        void _fill_construct(size_type n, const value_type& val = value_type())
        {
            _start = _alloc.allocate(n);
            _end = _start;
            _capacity = _start + n;
            for (size_type i = 0; i != n; i++){
                _alloc.construct(_end, val);
                _end++;
            }
        }
	};
}
