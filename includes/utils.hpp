/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:22:59 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/29 16:31:12 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{
    //* ========================== Integral_constant ==========================
    
	template < typename T, T Val >
	struct integral_constant 
	{
		typedef integral_constant   type;
		typedef T                   value_type;
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

    template<bool B, typename T = void >
    struct enable_if {};

    template<typename T>
    struct enable_if<true, T>
    {
        typedef T _type;
    };

    //* ============================== are_same ===============================
     
    template < typename T, typename U>
    struct are_same /*: public false_type*/
    {
        static const bool _value = false;
        typedef false_type _type;
    };
    
    template < typename T >
    struct are_same<T, T> /*: public true_type*/
    {
        static const bool _value = true;
        typedef true_type _type;
    };

	//* ======================= lexicographical_compare =======================

	template<typename InputIt1, typename InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
 	                            InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2){
			if(*first1 < *first2)
				return true;
			if(*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
	
}
