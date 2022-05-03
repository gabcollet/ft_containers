/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:37:36 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/03 11:46:49 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/_types/_size_t.h>
#include "../includes/stack.hpp"

void printStack(ft::stack<int> s)
{
    if (s.empty())
    {
        std::cout << std::endl;
        return;
    }
        
    int x = s.top();
    s.pop();
    std::cout << x << ' ';
    printStack(s);
    s.push(x);
}

int main()
{
    ft::stack<int> stack;
    
    size_t size = 5;
    
    for (size_t i = 0; i < size; i++){
        stack.push(size - i);
    }
    printStack(stack);

    ft::stack<int> stack_cp(stack);
    printStack(stack_cp);

    std::cout << (stack == stack_cp) << std::endl;
}