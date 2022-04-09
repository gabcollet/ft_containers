/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:43 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/08 22:47:55 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <cstddef>

namespace ft
{
	template < typename _Tp, typename _Alloc = std::allocator<_Tp> >
	class vector
	{
		//* =========================== Member types ===========================
		
    public:
        typedef _Tp										value_type;
        typedef _Alloc                                  allocator_type;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef typename allocator_type::pointer        pointer;
        typedef typename allocator_type::const_pointer  const_pointer;
        /* typedef typename ft::random_access_iterator<value_type>	iterator; //a coder
        typedef typename ft::random_access_iterator<const value_type>	const_iterator;
        typedef typename ft::reverse_iterator<iterator>	reverse_iterator; //a coder
        typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator; */
	};
}
