#include <iostream>
#include <iomanip>

int main() {
	double a, b, c;
	a = 3.1415926534;
	b = 2006.0;
	c = 1.0e-10;
	std::cout << std::setprecision(3);
	std::cout << a << '\t' << b << '\t' << c << std::endl;
	std::cout << std::fixed << a << '\t' << b << '\t' << c << std::endl;
	std::cout << std::scientific << a << '\t' << b << '\t' << c << std::endl;
}
