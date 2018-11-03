#include <iostream>
#include <deque>

int main() {
	typedef std::deque<int> DI;
	DI a;
	std::cout << a.size() << std::endl;

	DI b(10, 2);
	for(int i = 0; i < b.size(); i++) {
		std::cout << b[i] << " ";
	}	
	std::cout << std::endl;

	DI c(b.begin(), b.begin() + 7);
	for(int i = 0; i < c.size(); i++) {
		std::cout << c[i] << " ";
	}	
	std::cout << std::endl;

	//from array
	int myArray[] = {1,2,3,4,5,6,7,8};
	DI e(myArray, myArray + sizeof(myArray) / sizeof(int) );
	for(int i = 0; i < e.size(); i++) {
		std::cout << e[i] << " ";
	}	
	std::cout << std::endl;
	
	//move (acquire)
	DI f(e);
	for(int i = 0; i < f.size(); i++) {
		std::cout << f[i] << " ";
	}	
	std::cout << std::endl;
	f[5] = 2;
	for(int i = 0; i < f.size(); i++) {
		std::cout << f[i] << " ";
	}	
	std::cout << std::endl;
	
	//modifiers
	f.push_back(1000);
	f.push_front(-1000);
	for(int i = 0; i < f.size(); i++) {
		std::cout << f[i] << " ";
	}	
	std::cout << std::endl;
		

}
