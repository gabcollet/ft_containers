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

	ft::rb_tree<std::less<int>, int, std::allocator<int> > bst;
	ft::rb_tree_iterator<int> it;
	srand(345);
	for (int i = 0; i < 5000; i++){
		// std::cout << i << std::endl;
		// bst.treePrint();
		bst.insert(rand());
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

	// srand(678);
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
	// bst.deleteNode(15);

	bst.treePrint();

	//* ========================= Constructor Test =========================

/* 	ft::map<int, std::string> m1;
	ft::map<int, std::string>::iterator it;	

	// ft::pair<int, std::string> p1(1, "allo");
	// ft::pair<int, std::string> p1(1, "allo");
	// ft::pair<int, std::string> = ft::make_pair(1, "allo");

	// std::cout << std::boolalpha << m1.empty() << std::endl;
	m1.insert(ft::make_pair(1, "allo"));
	it = m1.begin();
	// std::cout << m1.erase(1) << std::endl;
	// m1.erase(it);
	// bool test2 = m1.insert(ft::make_pair(1, "pouet")).second;
	m1[3] = "blabla";
	m1[6] = "blabla";
	// std::cout << std::boolalpha << test2 << std::endl;
	// std::cout << m1[3] << std::endl;

	it = m1.end();
	--it;
	// --it;
	// std::cout << it->second << std::endl; 
	ft::pair<int, std::string> p(5, "test");
	m1.insert(it, p);

	// m1.erase(m1.begin(), m1.end());
	// std::cout << m1.find(3)->second << std::endl;
	const ft::map<int, std::string> m2 = m1;
	// std::cout << m2.at(3) << std::endl;
	std::cout << m1.size() << std::endl;
	std::cout << m1.count(4) << std::endl;
	std::cout << m1.lower_bound(2)->first << std::endl; 
	std::cout << m1.upper_bound(7)->first << std::endl; 
	// std::cout << m1.max_size() << std::endl; */

	//* ========================= Swap Test =========================

/* 	ft::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n'; */

	//* ========================= bound Test =========================

/* 	ft::map<char,int> mymap;
	ft::map<char,int>::iterator itlow,itup;

	mymap['l']=20;
	mymap['m']=40;
	mymap['n']=60;
	mymap['o']=80;
	mymap['p']=100;

	itlow=mymap.lower_bound ('m');  // itlow points to m
	itup=mymap.upper_bound ('o');   // itup points to p (not o!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	std::cout << mymap.size() << std::endl;
	// print content:
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
 */
	return 0;
}
