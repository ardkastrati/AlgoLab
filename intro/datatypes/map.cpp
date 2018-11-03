#include <iostream>
#include <map>

int main() {
	typedef std::map<int, int> MII;
	MII a;
	
	//modifiers
	//insert
	a[1] = 11;
	a[2] = 22;

	auto ret = a.insert(std::pair<int, int>(3, 33));
	auto it = ret.first;
	std::cout << it->second << std::endl;
	std::cout << a.size() << std::endl;

	for(auto n : a) {
		std::cout << n.first << " -> " << n.second << std::endl;
	}

	auto it2 = a.find(2);
	a.erase(it2, a.end());
	for(auto n : a) {
		std::cout << n.first << " -> " << n.second << std::endl;
	}

	for(int i = 0; i < 20; i++) {
		a[i] = 2*i;
	}	
	for(auto n : a) {
		std::cout << n.first << " -> " << n.second << std::endl;
	}
	
	auto s = a.find(4);
	auto t = a.find(10);
	a.erase(s, t);
	for(auto n : a) {
		std::cout << n.first << " -> " << n.second << std::endl;
	}




}
