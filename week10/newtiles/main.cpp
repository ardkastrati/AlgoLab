#include <iostream>
#include <vector>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;

void testcase() {
	int h, w; std::cin >> h >> w;
	VII floor(h, VI(w, 0));
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			std::cin >> floor[i][j];
		}
	}
	int num_bitmasks = 1 << w;	
	VII dp(h, VI(num_bitmasks, 0));

	for(int i = 1; i < h; i++) {
		for(int j = 0; j < num_bitmasks; j++) dp[i][0] = std::max(dp[i][0], dp[i-1][j]);	
		for(int j = 1; j < num_bitmasks; j++) {
			int bitmask = j;	
			int negated_bitmask = num_bitmasks - bitmask - 1;
			int counter = 0;
			int squares = 0;
			int max = 0;
			int compatible = true;
			for(int k = 0; k < w && compatible; k++) {
				if(bitmask & 1 << k) {
					if(floor[i][k] == 1 && floor[i-1][k] == 1) {
						counter++;
					} else {
						compatible = false;
					}
					max = std::max(max, dp[i][bitmask - (1<<k)]);
				} else {
					if(counter%2 == 1) {
						compatible = false;
					} else {
						squares += counter/2;
						counter = 0;
					}
				}
			}
			if(counter%2 == 1) compatible = false;

			if(compatible) {
				dp[i][j] = std::max(max, dp[i-1][negated_bitmask] + squares);
			} else {
				dp[i][j] = max;
			}
		}
	}
	std::cout << dp[h-1][num_bitmasks-1] << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
