#include "rb_tree.hpp"
#include <iostream>

int main() {
	
	ft::rb_tree<int> bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	// bst.insert(25);
	// bst.insert(40);
	// bst.insert(80);
	// bst.deleteNode(25);
	bst.prettyPrint();
	return 0;
}