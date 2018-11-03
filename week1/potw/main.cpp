#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> VI;

void testcase() {
	int n, k; std::cin >> n >> k;
	VI numbers(n);
	for(int i = 0; i < n; i++) {
		std::cin >> numbers[i];
	}

	int i = 0;
	int j = 0;
	int sum = numbers[0];

	int best_i = 0;
	int best_j = 0;
	int best_sum = numbers[0];

	while(i < n) {
		if(sum < k) {
			if(j < n) {
				j++;
				sum += numbers[j];
			} else {
				i++;
			}
		} else if (sum == k) {
			best_sum = k;
			best_i = i;
			best_j = j;
			break;
		} else {
			sum -= numbers[i];
			i++;
			if(i > j) {
				j++;
				sum += numbers[j];
			}
		}
		if(std::abs(sum - k) < std::abs(best_sum - k)) {
			best_i = i;
			best_j = j;
			best_sum = sum;
		}	
	}
	std::cout << best_i << " " << best_j << std::endl;
}

int main() { 
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) {
		testcase();
	}
	return 0;
}
