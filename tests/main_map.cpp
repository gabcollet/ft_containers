#include "rb_tree.hpp"
#include <iostream>
#include <cstdlib>

int main() {
	
	ft::rb_tree<std::less<int>, int> bst;
	srand(123);
	for (int i = 0; i < 50; i++){
		bst.insert(rand() % 50);
	}
	// bst.insert(11);
	// bst.insert(18);
	// bst.insert(18);

	// bst.insert(15);
	// bst.insert(17);
	// bst.insert(25);
	// bst.insert(40);
	// bst.insert(18);
	// bst.insert(80);
	// bst.insert(3);
	// bst.insert(1);
	// bst.insert(2);
	// bst.deleteNode(25);
	bst.treePrint();
	return 0;
}
