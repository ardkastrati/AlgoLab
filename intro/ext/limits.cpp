#include <limits>
#include <iostream>

int main() {
	std::cout << "type\tmin()\t\t\tmax()\t\t\t#binary digits\n";
	std::cout << "int\t"
		  << std::numeric_limits<int>::min() << "\t\t"
		  << std::numeric_limits<int>::max() << "\t\t"
		  << std::numeric_limits<int>::digits << "\n";

	std::cout << "long\t"
		  << std::numeric_limits<long>::min() << "\t"
		  << std::numeric_limits<long>::max() << "\t"
		  << std::numeric_limits<long>::digits << "\n"; 
	std::cout << "double\t"
		  << std::numeric_limits<double>::min() << "\t\t"
		  << std::numeric_limits<double>::max() << "\t\t"
		  << std::numeric_limits<double>::digits << "\n";
	return 0;
}
