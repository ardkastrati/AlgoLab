#include <iostream>
#include <vector>

typedef std::vector<int> VI;

int main() {
	VI a; // default constructor
	std::cout << a.size() << std::endl;

	VI b(10, 7);
	std::cout << b.size() << std::endl;
	for(int i = 0; i < b.size(); i++) {
		std::cout << b[i] << ", ";
	}
	std::cout << std::endl;

	VI c(b.begin(), b.end());
	for(int i = 0; i < c.size(); i++) {
		std::cout << c[i] << " ";
	}
	std::cout << std::endl;

	//copy from array
	int myArray[] = {1, 2, 4, 8, 16};
	VI d(myArray, myArray + sizeof(myArray)/sizeof(int));
	for(int i = 0; i < d.size(); i++) {
		std::cout << d[i] << " ";
	}
	std::cout << std::endl;

	VI e(d);
	for(int i = 0; i < e.size(); i++) {
		std::cout << e[i] << " ";
	}
	std::cout << std::endl;

	//methods
	//size,  resize, capacity, empty, reserve
	std::cout << e.size() << std::endl;
	e.resize(10, 7);
	for(int i = 0; i < e.size(); i++) {
		std::cout << e[i] << " ";
	}
	std::cout << std::endl;
	std::cout << e.capacity() << std::endl;	
	e.push_back(111);
	std::cout << e.capacity() << std::endl;

	VI f;
	f.reserve(123);
	std::cout << f.capacity() << std::endl;

	//access methods: [], at, front, back
	
	std::cout << e[4] << std::endl;
	std::cout << e.at(1) << std::endl;
	std::cout << e.back() << std::endl;
	std::cout << e.front() << std::endl;

	//modifiers
	e.push_back(456);	
	std::cout << e.back() << " " << e.size() << std::endl;
	e.pop_back();
	std::cout << e.back() << " " << e.size() << std::endl;

	e.insert(e.begin() + 2, b.begin(), b.end());
	for(int i = 0; i < e.size(); i++) { 
		std::cout << e[i] << " ";
	}
	std::cout << std::endl;

	e.erase(e.begin() + 5);
	for(int i = 0; i < e.size(); i++) { 
		std::cout << e[i] << " ";
	}
	std::cout << std::endl;

	e.erase(e.begin() + 1, e.begin() + 7);
	for(int i = 0; i < e.size(); i++) { 
		std::cout << e[i] << " ";
	}
	std::cout << std::endl;

	e.clear();
	std::cout << e.size() << std::endl;

	VI test = {1,2,3,4,5};
	for(int i = 0; i < test.size(); i++) { 
		std::cout << test[i] << " ";
	}
	std::cout << std::endl;
}
