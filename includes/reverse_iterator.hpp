/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:17:24 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/03 15:24:01 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "type_traits.hpp"

namespace ft
{
    template < typename Iterator >
    class reverse_iterator
    {

    private:
        Iterator                                        _Elem;
        typedef iterator_traits<Iterator>               _traits_type;

    public:
        typedef Iterator                                iterator_type;
        typedef typename _traits_type::iterator_category iterator_category;
        typedef typename _traits_type::value_type       value_type;
        typedef typename _traits_type::difference_type  difference_type;
        typedef typename _traits_type::pointer          pointer;
        typedef typename _traits_type::reference        reference;

        //Default Constructor
        reverse_iterator() : _Elem() {}

        reverse_iterator(const reverse_iterator& i) : _Elem(i._Elem) {}

        //Initialization Constructor
        explicit reverse_iterator(iterator_type i) : _Elem(i) {}

        //Copy Constructor
        template < typename Iter >
        reverse_iterator(const reverse_iterator<Iter>& i) : _Elem(i.base()) {}
        
        ~reverse_iterator() {}

        //member overloading operator
        reverse_iterator& operator=(const reverse_iterator& rit)
        {
            _Elem = rit._Elem;
            return *this;
        }

        reference operator*() const
        {
            iterator_type tmp = _Elem;
            return *--tmp;
        }

        pointer operator->() const { return &(operator*()); }

        reverse_iterator& operator++()
        {
            --_Elem;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reverse_iterator& operator--()
        {
            ++_Elem;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        // reference operator[](difference_type n) const { return *(*this + n); }
        reference operator[](difference_type n) const { return base()[-n-1]; }

        reverse_iterator& operator+=(difference_type n)
        {
            _Elem -= n;
            return *this;
        }

        reverse_iterator operator+(difference_type n) const
        { return reverse_iterator(_Elem - n); }

        reverse_iterator& operator-=(difference_type n)
        {
            _Elem += n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const
        { return reverse_iterator(_Elem + n); }

        iterator_type base() const { return _Elem; }

    };
    //non-member overloading operator
    template < typename IteratorL, typename IteratorR >
    bool operator== (const reverse_iterator<IteratorL>& lhs,
                     const reverse_iterator<IteratorR>& rhs)
    { return lhs.base() == rhs.base(); }

    template < typename Iterator >
    bool operator== (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<Iterator>& rhs)
    { return lhs.base() == rhs.base(); }

    template < typename IteratorL, typename IteratorR >
    bool operator!= (const reverse_iterator<IteratorL>& lhs,
                     const reverse_iterator<IteratorR>& rhs)
    { return lhs.base() != rhs.base(); }

    template < typename Iterator >
    bool operator!= (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<Iterator>& rhs)
    { return lhs.base() != rhs.base(); }

    template < typename IteratorL, typename IteratorR >
    bool operator< (const reverse_iterator<IteratorL>& lhs,
                    const reverse_iterator<IteratorR>& rhs)
    { return lhs.base() > rhs.base(); }

    template < typename Iterator >
    bool operator< (const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    { return lhs.base() > rhs.base(); }

    template < typename IteratorL, typename IteratorR >
    bool operator> (const reverse_iterator<IteratorL>& lhs,
                    const reverse_iterator<IteratorR>& rhs)
    { return lhs.base() < rhs.base(); }

    template < typename Iterator >
    bool operator> (const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    { return lhs.base() < rhs.base(); }

    template < typename IteratorL, typename IteratorR >
    bool operator<= (const reverse_iterator<IteratorL>& lhs,
                     const reverse_iterator<IteratorR>& rhs)
    { return lhs.base() >= rhs.base(); }

    template < typename Iterator >
    bool operator<= (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<Iterator>& rhs)
    { return lhs.base() >= rhs.base(); }

    template < typename IteratorL, typename IteratorR >
    bool operator>= (const reverse_iterator<IteratorL>& lhs,
                     const reverse_iterator<IteratorR>& rhs)
    { return lhs.base() <= rhs.base(); }

    template < typename Iterator >
    bool operator>= (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<Iterator>& rhs)
    { return lhs.base() <= rhs.base(); }

    template < typename IteratorL, typename IteratorR >
    typename reverse_iterator<IteratorL>::difference_type
    operator-(const reverse_iterator<IteratorL>& lhs,
              const reverse_iterator<IteratorR>& rhs)
    { return rhs.base() - lhs.base(); }

    template < typename Iterator >
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator>& lhs,
              const reverse_iterator<Iterator>& rhs)
    { return rhs.base() - lhs.base(); }

    template < typename Iterator >
    reverse_iterator<Iterator>
    operator+(typename reverse_iterator<Iterator>::difference_type n,
              const reverse_iterator<Iterator>& i)
    { return reverse_iterator<Iterator>(i.base() - n); }
}