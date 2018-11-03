#include <iostream>
#include <set>

int main() {
	typedef std::set<int> SI;
	typedef std::pair<SI::iterator, bool> RET;

	SI a;
	std::cout << a.size() << std::endl;

	SI b = {1,2,3,4,5};
	SI c(b.begin(), ++b.begin());
	std::cout << c.size() << std::endl;

	int myInt[] = {1,2,3,4,5,6};
	SI d(myInt, myInt + 4);
	std::cout << d.size() << std::endl;

	//modifiers
	RET ret = d.insert(28);
	std::cout << *ret.first << " " << ret.second << std::endl;	

	RET ret2 = d.insert(28);
	std::cout << *ret2.first << " " << ret2.second << std::endl;	

	auto it = d.begin();
	it++;
	d.erase(it);
	d.erase(5);

	for (auto n : d) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	auto it2 = d.find(4);
	auto it1 = d.begin();
	d.erase(it1, it2);
	
	for (auto n : d) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	for(int i = 0; i < 24; i++) {
		d.insert(i);
	}
	for (auto n : d) {
		std::cout << n << " ";
	}
	std::cout << std::endl;
	
	auto itlow = d.lower_bound(5);
	auto itup = d.upper_bound(10);
	d.erase(itlow, itup);

	for (auto n : d) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	for(int i = 0; i < 10; i++) {
	}
}
