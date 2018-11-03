#include <iostream>
#include <string>

int main(){
	/*
	//read integers and output their sum
	int sum = 0;
	int n; std::cin >> n;
	for(int i=0; i < n; i++){
		int a; std::cin >> a;
		sum += a;
	}

	std::cout << "The sum is: " << sum << std::endl;
	*/

	//read a string
	std::string name;
	std::cout << "Write your name: ";
	std::cin >> name;
	std::cout << "Hello " << name << "!" << std::endl;
}
