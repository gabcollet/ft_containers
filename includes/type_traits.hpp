/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:19:35 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/03 15:22:11 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iterator>

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
}
