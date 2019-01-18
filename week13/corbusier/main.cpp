#include <iostream>
#include <vector>

typedef std::vector<int> VI;

void testcase() {
	int n, i, k; std::cin >> n >> i >> k;
	VI possible(k, 0);

	for(int i = 0; i < n; i++) {
		int d; std::cin >> d;
		VI new_possible(k);
		for(int j = 0; j < k; j++) {
			if(possible[j] == 1) new_possible[(j + d) % k] = 1;
		}

		possible[d%k] = 1;

		for(int j = 0; j < k; j++) {
			possible[j] = std::max(possible[j], new_possible[j]);
		}
	}

	if(possible[i] == 1) {
		std::cout << "yes" << std::endl;
	} else {
		std::cout << "no" << std::endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;	
	while(t--) testcase();
	return 0;
}

