/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:24:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/29 15:45:25 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <utils.hpp>

namespace ft
{
    //* ======================= Basic iterator template =======================
    
    template < typename Category, typename T, typename Distance = ptrdiff_t,
                typename Pointer = T*, typename Reference =  T& >
    struct iterator
    {
        typedef Category                               iterator_category;
        typedef T                                      value_type;
        typedef Distance                               difference_type;
        typedef Pointer                                pointer;
        typedef Reference                              reference;
    };

    //* =================== Basic iterator_traits template ====================

    template < typename Iterator >
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category   iterator_category;
        typedef typename Iterator::value_type          value_type;
        typedef typename Iterator::difference_type     difference_type;
        typedef typename Iterator::pointer             pointer;
        typedef typename Iterator::reference           reference;
    };
    
    //* =================== Pointer iterator_traits template ==================

    template < typename T >
    struct iterator_traits<T*>
    {
        typedef std::random_access_iterator_tag       iterator_category;
        typedef T                                     value_type;
        typedef ptrdiff_t                             difference_type;
        typedef T*                                    pointer;
        typedef T&                                    reference;
    };
    
    //* ================ Const Pointer iterator_traits template ===============

    template < typename T >
    struct iterator_traits<const T*>
    {
        typedef std::random_access_iterator_tag       iterator_category;
        typedef T                                     value_type;
        typedef ptrdiff_t                             difference_type;
        typedef const T*                              pointer;
        typedef const T&                              reference;
    };

     //* ======================= Random access iterator =======================

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
    operator-(normal_iterator<IteratorL, Container>& lhs,
              normal_iterator<IteratorR, Container>& rhs)
    { return lhs.base() - rhs.base(); }
    
    template < typename Iterator, typename Container >
    typename normal_iterator<Iterator, Container>::difference_type 
    operator-(normal_iterator<Iterator, Container>& lhs,
              normal_iterator<Iterator, Container>& rhs)
    { return lhs.base() - rhs.base(); }

    template < typename Iterator, typename Container >
    normal_iterator<Iterator, Container> 
    operator+(typename normal_iterator<Iterator, Container>::difference_type n,
              const normal_iterator<Iterator, Container>& i)
    { return normal_iterator<Iterator, Container>(i.base() + n); }

    //* ======================= Reverse iterator =======================

    template < typename Iterator, typename Container >
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
        reverse_iterator() : _Elem(iterator_type()) {}

        //Copy Constructor
        explicit reverse_iterator(const iterator_type elem) : _Elem(elem) {}

        //iterator to const_iterator conversion
        template < typename Iter >
        reverse_iterator(const reverse_iterator<Iter, typename enable_if
                <are_same<Iter, typename Container::pointer>::_value,
                        Container>::_type>& i) : _Elem(i.base()) {}

        //member overloading operator
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

        reference operator[](difference_type n) const { return base()[n - 1]; }

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
    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator== (const reverse_iterator<IteratorL, Container>& lhs,
                     const reverse_iterator<IteratorR, Container>& rhs)
    { return lhs.base() == rhs.base(); }

    template < typename Iterator, typename Container >
    bool operator== (const reverse_iterator<Iterator, Container>& lhs,
                     const reverse_iterator<Iterator, Container>& rhs)
    { return lhs.base() == rhs.base(); }

    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator!= (const reverse_iterator<IteratorL, Container>& lhs,
                     const reverse_iterator<IteratorR, Container>& rhs)
    { return lhs.base() != rhs.base(); }

    template < typename Iterator, typename Container >
    bool operator!= (const reverse_iterator<Iterator, Container>& lhs,
                     const reverse_iterator<Iterator, Container>& rhs)
    { return lhs.base() != rhs.base(); }

    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator< (const reverse_iterator<IteratorL, Container>& lhs,
                    const reverse_iterator<IteratorR, Container>& rhs)
    { return lhs.base() > rhs.base(); }

    template < typename Iterator, typename Container >
    bool operator< (const reverse_iterator<Iterator, Container>& lhs,
                    const reverse_iterator<Iterator, Container>& rhs)
    { return lhs.base() > rhs.base(); }

    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator> (const reverse_iterator<IteratorL, Container>& lhs,
                    const reverse_iterator<IteratorR, Container>& rhs)
    { return lhs.base() < rhs.base(); }

    template < typename Iterator, typename Container >
    bool operator> (const reverse_iterator<Iterator, Container>& lhs,
                    const reverse_iterator<Iterator, Container>& rhs)
    { return lhs.base() < rhs.base(); }

    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator<= (const reverse_iterator<IteratorL, Container>& lhs,
                     const reverse_iterator<IteratorR, Container>& rhs)
    { return lhs.base() >= rhs.base(); }

    template < typename Iterator, typename Container >
    bool operator<= (const reverse_iterator<Iterator, Container>& lhs,
                     const reverse_iterator<Iterator, Container>& rhs)
    { return lhs.base() >= rhs.base(); }

    template < typename IteratorL, typename IteratorR, typename Container >
    bool operator>= (const reverse_iterator<IteratorL, Container>& lhs,
                     const reverse_iterator<IteratorR, Container>& rhs)
    { return lhs.base() <= rhs.base(); }

    template < typename Iterator, typename Container >
    bool operator>= (const reverse_iterator<Iterator, Container>& lhs,
                     const reverse_iterator<Iterator, Container>& rhs)
    { return lhs.base() <= rhs.base(); }

    template < typename IteratorL, typename IteratorR, typename Container >
    typename reverse_iterator<IteratorL, Container>::difference_type
    operator-(reverse_iterator<IteratorL, Container>& lhs,
              reverse_iterator<IteratorR, Container>& rhs)
    { return rhs.base() - lhs.base(); }

    template < typename Iterator, typename Container >
    typename reverse_iterator<Iterator, Container>::difference_type
    operator-(reverse_iterator<Iterator, Container>& lhs,
              reverse_iterator<Iterator, Container>& rhs)
    { return rhs.base() - lhs.base(); }

    template < typename Iterator, typename Container >
    reverse_iterator<Iterator, Container>
    operator+(typename reverse_iterator<Iterator, Container>::difference_type n,
              const reverse_iterator<Iterator, Container>& i)
    { return reverse_iterator<Iterator, Container>(i.base() - n); }
}
