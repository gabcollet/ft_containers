/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:24:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/08 17:24:40 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

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
		typedef _Category	iterator_category;
		typedef _Tp			value_type;
		typedef _Distance	difference_type;
		typedef _Pointer	pointer;
		typedef _Reference	reference;
	};

	//* =================== Basic iterator_traits template ====================

	template < typename _Iterator >
	struct iterator_traits
	{
		typedef typename _Iterator::iterator_category	iterator_category;
		typedef typename _Iterator::value_type			value_type;
		typedef typename _Iterator::difference_type		difference_type;
		typedef typename _Iterator::pointer				pointer;
		typedef typename _Iterator::reference			reference;
	};
	
	//* =================== Pointer iterator_traits template ==================

	template < typename _Tp >
	struct iterator_traits<_Tp*>
	{
		typedef random_access_iterator_tag				iterator_category;
		typedef _Tp										value_type;
		typedef ptrdiff_t								difference_type;
		typedef _Tp*									pointer;
		typedef _Tp&									reference;
	};
	
	//* ================ Const Pointer iterator_traits template ===============

	template < typename _Tp >
	struct iterator_traits<const _Tp*>
	{
		typedef random_access_iterator_tag				iterator_category;
		typedef _Tp										value_type;
		typedef ptrdiff_t								difference_type;
		typedef _Tp*									pointer;
		typedef _Tp&									reference;
	};
}
