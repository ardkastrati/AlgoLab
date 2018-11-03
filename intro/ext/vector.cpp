#include <iostream>
#include <vector>

int main() {
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) {
		int n; std::cin >> n;
		std::vector<int> v(n);
		for(int j = 0; j < n; j++) {
			std::cin >> v[j];
		}
		int d; std::cin >> d;
		if (!v.empty()) v.erase(v.begin() + d);
		int a, b; std::cin >> a >> b;
		if (!v.empty()) v.erase(v.begin()+a, v.begin()+b+1);
		if (v.empty()) {
			std::cout << "Empty" << std::endl;
		} else {
			for(int k = 0; k < v.size(); k++) {
				std::cout << v[k] << " ";
			}
			std::cout << std::endl;
		}
	}
}
