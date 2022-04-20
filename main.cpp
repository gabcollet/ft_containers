/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:40 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/19 14:48:25 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector.hpp>
#include <iterator.hpp>
#include <utils.hpp>
#include <istream>
#include <sstream>

template<typename T>
void printVector(const ft::vector<T>& vector) {
    for (size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;
}

int main(){

	/* std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl; */

//    std::istringstream commetuveux("string");
//    std::istreambuf_iterator<char> it(commetuveux),end;
//	ft::vector<char> vector3(it, end);

	ft::vector<std::string> vector;
//    printVector(vector3);

//	ft::vector<int> vector2;
//	ft::vector<std::string> vector_fill(5, "hello");


    vector.push_back("hello");
//	vector.push_back(" ");
//	vector.push_back("world");
//	vector.push_back("!");

//    vector.clear();
    vector.erase(vector.begin() + 1);
//    vector.erase(vector.begin(), vector.end());
//	ft::vector<std::string> vector_copy(vector);

//    vector2.push_back(1);
//    vector2.push_back(2);
//    vector2.push_back(3);
//	vector2.push_back(4);

//    ft::vector<int> vector_range2(5, 3);

    printVector(vector);
//    printVector(vector2);
//    printVector(vector_fill);
//    ft::vector<std::string> vector_range(&vector[0], &vector[3]);
//    printVector(vector_range);
//    printVector(vector_copy);
//    printVector(vector_range2);
    return 0;
}
