#include <iostream>
#include <list>

int main() {
	typedef std::list<int> LI;

	LI a;
	std::cout << a.size() << std::endl;

	LI b(10, -1);
	for(auto it = b.begin(); it != b.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	LI c(b.begin(), b.end());
	for(auto n : c) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	LI d = {1,2,3,4,5,6,7};
	for(auto n : d) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	//methods push_front, pop_front, push_back, pop_back easy
	//now insert, erase - modifiers
	auto it = d.begin();
	d.insert(++it, -1);
	d.insert(it, 99);
	std::cout << *it << std::endl;
	for(auto n : d) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	auto it1 = d.begin();
	auto it2 = d.begin();
	it2++;
	d.erase(it1, it2);
	for(auto n : d) {
		std::cout << n << " ";
	}
	std::cout << std::endl;
	std::cout << *it1 << " " << *it2 << std::endl; //interesting!!!

	//operatins based on the value!
	d.remove(3);
	d.insert(d.end(), 10, 1);
	d.push_back(2);
	d.unique();
	for(auto n : d) {
		std::cout << n << " ";
	}
	std::cout << std::endl;
		
}
