/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:22:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/08 17:24:15 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	//* ============================= Is_integral =============================

	template < typename _Tp, _Tp _Val >
	struct integral_constant 
	{
		typedef integral_constant	type;
		typedef _Tp					value_type;
		static const bool			value = _Val;
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;
	
	template < typename >
	struct _is_integral_result : public false_type {};
	
	template <>
	struct _is_integral_result<bool> : public true_type {};
	
	template <>
	struct _is_integral_result<char> : public true_type {};
	
	template <>
	struct _is_integral_result<signed char> : public true_type {};
	
	template <>
	struct _is_integral_result<unsigned char> : public true_type {};
	
	template <>
	struct _is_integral_result<wchar_t> : public true_type {};
	
	template <>
	struct _is_integral_result<short> : public true_type {};
	
	template <>
	struct _is_integral_result<unsigned short> : public true_type {};
	
	template <>
	struct _is_integral_result<int> : public true_type {};
	
	template <>
	struct _is_integral_result<unsigned int> : public true_type {};

	template <>
	struct _is_integral_result<long> : public true_type {};
	
	template <>
	struct _is_integral_result<unsigned long> : public true_type {};

	template <typename _Tp>
	struct is_integral : public _is_integral_result<_Tp> {};
}
