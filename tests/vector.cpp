/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:02:03 by gcollet           #+#    #+#             */
/*   Updated: 2022/06/10 11:24:30 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <limits>

#include "vector.hpp"
#include <vector>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template<typename T>
void printVector(const NAMESPACE::vector<T>& vector, int line) {
    std::cout << "line: " << line << std::endl;
    for (size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << " ";
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

int main()
{
    std::cout << "||==================================================================||" << std::endl;
    std::cout << "||                          -VECTOR TEST-                           ||" << std::endl;
    std::cout << "||==================================================================||" << std::endl;
    {
        std::cout << std::endl;
        std::cout << "||========================== Constructor ===========================||" << std::endl;
        //default constructor
        NAMESPACE::vector<int> vector;
        printVector(vector, __LINE__);
        //empty constructor
        NAMESPACE::vector<std::string, std::allocator<std::string> > empty_vec;
        printVector(empty_vec, __LINE__);
        //fill constructor
        NAMESPACE::vector<int> fill_vector(5, 42);
        printVector(fill_vector, __LINE__);
        //range constructor
        for (int i = 0; i < 10; i++)
            vector.push_back(i);
        NAMESPACE::vector<int>::iterator it = vector.begin();
        NAMESPACE::vector<int>::iterator ite = vector.end();
        NAMESPACE::vector<int> range_vector(it, ite);
        printVector(range_vector, __LINE__);
        //copy constructor
        NAMESPACE::vector<int> copy_vector(range_vector);
        printVector(copy_vector, __LINE__);
        std::cout << std::endl;
        std::cout << "||======================= Assignment operator ======================||" << std::endl;
        std::cout << "before assigment :" << std::endl;
        printVector(copy_vector, __LINE__);
        copy_vector = fill_vector;
        std::cout << "after assigment :" << std::endl;
        printVector(copy_vector, __LINE__);
    }
    {
        std::cout << std::endl;
        std::cout << "||========================== Get allocator =========================||" << std::endl;
        NAMESPACE::vector<int> vector;
        int *p;
        unsigned int i;
        p = vector.get_allocator().allocate(5);
        for (i = 0; i < 5; i++) 
            vector.get_allocator().construct(&p[i],i);
        std::cout << "line: " << __LINE__ << std::endl;
        std::cout << "The allocated array contains:";
        for (i = 0; i < 5; i++) 
            std::cout << ' ' << p[i];
        std::cout << std::endl;
        for (i=0; i<5; i++) 
            vector.get_allocator().destroy(&p[i]);
        vector.get_allocator().deallocate(p,5);
    }
    {
        std::cout << std::endl;
        std::cout << "||========================= Element access =========================||" << std::endl;
        //non const
        NAMESPACE::vector<int> vector;
        for (int i = 0; i < 10; i++)
            vector.push_back(i + 42);
        printVector(vector, __LINE__);
        std::cout << "Element at 2 is: " << vector.at(2) << std::endl;
        std::cout << "Element at 9 is: " << vector.at(9) << std::endl;
        std::cout << "Front element is: " << vector.front() << std::endl;
        std::cout << "Back element is: " << vector.back() << std::endl;
        std::cout << "Element [8] is: " << vector[8] << std::endl;
        std::cout << "Element [0] is: " << vector[0] << std::endl;
        int *p = vector.data();
        *p = 12345;
        std::cout << "After data(), element [0] is now: " << vector[0] << std::endl;
        std::cout << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        //const
        const NAMESPACE::vector<int> const_vector = vector;
        printVector(const_vector, __LINE__);
        std::cout << "Element at 2 is: " << const_vector.at(2) << std::endl;
        std::cout << "Element at 9 is: " << const_vector.at(9) << std::endl;
        std::cout << "Front element is: " << const_vector.front() << std::endl;
        std::cout << "Back element is: " << const_vector.back() << std::endl;
        std::cout << "Element [8] is: " << const_vector[8] << std::endl;
        std::cout << "Element [0] is: " << const_vector[0] << std::endl;
        const int *const_p = const_vector.data();
        std::cout << "Const element [0] cannot be modified and it still: " << *const_p << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Iterators ===========================||" << std::endl;
        //non const
        NAMESPACE::vector<float> vector;
        for (int i = 0; i < 10; i++)
            vector.push_back(i + 3.1416 / i);
        printVector(vector, __LINE__);
        NAMESPACE::vector<float>::iterator it;
        it = vector.begin();
        std::cout << "Iterator begin is: " << *it << std::endl;
        it = vector.end();
        --it;
        std::cout << "Iterator --end is: " << *it << std::endl;
        std::cout << std::endl;
        //const
        NAMESPACE::vector<float>::const_iterator cit;
        cit = vector.begin();
        std::cout << "Const_iterator begin is: " << *cit << std::endl;
        cit = vector.end();
        --cit;
        std::cout << "Const_iterator --end is: " << *cit << std::endl;
        std::cout << std::endl;
        //reverse non const
        NAMESPACE::vector<float>::reverse_iterator rit;
        rit = vector.rbegin();
        std::cout << "Reverse iterator rbegin is: " << *rit << std::endl;
        rit = vector.rend();
        --rit;
        std::cout << "Reverse iterator --rend is: " << *rit << std::endl;
        std::cout << std::endl;
        //reverse const
        NAMESPACE::vector<float>::const_reverse_iterator rcit;
        rcit = vector.rbegin();
        std::cout << "Reverse const_iterator begin is: " << *rcit << std::endl;
        rcit = vector.rend();
        --rcit;
        std::cout << "Reverse const_iterator --rend is: " << *rcit << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Capacity ============================||" << std::endl;
        NAMESPACE::vector<std::string> vector;
        printVector(vector, __LINE__);
        std::cout << std::boolalpha;
        std::cout << "Is empty?: " << vector.empty() << std::endl;
        std::cout << std::endl;
        vector.push_back("helloworld");
        printVector(vector, __LINE__);
        std::cout << "Is empty?: " << vector.empty() << std::endl;
        vector.assign(42, "Hello");
        printVector(vector, __LINE__);
        std::cout << "Size is: " << vector.size() << std::endl;
        std::cout << "Max size is: " << vector.max_size() << std::endl;
        std::cout << "Capacity is: " << vector.capacity() << std::endl;
        vector.push_back("world");
        std::cout << "Capacity after push_back is: " << vector.capacity() << std::endl;
        vector.reserve(10);
        std::cout << "Capacity after invalid reserve: " << vector.capacity() << std::endl;
        vector.reserve(100);
        std::cout << "Capacity after valid reserve: " << vector.capacity() << std::endl;
        vector.resize(50, "world");
        printVector(vector, __LINE__);
        std::cout << "Size after larger resize is: " << vector.size() << std::endl;
        vector.resize(30, "world");
        printVector(vector, __LINE__);
        std::cout << "Size after smaller resize is: " << vector.size() << std::endl;
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Modifier ============================||" << std::endl;
        NAMESPACE::vector<double> vector;
        NAMESPACE::vector<double> vector2;
        NAMESPACE::vector<double>::iterator it;
        printVector(vector, __LINE__);
        vector.assign(42, 42.42);
        printVector(vector, __LINE__);
        it = vector.begin();
        vector.assign(it, it + 10);
        printVector(vector, __LINE__);
        vector.clear();
        printVector(vector, __LINE__);
        for (int i = 0; i < 15; i++)
            vector.push_back(i + 42);
        printVector(vector, __LINE__);
        vector.pop_back();
        printVector(vector, __LINE__);
        vector.erase(vector.begin());
        printVector(vector, __LINE__);
        vector.erase(vector.begin(), vector.begin() + 5);
        printVector(vector, __LINE__);
        vector.insert(vector.begin() + 4, 11111.2);
        printVector(vector, __LINE__);
        vector.insert(vector.end(), 5, 42);
        vector2 = vector;
        printVector(vector, __LINE__);
        vector.insert(vector.begin(), vector.begin() + 3, vector.end() - 3);
        printVector(vector, __LINE__);
        std::cout << "Before swap: " << std::endl;
        printVector(vector2, __LINE__);
        vector2.swap(vector);
        std::cout << "After swap: " << std::endl;
        printVector(vector2, __LINE__);
    }
    {
        std::cout << std::endl;
        std::cout << "||============================ Operator ============================||" << std::endl;
        NAMESPACE::vector<int> vector;
        for (int i = 0; i < 5; i++)
            vector.push_back(i);
        std::cout << "Vector 1 contain: " << std::endl;
        printVector(vector, __LINE__);
        NAMESPACE::vector<int> vector2;
        for (int i = 0; i < 5; i++)
            vector2.push_back(i + 1);
        std::cout << "Vector 2 contain: " << std::endl;
        printVector(vector2, __LINE__);
        std::cout << std::boolalpha;
        std::cout << "V1 == V2?: " << (vector == vector2) << std::endl;
        std::cout << "V1 != V2?: " << (vector != vector2) << std::endl;
        std::cout << "V1 < V2?: " << (vector < vector2) << std::endl;
        std::cout << "V1 <= V2?: " << (vector <= vector2) << std::endl;
        std::cout << "V1 > V2?: " << (vector > vector2) << std::endl;
        std::cout << "V1 >= V2?: " << (vector >= vector2) << std::endl;
        std::cout << "Before swap: " << std::endl;
        std::cout << std::endl;
        printVector(vector2, __LINE__);
        NAMESPACE::swap(vector, vector2);
        std::cout << "After swap: " << std::endl;
        printVector(vector2, __LINE__);
    }
    return 0;
}
