#include <iostream>
#include <string>

int main() {
	//Constructor
	std::string test = "Test";
	std::cout << test << std::endl;

	std::string test2("Test2");
	std::cout << test2 << std::endl;

	std::string test3(test);
	std::cout << test3[1] << std::endl;

	std::string test4(test, 1, 2);
	std::cout <<  test4 << std::endl;

	std::string test5(test.begin(), test.begin()+3);
	std::cout << test5 << std::endl;

	std::string test6(42, 'c');
	std::cout << test6 << std::endl;

	std::string test7(test6, 5);
	std::cout << test7 << std::endl;

	//iterators
	for(int i = 0; i < test.length(); i++) {
		std::cout << i << " " << test[i] << std::endl;
	}

	for(auto i : test) {
		std::cout << i << std::endl;
	}
	
	//weird code, just to show what can you do with iterators	
	std::string::iterator it = test.end()--;	
	for(; it != test.begin()-1; it--) {
		std::cout << *it << std::endl;
	}

	if(not test.empty()) {
		std::cout  << "Tested that test is not empty" << std::endl;
	}
}
