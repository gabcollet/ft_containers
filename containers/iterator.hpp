/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:24:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/08 23:46:49 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "utils.hpp"

namespace ft
{

    //* ============================ Iterator tag =============================

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};
    
    //* ======================= Basic iterator template =======================
    
    template < typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
                typename _Pointer = _Tp*, typename _Reference =  _Tp& >
    struct iterator
    {
        typedef _Category                               iterator_category;
        typedef _Tp                                     value_type;
        typedef _Distance                               difference_type;
        typedef _Pointer                                pointer;
        typedef _Reference                              reference;
    };

    //* =================== Basic iterator_traits template ====================

    template < typename _Iterator >
    struct iterator_traits
    {
        typedef typename _Iterator::iterator_category   iterator_category;
        typedef typename _Iterator::value_type          value_type;
        typedef typename _Iterator::difference_type     difference_type;
        typedef typename _Iterator::pointer             pointer;
        typedef typename _Iterator::reference           reference;
    };
    
    //* =================== Pointer iterator_traits template ==================

    template < typename _Tp >
    struct iterator_traits<_Tp*>
    {
        typedef random_access_iterator_tag              iterator_category;
        typedef _Tp                                     value_type;
        typedef ptrdiff_t                               difference_type;
        typedef _Tp*                                    pointer;
        typedef _Tp&                                    reference;
    };
    
    //* ================ Const Pointer iterator_traits template ===============

    template < typename _Tp >
    struct iterator_traits<const _Tp*>
    {
        typedef random_access_iterator_tag              iterator_category;
        typedef _Tp                                     value_type;
        typedef ptrdiff_t                               difference_type;
        typedef _Tp*                                    pointer;
        typedef _Tp&                                    reference;
    };

     //* =========================== Normal iterator ==========================

    template < typename _Iterator, typename _Container >
    class normal_iterator
    {
    protected:
        _Iterator                                       _Elem;
        typedef iterator_traits<_Iterator>              _traits_type;
        
    public:
        typedef _Iterator                               iterator_type;
        typedef typename _traits_type::iterator_category iterator_category;
        typedef typename _traits_type::value_type       value_type;
        typedef typename _traits_type::differenece_type difference_type;
        typedef typename _traits_type::pointer          pointer;
        typedef typename _traits_type::reference        reference;
        
        normal_iterator() : _Elem(_Iterator()) {}
        normal_iterator(const _Iterator& elem) : _Elem(elem) {}

        //iterator to const_iterator conversion
        template < typename _Iter >
        normal_iterator(const normal_iterator<_Iter, typename enable_if
                        <(are_same<_Iter, typename _Container::pointer>::_value),
                        _Container>::_type>& _i) : _Elem(_i.base()) {}

        //overloading operator
        reference operator*() const { return *_Elem; }
        pointer operator->() const { return _Elem; }
        normal_iterator& operator++() 
        { 
            ++_Elem;
            return *this;
        }
        normal_iterator operator++(int) { return normal_iterator(_Elem++); }
        normal_iterator& operator--()
        {
            --_Elem;
            return *this;
        }
        normal_iterator operator--(int) { return normal_iterator(_Elem--); }
        reference operator[](difference_type _n) { return _Elem[_n]; }
        normal_iterator& operator+=(difference_type _n)
        {
            _Elem += _n;
            return *this;
        }
        normal_iterator operator+(difference_type _n) const
        { return normal_iterator(_Elem + _n); }
        normal_iterator& operator-=(difference_type _n)
        {
            _Elem -= _n;
            return *this;
        }
        normal_iterator operator-(difference_type _n) const
        { return normal_iterator(_Elem - _n); }
        const _Iterator& base() const { return _Elem; }

        //reste les ==, !=, <, >, <=, >=
    };
}
