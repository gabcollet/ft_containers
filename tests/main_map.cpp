#include "map.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"
#include "rb_tree_iterator.hpp"
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <memory>

int main() {
	
    //* ========================= RBTree test =========================

/* 	ft::rb_tree<std::less<int>, int, std::allocator<int> > bst;
	ft::rb_tree_iterator<int> it;
	// srand(123);
	// for (int i = 0; i < 100; i++){
	// 	// std::cout << i << std::endl;
	// 	// bst.treePrint();
	// 	bst.insert(rand() % 100);
	// }
	// bst.insert(11);
	// bst.insert(18);
	// bst.insert(15);
	// bst.insert(17);
	// bst.insert(25);
	// bst.insert(40);
	// bst.insert(80);
	// bst.insert(3);
	// bst.insert(1);
	// bst.insert(2);
	// bst.insert(39);
	// bst.insert(38);
	// bst.insert(37);

	// srand(123);
	// for (int i = 0; i < 50; i++){
	// 	std::cout << i << std::endl;
	// 	bst.treePrint();
	// 	bst.deleteNode(rand() % 100);
	// }
	// bst.deleteNode(38);
	// bst.deleteNode(25);
	// bst.deleteNode(1);
	// bst.deleteNode(15);
	// bst.deleteNode(40);
	// bst.deleteNode(37);
	// bst.deleteNode(80);
	bst.deleteNode(15);

	bst.treePrint(); */

	//* ========================= Constructor Test =========================

	ft::map<int, std::string> m1;
	ft::map<int, std::string>::iterator it;	

	// ft::pair<int, std::string> p1(1, "allo");
	// ft::pair<int, std::string> p1(1, "allo");
	// ft::pair<int, std::string> = ft::make_pair(1, "allo");

	// std::cout << std::boolalpha << m1.empty() << std::endl;
	bool test = m1.insert(ft::make_pair(1, "allo")).second;
	it = m1.begin();
	m1.erase(it);
	bool test2 = m1.insert(ft::make_pair(1, "pouet")).second;
	m1[3] = "blabla";
	std::cout << std::boolalpha << test << std::endl;
	std::cout << std::boolalpha << test2 << std::endl;
	// std::cout << m1[3] << std::endl;

	it = m1.end();
	--it;
	--it;
	ft::pair<int, std::string> p(2, "test");
	m1.insert(it, p);
	// std::cout << it->second << std::endl; 

	// std::cout << m1.find(3)->second << std::endl;
	const ft::map<int, std::string> m2 = m1;
	std::cout << m2.at(3) << std::endl;
	std::cout << m1.size() << std::endl;
	// std::cout << m1.max_size() << std::endl;


	return 0;
}
