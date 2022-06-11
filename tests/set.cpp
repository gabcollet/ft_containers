/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:24:06 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/11 15:56:32 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <limits>

#include "set.hpp"
#include <set>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template<typename Key, typename T>
void printset(const NAMESPACE::set<Key, T>& set, int line) {
    std::cout << "line: " << line << std::endl;
    for (typename NAMESPACE::set<Key,T>::const_iterator it=set.begin(); it!=set.end(); ++it)
		std::cout << *it << ' ';
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

int main()
{
    std::cout << "||==================================================================||" << std::endl;
    std::cout << "||                            -SET TEST-                            ||" << std::endl;
    std::cout << "||==================================================================||" << std::endl;
    {
        std::cout << std::endl;
        std::cout << "||========================== Constructor ===========================||" << std::endl;
        //empty constructor
        NAMESPACE::set<int> set;
        for (int i = 0; i < 10; i++)
            set.insert(i * 2);
        printset(set, __LINE__);
        //range constructor
        NAMESPACE::set<int>::iterator it=set.begin();
        NAMESPACE::set<int>::iterator ite=set.end();
        --ite;
        --ite;
        NAMESPACE::set<int> range_set(it, ite);
        printset(range_set, __LINE__);
        //copy_constructor
        NAMESPACE::set<int> copy_set(range_set);
        printset(copy_set, __LINE__);
        std::cout << "||======================= Assignment operator ======================||" << std::endl;
        std::cout << "before assigment :" << std::endl;
        printset(copy_set, __LINE__);
        copy_set = set;
        std::cout << "after assigment :" << std::endl;
        printset(copy_set, __LINE__);
    }
    {
        std::cout << std::endl;
        std::cout << "||========================== Get allocator =========================||" << std::endl;
        int psize;
        NAMESPACE::set<char> set;
        char* p;
        p=set.get_allocator().allocate(5);
        psize = sizeof(std::set<char>::value_type)*5;
        std::cout << "The allocated array has a size of " << psize << " bytes." << std::endl;
        set.get_allocator().deallocate(p,5);
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Iterators ===========================||" << std::endl;
        NAMESPACE::set<double> set;
        for (double i = 0; i < 10; i++)
            set.insert(i * 3.1416);
        printset(set, __LINE__);
        NAMESPACE::set<double>::iterator it;
        it = set.begin();
        std::cout << "Iterator begin is: " << *it << std::endl;
        it = set.end();
        --it;
        std::cout << "Iterator --end is: " << *it << std::endl;
        std::cout << std::endl;
        //const
        NAMESPACE::set<double>::const_iterator cit;
        cit = set.begin();
        std::cout << "Const_iterator begin is: " << *cit << std::endl;
        cit = set.end();
        --cit;
        std::cout << "Const_iterator --end is: " << *cit << std::endl;
        std::cout << std::endl;
        //reverse non const
        NAMESPACE::set<double>::reverse_iterator rit;
        rit = set.rbegin();
        std::cout << "Reverse iterator rbegin is: " << *rit << std::endl;
        rit = set.rend();
        --rit;
        std::cout << "Reverse iterator --rend is: " << *rit << std::endl;
        std::cout << std::endl;
        //reverse const
        NAMESPACE::set<double>::const_reverse_iterator rcit;
        rcit = set.rbegin();
        std::cout << "Reverse const_iterator begin is: " << *rcit << std::endl;
        rcit = set.rend();
        --rcit;
        std::cout << "Reverse const_iterator --rend is: " << *rcit << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Capacity ============================||" << std::endl;
        NAMESPACE::set<std::string> set;
        printset(set, __LINE__);
        std::cout << std::boolalpha;
        std::cout << "Is empty?: " << set.empty() << std::endl;
        std::cout << std::endl;
        set.insert("helloworld");
        printset(set, __LINE__);
        std::cout << "Is empty?: " << set.empty() << std::endl;
        for (double i = 0; i < 10; i++)
            set.insert("hello");
        printset(set, __LINE__);
        std::cout << "Size is: " << set.size() << std::endl;
        std::cout << "Max size is: " << set.max_size() << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Modifier ============================||" << std::endl;
        NAMESPACE::set<std::string> set, set2;
        NAMESPACE::set<std::string>::iterator it;
        for (double i = 0; i < 10; i++)
            set.insert("I love set");
        set2 = set;
        printset(set, __LINE__);
        set.clear();
        printset(set, __LINE__);
        set.insert("I hate set");
        set.insert("ZZZZZZZZ");
        set.insert("ZZZAAAZZZZZ");
        set.insert("AAAAAAA");
        printset(set, __LINE__);
        it = set.begin();
        set.insert(it, ++it);
        printset(set, __LINE__);
        set.erase(it);
        printset(set, __LINE__);
        set.erase("I'm neutral w set");
        printset(set, __LINE__);
        it = set.begin();
        set.erase(it, ++it);
        printset(set, __LINE__);
        std::cout << "Before swap: " << std::endl;
        printset(set2, __LINE__);
        set2.swap(set);
        std::cout << "After swap: " << std::endl;
        printset(set2, __LINE__);
    }
    {
        std::cout << std::endl;
        std::cout << "||============================= Lookup =============================||" << std::endl;
        NAMESPACE::set<char> myset;
        myset.insert('l');
        myset.insert('m');
        myset.insert('n');
        myset.insert('o');
        myset.insert('p');
        printset(myset, __LINE__);
        std::cout << "count of 'o' is: " << myset.count('o') << std::endl;
        //non const
        std::cout << "find of 'p' is: " << *myset.find('p') << std::endl;
        std::cout << "equal range of 'n' is: " << *myset.equal_range('n').first 
        << " to " << *myset.equal_range('n').second << std::endl;
        std::cout << "lower bound of 'm' is: " << *myset.lower_bound ('m') << std::endl;
        std::cout << "upper bound of 'm' is: " << *myset.upper_bound ('m') << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        //const
        const NAMESPACE::set<char> const_myset = myset;
        std::cout << "find of 'p' is: " << *myset.find('p') << std::endl;
        std::cout << "equal range of 'n' is: " << *myset.equal_range('n').first 
        << " to " << *myset.equal_range('n').second << std::endl;
        std::cout << "lower bound of 'm' is: " << *myset.lower_bound ('m') << std::endl;
        std::cout << "upper bound of 'm' is: " << *myset.upper_bound ('m') << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Observer ============================||" << std::endl;
        NAMESPACE::set<char> myset;
        NAMESPACE::set<char>::key_compare mycomp = myset.key_comp();
        myset.insert('a');
        myset.insert('b');
        myset.insert('c');
        std::cout << "myset contains:" << std::endl;
        char highest = *myset.rbegin();
        NAMESPACE::set<char>::iterator it = myset.begin();
        do {
            std::cout << *it << std::endl;
        } while (mycomp((*it++), highest));
        char high;
        std::cout << "myset contains:" << std::endl;
        high = *myset.rbegin();
        it = myset.begin();
        do {
            std::cout << *it << '\n';
        } while ( myset.value_comp()(*it++, high) );
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Operator ============================||" << std::endl;
        NAMESPACE::set<int> set;
        for (int i = 0; i < 10; i++)
            set.insert(i * 2);
        std::cout << "set 1 contain: " << std::endl;
        printset(set, __LINE__);
        NAMESPACE::set<int> set2;
        for (int i = 0; i < 10; i++)
            set2.insert(i + 2);
        std::cout << "set 2 contain: " << std::endl;
        printset(set2, __LINE__);
        std::cout << std::boolalpha;
        std::cout << "M1 == M2?: " << (set == set2) << std::endl;
        std::cout << "M1 != M2?: " << (set != set2) << std::endl;
        std::cout << "M1 < M2?: " << (set < set2) << std::endl;
        std::cout << "M1 <= M2?: " << (set <= set2) << std::endl;
        std::cout << "M1 > M2?: " << (set > set2) << std::endl;
        std::cout << "M1 >= M2?: " << (set >= set2) << std::endl;
        std::cout << "Before swap: " << std::endl;
        std::cout << std::endl;
        printset(set2, __LINE__);
        NAMESPACE::swap(set, set2);
        std::cout << "After swap: " << std::endl;
        printset(set2, __LINE__);
    }
    return 0;
}
