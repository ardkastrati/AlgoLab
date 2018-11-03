#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <utility>
#include <limits>
#include <map>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;
typedef std::pair<int, int> P;
typedef std::vector<P> VP;
typedef std::vector<VP> VVP;
typedef std::map<VI, int> MVI;

int MAX = std::numeric_limits<int>::max();

void subset_sum(VVP& light, MVI& config, int N, int M) {
	for(int s = 0; s < 1 << N; ++s) {
		VI lights(M, 0);
		int count = 0;
		for(int i = 0; i < N; i++) {
			if(s & 1<<i) {
				count++;
				for(int j = 0; j < M; j++) lights[j] += light[i][j].second;
			} else {
				for(int j = 0; j < M; j++) lights[j] += light[i][j].first;
			}
		}
		if(config.find(lights) == config.end()) {
			config[lights] = count;
		} else {
			config[lights] = std::min(count, config[lights]);
		}
	}
}

void testcase() {
	int N, M; std::cin >> N >> M;
	VI b(M);
	for(int i = 0; i < M; i++) std::cin >> b[i];
	VVP light1(N/2, VP(M));
	VVP light2(N - N/2, VP(M));
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			int a, b; std::cin >> a >> b;
			if(i < N/2) light1[i][j] = std::make_pair(a, b);
			else light2[i - N/2][j] = std::make_pair(a,b);
		}
	}
	MVI config1, config2;
	subset_sum(light1, config1, light1.size(), M);	
	subset_sum(light2, config2, light2.size(), M);

	int best = MAX;
	for(auto it = config1.begin(); it != config1.end(); ++it) {
		VI current = it->first;
		VI must(M);
		for(int i = 0; i < M; i++) {
			must[i] = b[i] - current[i];
		}
		if(config2.find(must) != config2.end()) {
			best = std::min(best, it->second + config2[must]);
		}
	}
	if(best == MAX) std::cout << "impossible" << std::endl;
	else std::cout << best << std::endl;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
