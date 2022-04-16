/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:43 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/16 11:27:14 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <cstddef>
#include "iterator.hpp"

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
        explicit vector (const allocator_type& alloc = allocator_type()) :
            _alloc(alloc), _start(nullptr), _end(nullptr), _capacity(nullptr) {}

        //fill constructor
        explicit vector (size_t n, const value_type& val = value_type(),
                          const allocator_type& alloc = allocator_type()) :
            _alloc(alloc), _start(nullptr), _end(nullptr), _capacity(nullptr)
        {
            for (size_t i = 0; i < n; i++)
                push_back(val);
        }

        //range constructor
/*        template < typename InputIterator >
        vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type()) :
            _alloc(alloc), _start(nullptr), _end(nullptr), _capacity(nullptr)
        {
            // Check whether it's an integral type.  If so, it's not an iterator.
            typedef typename ft::is_integral<InputIterator>::type integral;

        }*/

        //copy constructor
//        vector (const vector& x) {}

        //member overload
//        vector& operator= (const vector& x) { return }

        size_t size() const {return _end - _start;}

        size_t max_size() const {return _alloc.max_size();}

        size_t capacity() const {return _capacity - _start;}

        void reserve (size_t n)
        {
            if (n > max_size())
                throw std::length_error("vector::reserve");
            if (n > capacity()){
                pointer oldStart = _start;
                pointer oldEnd = _end;
                size_t oldCapacity = capacity();

                _start = _alloc.allocate(n);
                _end = _start;
                _capacity = _start + n;
                while (oldStart != oldEnd){
                    _alloc.construct(_end, *oldStart);
                    _end++;
                    oldStart++;
                }
                _alloc.deallocate(oldStart - size(), oldCapacity);
            }
        }

        reference operator[] (size_t n) {return *(_start + n);}
        const_reference  operator[] (size_t n) const {return *(_start + n);}

        void push_back (const value_type& val)
        {
            if (_end == _capacity){
                size_t newCapacity;
                if (size() > 0)
                    newCapacity = size() * 2;
                else
                    newCapacity = 1;
                reserve(newCapacity);
            }
            _alloc.construct(_end, val);
            _end++;
        }

    private:
        allocator_type      _alloc;
        pointer             _start;
        pointer             _end;
        pointer             _capacity;

        //* ======================== Private functions ========================
/*        template <typename Integer>
        void _initialize_dispatch(Integer n, Integer value, true_type)*/
	};
}
