/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:37:36 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/11 15:23:45 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <limits>

#include "stack.hpp"
#include <stack>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template<typename T>
void printStack(NAMESPACE::stack<T> s)
{
    if (s.empty()){
        std::cout << std::endl;
        return;
    }    
    int x = s.top();
    s.pop();
    std::cout << x << ' ';
    printStack(s);
    s.push(x);
}

template<typename T>
void printStack(const NAMESPACE::stack<T>& stack, int line) {
    std::cout << "line: " << line << std::endl;
    printStack(stack);
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

int main()
{
    std::cout << "||==================================================================||" << std::endl;
    std::cout << "||                           -STACK TEST-                           ||" << std::endl;
    std::cout << "||==================================================================||" << std::endl;
    {
        std::cout << std::endl;
        std::cout << "||========================== Constructor ===========================||" << std::endl;
        //empty constructor
        NAMESPACE::stack<int> stack;
        printStack(stack, __LINE__);
        for (int i = 0; i < 10; i++)
            stack.push(i + 42);
        NAMESPACE::stack<int> copy_stack(stack);
        printStack(copy_stack, __LINE__);
        stack.pop();
        stack.pop();
        std::cout << "||======================= Assignment operator ======================||" << std::endl;
        std::cout << "before assigment :" << std::endl;
        printStack(copy_stack, __LINE__);
        copy_stack = stack;
        std::cout << "after assigment :" << std::endl;
        printStack(copy_stack, __LINE__);
        std::cout << "||========================== Element access ========================||" << std::endl;
        std::cout << "before assigment :" << std::endl;
        //non const
        std::cout << "element on top is: " << stack.top() << std::endl;
        const NAMESPACE::stack<int> const_stack = stack;
        //const
        std::cout << "element on top is: " << const_stack.top() << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Capacity ============================||" << std::endl;
        NAMESPACE::stack<int> stack;
        std::cout << std::boolalpha;
        std::cout << "Is empty?: " << stack.empty() << std::endl;
        std::cout << "Size is: " << stack.size() << std::endl;
        printStack(stack, __LINE__);
        for (int i = 0; i < 10; i++)
            stack.push(i + 42);
        std::cout << "Is empty?: " << stack.empty() << std::endl;
        std::cout << "Size is: " << stack.size() << std::endl;
        printStack(stack, __LINE__);
        std::cout << std::endl;
        std::cout << "||============================= Modifier ============================||" << std::endl;
        printStack(stack, __LINE__);
        stack.push(1);
        printStack(stack, __LINE__);
        stack.pop();
        printStack(stack, __LINE__);
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Capacity ============================||" << std::endl;
        NAMESPACE::stack<int> stack;
        NAMESPACE::stack<int> stack2;
        for (int i = 0; i < 10; i++)
            stack.push(i + 42);
        printStack(stack, __LINE__);
        for (int i = 0; i < 10; i++)
            stack2.push(i + 42 / 2);
        printStack(stack2, __LINE__);
        std::cout << std::boolalpha;
        std::cout << "S1 == S2?: " << (stack == stack2) << std::endl;
        std::cout << "S1 != S2?: " << (stack != stack2) << std::endl;
        std::cout << "S1 < S2?: " << (stack < stack2) << std::endl;
        std::cout << "S1 <= S2?: " << (stack <= stack2) << std::endl;
        std::cout << "S1 > S2?: " << (stack > stack2) << std::endl;
        std::cout << "S1 >= S2?: " << (stack >= stack2) << std::endl;
    }
    return 0;
}
