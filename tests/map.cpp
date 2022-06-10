/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:29:17 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/10 14:49:35 by gcollet          ###   ########.fr       */
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
    {
        std::cout << std::endl;
        std::cout << "||========================= Element access =========================||" << std::endl;
        //non const
        NAMESPACE::map<int, double> map;
        for (double i = 0; i < 10; i++)
            map.insert(NAMESPACE::make_pair(i, i * 2.31416));
        printMap(map, __LINE__);
        std::cout << "Element at 2 is: " << map.at(2) << std::endl;
        std::cout << "Element at 9 is: " << map.at(9) << std::endl;
        std::cout << "Element [8] is: " << map[8] << std::endl;
        std::cout << "Element [0] is: " << map[0] << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        //const
        const NAMESPACE::map<int, double> const_map;
        for (double i = 0; i < 10; i++)
            map.insert(NAMESPACE::make_pair(i, i * 2.31416));
        std::cout << "Element at 2 is: " << map.at(2) << std::endl;
        std::cout << "Element at 9 is: " << map.at(9) << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Iterators ===========================||" << std::endl;
        NAMESPACE::map<int, double> map;
        for (double i = 0; i < 10; i++)
            map.insert(NAMESPACE::make_pair(i, i * 2.31416));
        printMap(map, __LINE__);
        NAMESPACE::map<int, double>::iterator it;
        it = map.begin();
        std::cout << "Iterator begin is: " << it->first << std::endl;
        it = map.end();
        --it;
        std::cout << "Iterator --end is: " << it->first << std::endl;
        std::cout << std::endl;
        //const
        NAMESPACE::map<int, double>::const_iterator cit;
        cit = map.begin();
        std::cout << "Const_iterator begin is: " << cit->first << std::endl;
        cit = map.end();
        --cit;
        std::cout << "Const_iterator --end is: " << cit->first << std::endl;
        std::cout << std::endl;
        //reverse non const
        NAMESPACE::map<int, double>::reverse_iterator rit;
        rit = map.rbegin();
        std::cout << "Reverse iterator rbegin is: " << rit->first << std::endl;
        rit = map.rend();
        --rit;
        std::cout << "Reverse iterator --rend is: " << rit->first << std::endl;
        std::cout << std::endl;
        //reverse const
        NAMESPACE::map<int, double>::const_reverse_iterator rcit;
        rcit = map.rbegin();
        std::cout << "Reverse const_iterator begin is: " << rcit->first << std::endl;
        rcit = map.rend();
        --rcit;
        std::cout << "Reverse const_iterator --rend is: " << rcit->first << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Capacity ============================||" << std::endl;
        NAMESPACE::map<int, std::string> map;
        printMap(map, __LINE__);
        std::cout << std::boolalpha;
        std::cout << "Is empty?: " << map.empty() << std::endl;
        std::cout << std::endl;
        map.insert(NAMESPACE::make_pair(11, "helloworld"));
        printMap(map, __LINE__);
        std::cout << "Is empty?: " << map.empty() << std::endl;
        for (double i = 0; i < 10; i++)
            map.insert(NAMESPACE::make_pair(i, "hello"));
        printMap(map, __LINE__);
        std::cout << "Size is: " << map.size() << std::endl;
        std::cout << "Max size is: " << map.max_size() << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Modifier ============================||" << std::endl;
        NAMESPACE::map<int, std::string> map, map2;
        NAMESPACE::map<int, std::string>::iterator it;
        for (double i = 0; i < 10; i++)
            map.insert(NAMESPACE::make_pair(i, "I love map"));
        map2 = map;
        printMap(map, __LINE__);
        map.clear();
        printMap(map, __LINE__);
        map.insert(NAMESPACE::make_pair(1, "I hate map"));
        printMap(map, __LINE__);
        it = map.end();
        map.insert(it, NAMESPACE::make_pair(2, "I'm neutral w map"));
        it = map.begin();
        map.insert(it, NAMESPACE::make_pair(3, "ZZZZZZZZ"));
        map.insert(it, NAMESPACE::make_pair(11, "ZZZAAAZZZZZ"));
        map.insert(it, NAMESPACE::make_pair(4, "AAAAAAA"));
        printMap(map, __LINE__);
        it = map.begin();
        map.insert(it, ++it);
        printMap(map, __LINE__);
        map.erase(it);
        printMap(map, __LINE__);
        map.erase(11);
        printMap(map, __LINE__);
        it = map.begin();
        map.erase(it, ++it);
        printMap(map, __LINE__);
        std::cout << "Before swap: " << std::endl;
        printMap(map2, __LINE__);
        map2.swap(map);
        std::cout << "After swap: " << std::endl;
        printMap(map2, __LINE__);
    }
    {
        std::cout << std::endl;
        std::cout << "||============================= Lookup =============================||" << std::endl;
        NAMESPACE::map<char,int> mymap;
        mymap['l']=20;
        mymap['m']=40;
        mymap['n']=60;
        mymap['o']=80;
        mymap['p']=100;
        printMap(mymap, __LINE__);
        std::cout << "count of 'o' is: " << mymap.count('o') << std::endl;
        //non const
        std::cout << "find of 'p' is: " << mymap.find('p')->first << std::endl;
        std::cout << "equal range of 'n' is: " << mymap.equal_range('n').first->first 
        << " to " << mymap.equal_range('n').second->first << std::endl;
        std::cout << "lower bound of 'm' is: " << mymap.lower_bound ('m')->first << std::endl;
        std::cout << "upper bound of 'm' is: " << mymap.upper_bound ('m')->first << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        //const
        const NAMESPACE::map<char,int> const_mymap = mymap;
        std::cout << "find of 'p' is: " << mymap.find('p')->first << std::endl;
        std::cout << "equal range of 'n' is: " << mymap.equal_range('n').first->first 
        << " to " << mymap.equal_range('n').second->first << std::endl;
        std::cout << "lower bound of 'm' is: " << mymap.lower_bound ('m')->first << std::endl;
        std::cout << "upper bound of 'm' is: " << mymap.upper_bound ('m')->first << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Observer ============================||" << std::endl;
        NAMESPACE::map<char,int> mymap;
        NAMESPACE::map<char,int>::key_compare mycomp = mymap.key_comp();
        mymap['a']=100;
        mymap['b']=200;
        mymap['c']=300;
        std::cout << "mymap contains:" << std::endl;
        char highest = mymap.rbegin()->first;
        NAMESPACE::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << std::endl;
        } while (mycomp((*it++).first, highest));
        NAMESPACE::pair<char,int> high;
        std::cout << "mymap contains:" << std::endl;
        high = *mymap.rbegin();
        it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mymap.value_comp()(*it++, high) );
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Operator ============================||" << std::endl;
        NAMESPACE::map<int, int> map;
        for (int i = 0; i < 10; i++)
            map.insert(NAMESPACE::make_pair(i, i * 2));
        std::cout << "Map 1 contain: " << std::endl;
        printMap(map, __LINE__);
        NAMESPACE::map<int, int> map2;
        for (int i = 0; i < 10; i++)
            map2.insert(NAMESPACE::make_pair(i, i + 2));
        std::cout << "Map 2 contain: " << std::endl;
        printMap(map2, __LINE__);
        std::cout << std::boolalpha;
        std::cout << "M1 == M2?: " << (map == map2) << std::endl;
        std::cout << "M1 != M2?: " << (map != map2) << std::endl;
        std::cout << "M1 < M2?: " << (map < map2) << std::endl;
        std::cout << "M1 <= M2?: " << (map <= map2) << std::endl;
        std::cout << "M1 > M2?: " << (map > map2) << std::endl;
        std::cout << "M1 >= M2?: " << (map >= map2) << std::endl;
        std::cout << "Before swap: " << std::endl;
        std::cout << std::endl;
        printMap(map2, __LINE__);
        NAMESPACE::swap(map, map2);
        std::cout << "After swap: " << std::endl;
        printMap(map2, __LINE__);
    }
    return 0;
}