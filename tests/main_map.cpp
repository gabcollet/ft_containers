#include "rb_tree.hpp"
#include <iostream>
#include <cstdlib>
#include <memory>

int main() {
	
	ft::rb_tree<std::less<int>, int, std::allocator<int> > bst;
	srand(123);
	for (int i = 0; i < 100; i++){
		// std::cout << i << std::endl;
		// bst.treePrint();
		bst.insert(rand() % 100);
	}
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

	srand(345);
	for (int i = 0; i < 50; i++){
		std::cout << i << std::endl;
		bst.treePrint();
		bst.deleteNode(rand() % 100);
	}
	// bst.deleteNode(38);
	// bst.deleteNode(25);
	// bst.deleteNode(1);
	// bst.deleteNode(40);
	// bst.deleteNode(37);
	// bst.deleteNode(80);
	
	// bst.deleteNode(69);
	// bst.deleteNode(420);

	
	return 0;
}
