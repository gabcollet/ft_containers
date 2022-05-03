/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:47 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/03 16:19:35 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> > 
    class stack
    {
        //* =========================== Member types ==========================

    public:
        typedef Container                                   container_type;
        typedef typename container_type::value_type         value_type;
        typedef typename container_type::size_type          size_type;
        typedef typename container_type::reference          reference;
        typedef typename container_type::const_reference    const_reference;
        
        //* ========================= Member functions =========================       
        
        //default constructor
        explicit stack(const Container& cont = container_type()) : c(cont) {}

        //copy constructor
        stack( const stack& other ) : c(other.c)
        {
            if (other.size() > 0) 
                *this = other;
        }

        //destructor
        ~stack() {}

        //member overload
        stack& operator=( const stack& other )
        {
            c = other.c;
            return *this;
        }

        //* ========================= Element access ==========================
        
        reference top() { return c.back(); }
		
        const_reference top() const { return c.back(); }

        //* ============================ Capacity =============================

        bool empty() const { return c.empty(); }
	
        size_type size() const { return c.size(); }
        
        //* ============================ Modifier =============================
        
        void push( const value_type& value ) { return c.push_back(value); }

        void pop() { return c.pop_back(); }

        //* ================== Non-member function prototype ==================

        template< class T_n, class Container_n >
        friend bool operator== ( const ft::stack<T_n,Container_n>& lhs,
                                 const ft::stack<T_n,Container_n>& rhs );
        
        template< class T_n, class Container_n >
        friend bool operator!= ( const ft::stack<T_n,Container_n>& lhs,
                                 const ft::stack<T_n,Container_n>& rhs );
        
        template< class T_n, class Container_n >
        friend bool operator< ( const ft::stack<T_n,Container_n>& lhs,
                                 const ft::stack<T_n,Container_n>& rhs );
        
        template< class T_n, class Container_n >
        friend bool operator<= ( const ft::stack<T_n,Container_n>& lhs,
                                 const ft::stack<T_n,Container_n>& rhs );
        
        template< class T_n, class Container_n >
        friend bool operator> ( const ft::stack<T_n,Container_n>& lhs,
                                 const ft::stack<T_n,Container_n>& rhs );
        
        template< class T_n, class Container_n >
        friend bool operator>= ( const ft::stack<T_n,Container_n>& lhs,
                                 const ft::stack<T_n,Container_n>& rhs );

    protected:
        container_type c;
    };  
    
    //* ========================= Non-member function =========================

    template< class T, class Container >
    bool operator== ( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c ==  rhs.c;
    }

    template< class T, class Container >
    bool operator!= ( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c != rhs.c;
    }
	
    template< class T, class Container >
    bool operator< ( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c < rhs.c;
    }

    template< class T, class Container >
    bool operator<= ( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c <= rhs.c;
    }
	
    template< class T, class Container >
    bool operator> ( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c > rhs.c;
    }
	
    template< class T, class Container >
    bool operator>= ( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
    {
        return lhs.c >= rhs.c;
    }
}
