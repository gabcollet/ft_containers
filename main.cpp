/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:08:40 by gcollet           #+#    #+#             */
/*   Updated: 2022/04/12 14:07:36 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "vector.hpp"
#include "iterator.hpp"
#include "utils.hpp"

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

//	typedef ft::vector<std::string>::iterator stringIterator;

	ft::vector<std::string> vector;
	ft::vector<std::string> vector_fill(5, "hello");
//	ft::vector<std::string> vector_range(vector[0], vector[2]);
//	ft::vector<std::string> vector_copy(vector_fill);
	

	vector.push_back("hello");
	vector.push_back(" ");
	vector.push_back("world");
	vector.push_back("!");

    printVector(vector);
    printVector(vector_fill);
//    printVector(vector_range);
	return 0;
}
