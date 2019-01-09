#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <boost/functional/hash.hpp>

typedef std::vector<int> Config;
typedef std::vector<int> VI;
typedef std::vector<VI> VII;
typedef std::unordered_map<Config, int, boost::hash<Config> > DP_Table;

int f(Config& config, DP_Table& dp, VII& stacks, int& n) {
	if(dp.find(config) == dp.end()) {
		int max = 0;
		for(int i = 1; i < 1<<n; i++) {
			int value = -1;
			int sum = 0;
  			VI new_config = config;
  			bool allSame = true;
  			for(int j = 0; j < n; j++) {
  				if (i & 1 << j) {
  					if(config[j] > 0) {
						if(value == -1) {
							value = stacks[j][config[j] - 1];
						} else  {
							allSame &= stacks[j][config[j] - 1] == value;
						}
						sum++;
						new_config[j]--;
  					} else {
  						allSame = false;
  					}
  				}
  			}
  			if(allSame) {
  				max = std::max(max, f(new_config, dp, stacks, n) + (sum == 1 ? 0 : 1 << (sum - 2)));
  			}
		}
		dp[config] = max;
	}
	return dp[config];
}

void testcase() {
	int n; std::cin >> n;
	VI size(n);
	for(int i = 0; i < n; i++) std::cin >> size[i];
	VII stacks(n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < size[i]; j++) {
			int c; std::cin >> c;
			stacks[i].push_back(c);
		}
	}
	DP_Table dp;
	Config start;
	for(int i = 0; i < n; i++) start.push_back(size[i]);
	Config end(n, 0);
	dp[end] = 0;
	std::cout << f(start, dp, stacks, n) << std::endl; 
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
