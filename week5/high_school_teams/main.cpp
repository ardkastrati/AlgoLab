#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <map>
#include <cmath>

typedef std::vector<int> VI;
typedef std::pair<int, int> P;
typedef std::vector<P> VP;
typedef std::map<P, int> MPI;

void subset_sum(VI& skill, MPI& config, int N) {
	int max = std::pow(3, N);
	for(int s = 0; s < max; ++s) {
		int sum = 0, k = 0;
		int curr = s;
		for(int i = 0; i < N; i++) {
			if(curr % 3 == 0) k++;
			else if(curr % 3 == 1) sum += skill[i];
			else if(curr % 3 == 2) sum -= skill[i];
			curr /= 3;
		}
		P config_data(sum, k);
		if(config.find(config_data) == config.end()) {
			config[config_data] = 1;
		} else {
			config[config_data] += 1;
		}
	}
}

void testcase() {
	int n, k; std::cin >> n >> k;
	VI skill1(n/2), skill2(n - n/2);
	for(int i = 0; i < n; i++) {
		if(i < n/2) std::cin >> skill1[i];
		else std::cin >> skill2[i - n/2]; 
	}
	MPI config1, config2;
	subset_sum(skill1, config1, skill1.size());	
	subset_sum(skill2, config2, skill2.size());
	
	long long int solution = 0;
	for(auto it = config1.begin(); it != config1.end(); ++it) {
		int sum = it->first.first, non_player = it->first.second;
		for(int i = 0; i <= k - non_player; i++) {
			if(config2.find(std::make_pair(-sum, i)) != config2.end()) {
				solution += it->second * config2[std::make_pair(-sum, i)];	
			}
		}
	}
	std::cout << solution << std::endl;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
