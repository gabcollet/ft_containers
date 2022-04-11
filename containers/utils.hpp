/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:22:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/11 15:13:32 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    //* ========================== Integral_constant ==========================
    
	template < typename T, T Val >
	struct integral_constant 
	{
		typedef integral_constant   type;
		typedef T                 value_type;
		static const bool           value = Val;
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

	template < typename T >
	struct is_integral : public _is_integral_result<T> {};

    //* ============================== enable_if ==============================

    template < bool, typename >
    struct enable_if {};

    template < typename T >
    struct enable_if<true, T>
    { 
        typedef T _type;
    };

     //* ============================== are_same ==============================
     
    template < typename, typename >
    struct are_same
    {
        enum {_value = 0};
        typedef false_type _type;
    };
    
    template < typename T >
    struct are_same<T, T>
    {
        enum {_value = 1};
        typedef true_type _type;
    };
}
