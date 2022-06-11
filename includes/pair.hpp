/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:37:05 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/11 14:01:59 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template <class T1, class T2> 
    struct pair
    {
        //* ========================== Member types ===========================

        typedef T1      first_type;
        typedef T2      second_type;

        //* ========================= Member objects ==========================

        T1 first;
        T2 second;

        //* ========================= Member functions =========================
        
        //default constructor
        pair() : first(), second() {}

        //copy constructor
        template<class U, class V> 
        pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

        //initialization constructor
        pair (const first_type& a, const second_type& b) : first(a), second(b) {}

        pair& operator= (const pair& pr) 
        {
            first = pr.first;
            second = pr.second;
            return *this;
        }
    };
    
    //* ========================= Non-member function =========================

    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return pair<T1, T2>(x, y);
    }

    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return (lhs.first == rhs.first); 
    }
    
    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return !(lhs == rhs); 
    }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); 
    }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return !(rhs < lhs); 
    }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return rhs < lhs; 
    }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return !(lhs < rhs); 
    }
}
