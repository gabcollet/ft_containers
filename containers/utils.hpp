/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:22:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/08 23:02:59 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    //* ========================== Integral_constant ==========================
    
	template < typename _Tp, _Tp _Val >
	struct integral_constant 
	{
		typedef integral_constant   type;
		typedef _Tp                 value_type;
		static const bool           value = _Val;
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;
    
	//* ============================= Is_integral =============================
	
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

	template < typename _Tp >
	struct is_integral : public _is_integral_result<_Tp> {};

    //* ============================== enable_if ==============================

    template < bool, typename >
    struct enable_if {};

    template < typename _Tp >
    struct enable_if<true, _Tp>
    { 
        typedef _Tp _type; 
    };

     //* ============================== are_same ==============================
     
    template < typename, typename >
    struct are_same
    {
        enum {_value = 0};
        typedef false_type _type;
    };
    
    template < typename _Tp >
    struct are_same<_Tp, _Tp>
    {
        enum {_value = 1};
        typedef true_type _type;
    };
}
