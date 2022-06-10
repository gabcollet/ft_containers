/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:29:17 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/10 12:06:57 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <limits>

#include "map.hpp"
#include <map>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template<typename Key, typename T>
void printMap(const NAMESPACE::map<Key, T>& map, int line) {
    std::cout << "line: " << line << std::endl;
    for (typename NAMESPACE::map<Key,T>::const_iterator it=map.begin(); it!=map.end(); ++it)
		std::cout << "(" <<it->first << "," << it->second << ")" << ' ';
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

int main()
{
    std::cout << "||==================================================================||" << std::endl;
    std::cout << "||                            -MAP TEST-                            ||" << std::endl;
    std::cout << "||==================================================================||" << std::endl;
    {
        std::cout << std::endl;
        std::cout << "||========================== Constructor ===========================||" << std::endl;
        //empty constructor
        NAMESPACE::map<int, int> map;
        for (int i = 0; i < 10; i++)
            map.insert(NAMESPACE::make_pair(i, i * 2));
        printMap(map, __LINE__);
        //range constructor
        NAMESPACE::map<int,int>::iterator it=map.begin();
        NAMESPACE::map<int,int>::iterator ite=map.end();
        --ite;
        --ite;
        NAMESPACE::map<int, int> range_map(it, ite);
        printMap(range_map, __LINE__);
        //copy_constructor
        NAMESPACE::map<int, int> copy_map(range_map);
        printMap(copy_map, __LINE__);
        std::cout << "||======================= Assignment operator ======================||" << std::endl;
        std::cout << "before assigment :" << std::endl;
        printMap(copy_map, __LINE__);
        copy_map = map;
        std::cout << "after assigment :" << std::endl;
        printMap(copy_map, __LINE__);
    }
    {
        std::cout << std::endl;
        std::cout << "||========================== Get allocator =========================||" << std::endl;
        int psize;
        NAMESPACE::map<char,int> map;
        NAMESPACE::pair<const char,int>* p;
        p=map.get_allocator().allocate(5);
        psize = sizeof(std::map<char,int>::value_type)*5;
        std::cout << "The allocated array has a size of " << psize << " bytes." << std::endl;
        map.get_allocator().deallocate(p,5);

    }
    return 0;
}