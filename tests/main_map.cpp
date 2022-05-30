#include "map.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"
#include "rb_tree_iterator.hpp"
#include <iostream>
#include <cstdlib>
#include <memory>

int main() {
	
    //* ========================= RBTree test =========================

	ft::rb_tree<std::less<int>, int, std::allocator<int> > bst;
	ft::rb_tree_iterator<int> it;
	// srand(123);
	// for (int i = 0; i < 100; i++){
	// 	// std::cout << i << std::endl;
	// 	// bst.treePrint();
	// 	bst.insert(rand() % 100);
	// }
	bst.insert(11);
	bst.insert(18);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.insert(3);
	bst.insert(1);
	bst.insert(2);
	bst.insert(39);
	bst.insert(38);
	bst.insert(37);

	// srand(123);
	// for (int i = 0; i < 50; i++){
	// 	std::cout << i << std::endl;
	// 	bst.treePrint();
	// 	bst.deleteNode(rand() % 100);
	// }
	bst.deleteNode(38);
	bst.deleteNode(25);
	bst.deleteNode(1);
	bst.deleteNode(15);
	bst.deleteNode(40);
	bst.deleteNode(37);
	bst.deleteNode(80);
	bst.deleteNode(11);

	bst.treePrint();

	//* ========================= Constructor Test =========================

	/* ft::map<int, std::string> m1;
	ft::map<int, std::string>::iterator it;	

	// ft::pair<int, std::string> p1(1, "allo");
	// ft::pair<int, std::string> p1(1, "allo");
	// ft::pair<int, std::string> = ft::make_pair(1, "allo");

	bool test = m1.insert(ft::make_pair(1, "allo")).second;
	bool test2 = m1.insert(ft::make_pair(1, "pouet")).second;
	std::string str = m1[2] = "blabla";
	std::cout << std::boolalpha << test << std::endl;
	std::cout << std::boolalpha << test2 << std::endl;
	std::cout << str << std::endl; */

	return 0;
}
