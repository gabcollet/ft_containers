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
        typedef typename ft::normal_iterator<pointer, vector>	iterator;
        typedef typename ft::normal_iterator<const_pointer, vector>	const_iterator;
        /* typedef typename ft::reverse_iterator<iterator>	reverse_iterator; //a coder
        typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator; */

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
            _start = _alloc.allocate(n);
            _end = _start;
            _capacity = _start + n;
            for (size_type i = 0; i != n; i++){
                _alloc.construct(_end, val);
                _end++;
            }
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
            _alloc.deallocate(_start, capacity());
        }

        //member overload
//        vector& operator= (const vector& x) { return }

        allocator_type get_allocator() const {return _alloc;}

        //* ========================= Element access ==========================

        reference operator[] (size_type n) {return *(_start + n);}

        const_reference  operator[] (size_type n) const {return *(_start + n);}



        //* ============================ Iterators ============================

        iterator begin() {return iterator(_start);}

        const_iterator begin() const {return const_iterator(_start);}

        iterator end() {return iterator(_end);}

        const_iterator end() const {return const_iterator(_end);}

        //* ============================ Capacity =============================

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
            pointer ptr_first = first.base();
            for (; first != last; ++first) {
                _alloc.destroy(first.base());
            }
            size_type size_right = _end - last.base();
            for (size_type i = 0; i < size_right; i++){
                _alloc.construct(ptr_first + i, *last.base());
                _alloc.destroy(last.base());
                ++last;
            }
            _end = ptr_first + size_right;
            return iterator(ptr_first);
        }

    private:
        allocator_type      _alloc;
        pointer             _start;
        pointer             _end;
        pointer             _capacity;

        //* ========================= range_construct =========================

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
            for (long i = 0; i != n; i++){
                _alloc.construct(_end, *first++);
                _end++;
            }
        }
	};
}
