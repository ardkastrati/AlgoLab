#include <iostream>
#include <array>

int main() {
	typedef std::array<int, 5> Aint5;
	Aint5 a;
	Aint5 b = {};
	Aint5 c = {1,2,3,4,5}

	int d = c[1];
	d = c.at(3);

}
