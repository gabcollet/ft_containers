/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:40 by gcollet           #+#    #+#             */
/*   Updated: 2022/05/18 12:25:45 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <istream>
#include <memory>
#include <vector>
#include "../includes/vector.hpp"

template<typename T>
void printVector(const ft::vector<T>& vector) {
    for (size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;
}

int main() {

    //* ======================= Is_integral tests =======================
    /* std::cout << std::boolalpha;
    std::cout << "is_integral:" << std::endl;
    std::cout << "char: " << ft::is_integral<char>::value << std::endl;
    std::cout << "int: " << ft::is_integral<int>::value << std::endl;
    std::cout << "float: " << ft::is_integral<float>::value << std::endl; */

    //* ======================= Input iterator constructor tests =======================
//    std::istringstream commetuveux("string");
//    std::istreambuf_iterator<char> it(commetuveux),end;
//	ft::vector<char> vector3(it, end);
//    printVector(vector3);

    //* ======================= Constructor tests =======================
//    ft::vector<std::string> vector;
//     ft::vector<int> vector2 (5);
//    ft::vector<std::string> vector4;

//	ft::vector<std::string> vector_fill(5, "hello");
//    ft::vector<int> vector_range2(5, 3);

//     //* ======================= Method tests =======================
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


    //* ======================= Assign tests =======================
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

    //* ======================= Operator = tests =======================

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

    // *======================= Insert tests =======================
    
   /* ft::vector<int> myvector (3,100);
   ft::vector<int>::iterator it;

   it = myvector.begin();
   it = myvector.insert ( it , 200 );

   // "it" no longer valid, get a new one:
   it = myvector.begin();
   myvector.insert (it,2,300);

   it = myvector.begin();
   ft::vector<int> anothervector (2,400);
   myvector.insert (it+2,anothervector.begin(),anothervector.end());

   int myarray [] = { 501,502,503 };
   myvector.insert (myvector.begin(), myarray, myarray+3);

   // printVector(myvector);
   std::cout << "myvector contains:";
   for (it=myvector.begin(); it<myvector.end(); it++)
       std::cout << ' ' << *it;
   std::cout << '\n'; */

    // *======================= Pop_back tests =======================

    /* ft::vector<int> myvector;
    int sum (0);
    myvector.push_back (100);
    myvector.push_back (200);
    myvector.push_back (300);

    while (!myvector.empty())
    {
        sum+=myvector.back();
        myvector.pop_back();
    }

    std::cout << "The elements of myvector add up to " << sum << '\n'; */

    // *======================= Resize tests =======================
    /* ft::vector<int> vector;
    ft::vector<int>::iterator it;

    it = vector.begin();
    vector.resize(4, 10);
    std::cout << "myvector contains:";
    for (it=vector.begin(); it<vector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n'; */

    // *======================= Swap tests =======================

/*     ft::vector<int> foo (3,100);   // three ints with a value of 100
    ft::vector<int> bar (5,200);   // five ints with a value of 200

    // foo.swap(bar);
    ft::swap(foo, bar);

    std::cout << "foo contains:";
    for (unsigned i=0; i<foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i=0; i<bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << '\n'; */

    

    // *================== Relation Operator tests =====================

   /*  ft::vector<int> foo (3,100);   // three ints with a value of 100
    ft::vector<int> bar (2,200);   // two ints with a value of 200

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n"; */


    // *================== Test a max =====================
    
    ft::vector<int> vec;

    std::vector<int> vec2;

    for (size_t i = 1; i < 14; ++i) {
        vec.push_back(i);
        vec2.push_back(i);
    }
    
    std::cout << "\nSTD_VEC BEFORE Insert ---> Capacity: " << vec2.capacity() << std::endl;
    std::cout << "FT_VEC BEFORE Insert ---> Capacity: " << vec.capacity() << std::endl;

    ft::vector<int>::iterator it = vec.begin();
    std::vector<int>::iterator it2 = vec2.begin();

    vec.insert(it, 4, 42);
    vec2.insert(it2, 4, 42);

    std::cout << "\nSTD_VEC AFTER Insert ---> Capacity: " << vec2.capacity() << std::endl;
    std::cout << "FT_VEC AFTER Insert ---> Capacity: " << vec.capacity() << std::endl;
    // printVector(vec);
    
    return 0;
}
