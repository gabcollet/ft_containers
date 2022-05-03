/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:24:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/03 15:23:45 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iterator>
#include "utils.hpp"
#include "type_traits.hpp"

namespace ft
{
    template < typename Iterator, typename Container >
    class normal_iterator
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
        normal_iterator() : _Elem(iterator_type()) {}

        //Copy Constructor
        explicit normal_iterator(const iterator_type elem) : _Elem(elem) {}

        //iterator to const_iterator conversion
        template < typename Iter >
        normal_iterator(const normal_iterator<Iter, typename enable_if
                        <are_same<Iter, typename Container::pointer>::_value,
                        Container>::_type>& i) : _Elem(i.base()) {}

        //member overloading operator
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

        reference operator[](difference_type n) { return _Elem[n]; }

        normal_iterator& operator+=(difference_type n)
        {
            _Elem += n;
            return *this;
        }

        normal_iterator operator+(difference_type n) const
        { return normal_iterator(_Elem + n); }

        normal_iterator& operator-=(difference_type n)
        {
            _Elem -= n;
            return *this;
        }
      
        normal_iterator operator-(difference_type n) const
        { return normal_iterator(_Elem - n); }
       
        const iterator_type& base() const { return _Elem; }

    };
    //non-member overloading operator
    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator== (const normal_iterator<IteratorL, Container>& lhs,
                     const normal_iterator<IteratorR, Container>& rhs)
    { return lhs.base() == rhs.base(); }
    
    template < typename Iterator, typename Container >
    bool operator== (const normal_iterator<Iterator, Container>& lhs,
                     const normal_iterator<Iterator, Container>& rhs)
    { return lhs.base() == rhs.base(); }
    
    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator!= (const normal_iterator<IteratorL, Container>& lhs,
                     const normal_iterator<IteratorR, Container>& rhs)
    { return lhs.base() != rhs.base(); }
    
    template < typename Iterator, typename Container >
    bool operator!= (const normal_iterator<Iterator, Container>& lhs,
                     const normal_iterator<Iterator, Container>& rhs)
    { return lhs.base() != rhs.base(); }
    
    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator< (const normal_iterator<IteratorL, Container>& lhs,
                    const normal_iterator<IteratorR, Container>& rhs)
    { return lhs.base() < rhs.base(); }
    
    template < typename Iterator, typename Container >
    bool operator< (const normal_iterator<Iterator, Container>& lhs,
                    const normal_iterator<Iterator, Container>& rhs)
    { return lhs.base() < rhs.base(); }
   
    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator> (const normal_iterator<IteratorL, Container>& lhs,
                    const normal_iterator<IteratorR, Container>& rhs)
    { return lhs.base() > rhs.base(); }
    
    template < typename Iterator, typename Container >
    bool operator> (const normal_iterator<Iterator, Container>& lhs,
                    const normal_iterator<Iterator, Container>& rhs)
    { return lhs.base() > rhs.base(); }
    
    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator<= (const normal_iterator<IteratorL, Container>& lhs,
                     const normal_iterator<IteratorR, Container>& rhs)
    { return lhs.base() <= rhs.base(); }
    
    template < typename Iterator, typename Container >
    bool operator<= (const normal_iterator<Iterator, Container>& lhs,
                     const normal_iterator<Iterator, Container>& rhs)
    { return lhs.base() <= rhs.base(); }
    
    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator>= (const normal_iterator<IteratorL, Container>& lhs,
                     const normal_iterator<IteratorR, Container>& rhs)
    { return lhs.base() >= rhs.base(); }
    
    template < typename Iterator, typename Container >
    bool operator>= (const normal_iterator<Iterator, Container>& lhs,
                     const normal_iterator<Iterator, Container>& rhs)
    { return lhs.base() >= rhs.base(); }
    
    template < typename IteratorL, typename IteratorR, typename Container >
    typename normal_iterator<IteratorL, Container>::difference_type 
    operator-(const normal_iterator<IteratorL, Container>& lhs,
              const normal_iterator<IteratorR, Container>& rhs)
    { return lhs.base() - rhs.base(); }
    
    template < typename Iterator, typename Container >
    typename normal_iterator<Iterator, Container>::difference_type 
    operator-(const normal_iterator<Iterator, Container>& lhs,
              const normal_iterator<Iterator, Container>& rhs)
    { return lhs.base() - rhs.base(); }

    template < typename Iterator, typename Container >
    normal_iterator<Iterator, Container> 
    operator+(typename normal_iterator<Iterator, Container>::difference_type n,
              const normal_iterator<Iterator, Container>& i)
    { return normal_iterator<Iterator, Container>(i.base() + n); }
}
