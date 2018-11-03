#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> VI;

int testcase() {
	int n; std::cin >> n;
	VI v(n);	
	for(int i = 0; i < n; i++) {
		std::cin >> v[i];
	}
	int x; std::cin >> x;
	if(x == 0) {
		std::sort(v.begin(), v.end());
	} else {
		std::sort(v.begin(), v.end(), std::greater<int>());
	}

	for(int i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int main() { 
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) {
		testcase();
	}
}

