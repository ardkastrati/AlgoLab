#include <iostream>
#include <iomanip>
#include <string>

int main() {
	int t; std::cin >> t;
	for(int i = 0; i < t; i++){
		int a;
		long b;
		std::string c;
		double d;
		std::cin >> a >> b >> c >> d;
		std::cout << std::setprecision(2) << std::fixed << a << " " << b << " " << c << " " << d << std::endl; 
	}
}
