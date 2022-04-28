/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:40 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/27 19:11:12 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <istream>
#include <memory>
#include <vector>
#include <vector.hpp>

template<typename T>
void printVector(const ft::vector<T>& vector) {
    for (size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;
}

int main() {

    //* ======================= Is_integral test =======================
    /* std::cout << std::boolalpha;
    std::cout << "is_integral:" << std::endl;
    std::cout << "char: " << ft::is_integral<char>::value << std::endl;
    std::cout << "int: " << ft::is_integral<int>::value << std::endl;
    std::cout << "float: " << ft::is_integral<float>::value << std::endl; */

    //* ======================= Input iterator constructor test =======================
//    std::istringstream commetuveux("string");
//    std::istreambuf_iterator<char> it(commetuveux),end;
//	ft::vector<char> vector3(it, end);
//    printVector(vector3);

    //* ======================= Constructor test =======================
//    ft::vector<std::string> vector;
//     ft::vector<int> vector2 (5);
//    ft::vector<std::string> vector4;

//	ft::vector<std::string> vector_fill(5, "hello");
//    ft::vector<int> vector_range2(5, 3);

//     //* ======================= Method test =======================
//    vector.push_back("hello");
//    vector.push_back(" ");
//    vector.push_back("world");
//    vector.push_back("!");
//    vector.push_back("!");
//
//    vector.clear();
//    vector.erase(vector.begin() + 1);
//    vector.erase(vector.begin() + 1, vector.end() - 1);

//    vector.push_back("hello");
//    vector.push_back(" ");
//    vector.push_back("world");
//    vector.push_back("!");
//    vector.push_back("!");
   
//	ft::vector<std::string> vector_copy(vector);
//
//    vector2.push_back(1);
//    vector2.push_back(2);
//    vector2.push_back(3);
// 	vector2.push_back(4);

    // int i = 0;

    // ft::vector<int>::reverse_iterator rit = vector2.rbegin();
    // for (; rit!= vector2.rend(); ++rit)
    //     *rit = ++i;
    // printVector(vector2);

//    int* p = vector2.data();
//    *p = 10;
//    ++p;
//    *p = 20;
//    p[2] = 100;
//    printVector(vector2);
//
//    std::cout << vector2.at(0) << std::endl;
//    vector2.front() += vector2.back();
//    std::cout << vector2.at(0) << std::endl;

//    ft::vector<std::string>::iterator it;
//    vector4.assign(vector.begin() + 1, vector.end());
//    vector.assign(5, "hello");
//    vector4.reserve(100);
//    vector2.assign(5, 42);
//    std::cout << vector.at(0) << std::endl;
//
//    printVector(vector);
//    printVector(vector4);
//    printVector(vector2);
//    printVector(vector_fill);
//    ft::vector<std::string> vector_range(&vector[0], &vector[3]);
//    printVector(vector_range);
//    printVector(vector_copy);
//    printVector(vector_range2);


    //* ======================= Assign test =======================
//    {
//        ft::vector<int> first;
//        ft::vector<int> second;
//        ft::vector<int> third;
//
//        first.assign(7, 100);             // 7 ints with a value of 100
//
//
//        ft::vector<int>::iterator it;
//        it = first.begin() + 1;
//
//        second.assign(it, first.end() - 1); // the 5 central values of first
//
//        int myints[] = {1776, 7, 4};
//        third.assign(myints, myints + 3);   // assigning from array.
//
//        std::cout << "Size of first: " << int(first.size()) << '\n';
//        std::cout << "Size of second: " << int(second.size()) << '\n';
//        std::cout << "Size of third: " << int(third.size()) << '\n';
//
//        ft::vector<char> characters;
//
//        characters.assign(5, 'a');
//        printVector(characters);
//
//        const std::string extra(6, 'b');
//        characters.assign(extra.begin(), extra.end());
//        printVector(characters);
//    }

    //* ======================= Operator = test =======================

//    ft::vector<int> foo (3,0);
//    ft::vector<int> bar (5,0);
//
//    bar = foo;
//    foo = ft::vector<int>();
//
//    std::cout << "Size of foo: " << int(foo.size()) << '\n';
//    std::cout << "Size of bar: " << int(bar.size()) << '\n';

/*ft::vector<int> vec;
ft::vector<int>::iterator x = vec.begin();
    ft::vector<int>::const_iterator y = x;*/

    // *======================= Insert = test =======================
    
//    ft::vector<int> myvector (3,100);
//    ft::vector<int>::iterator it;
//
//    it = myvector.begin();
//    it = myvector.insert ( it , 200 );
//
//    // "it" no longer valid, get a new one:
//    it = myvector.begin();
//    myvector.insert (it,2,300);
//
//    it = myvector.begin();
//    ft::vector<int> anothervector (2,400);
//    myvector.insert (it+2,anothervector.begin(),anothervector.end());
//
//    int myarray [] = { 501,502,503 };
//    myvector.insert (myvector.begin(), myarray, myarray+3);
//
//    // printVector(myvector);
//    std::cout << "myvector contains:";
//    for (it=myvector.begin(); it<myvector.end(); it++)
//        std::cout << ' ' << *it;
//    std::cout << '\n';

    // *======================= Pop_back = test =======================

    ft::vector<int> myvector;
    int sum (0);
    myvector.push_back (100);
    myvector.push_back (200);
    myvector.push_back (300);

    while (!myvector.empty())
    {
        sum+=myvector.back();
        myvector.pop_back();
    }

    std::cout << "The elements of myvector add up to " << sum << '\n';


    return 0;
}
