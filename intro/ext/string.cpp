#include <iostream>
#include <algorithm>
#include <string>

int main() {
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) {
		std::string a, b;
	       	std::cin >> a >> b;
		std::cout << a.length() << " " << b.length() << "\n";
		std::cout << a << b << std::endl;
		std::reverse(a.begin(), a.end());
		std::reverse(b.begin(), b.end());
		char t = a[0];
		a[0] = b[0];
		b[0] = t;
		std::cout << a << " " <<  b << std::endl;
	}	
}
