#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> VI;

void testcase() {
	int n; std::cin >> n;
	VI parasol(n);
	for(int i = 0; i < n; i++) {
		std::cin >> parasol[i];
	}
	std::sort(parasol.begin(), parasol.end());
	
	int i = 0, j = 1;
	int best_max = 1, best_min = 0;
	int max = 1, min = 0;

	while(j < n) {
		if(parasol[j] - parasol[i] <= 200) {
			max++;
			min = (parasol[j] - parasol[i])/2 + (parasol[j] - parasol[i])%2;			
			j++;
			if (max >= best_max) {
				if(max > best_max)
					best_min = min;
				else 
					best_min = std::min(best_min, min);
				best_max = max;	
			}
		} else {
			i++;
			max--;
			if(i == j) {
				j++;
				max++;
			}
		}
	}
	std::cout << best_max << " " << best_min << std::endl;

	for(int i = 0; i < n - best_max + 1; i++) {
		int a = parasol[i + best_max - 1], b = parasol[i];
		min = (a - b)/2 + (a - b)%2;
		if(min == best_min) {
			if((a + b)%2 == -1) std::cout << (a + b)/2 - 1 << " "; 
			std::cout << (a + b)/2 << " ";
			if((a + b)%2 == 1) std::cout << (a + b)/2 + 1 << " ";
		}	
	}
	std::cout << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t > 0) {
		testcase();
		t--;
	}
	return 0;
}
