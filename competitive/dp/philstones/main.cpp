#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;


int testcase() {
	int h, w; std::cin >> h >> w;
	VII matrix(h, VI(w, 0));
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			std::cin >> matrix[i][j];
		}
	}	

	for(int i = h-2; i >= 0; i--) {
		for(int j = 0; j < w; j++) {
			int left = j-1 >= 0 ? matrix[i+1][j-1] : 0;
			int down = matrix[i+1][j];
			int right = j+1 < w ? matrix[i+1][j+1] : 0;
			matrix[i][j] += std::max(std::max(left, down), right);
		}
	}
	auto max = std::max_element(matrix[0].begin(), matrix[0].end());
	std::cout << *max << std::endl;
}

int main() {
	int T; std::cin >> T;
	while(T--) testcase();
	return 0;
}
