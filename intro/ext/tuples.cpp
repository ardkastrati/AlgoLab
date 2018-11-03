#include <iostream>
#include <tuple>
#include <string>
#include <utility>

int main() {
	std::pair<int, int> p1(0, 1);
	std::cout << p1.first << " " << p1.second << std::endl;
	std::pair<int, std::string> p2(3, "three");

	std::tuple<double, std::string, int, char> t(3.14, "Pi", 1, 'c');
	std::cout << std::get<0>(t) << " " << std::get<1>(t) << " " 
		  << std::get<2>(t) << " " << std::get<3>(t) << std::endl;
}
