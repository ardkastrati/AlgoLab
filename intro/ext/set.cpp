#include <iostream>
#include <set>

int main() {
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) {
		int q; std::cin >> q;
		std::set<int> theSet;
		for(int j = 0; j < q; j++) {
			int a, b; std::cin >> a >> b;
			if(a == 0) {
				theSet.insert(b);
			} else {
				theSet.erase(b);
			}
		}
		if (theSet.empty()) {
			std::cout << "Empty" << std::endl;
		} else {
			for(auto n : theSet) {
				std::cout << n << " ";
			}
			std::cout << std::endl;
		}
	}
}
