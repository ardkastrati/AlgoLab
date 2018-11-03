#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>
#include <set>

typedef std::vector<int> VI;
typedef std::set<int> SI;
typedef std::pair<int, SI> PISI;
typedef std::vector<PISI> DP_TABLE;

int MAX = std::numeric_limits<int>::max();

void f(int k, DP_TABLE& dp, VI& c, VI& v) {
	if(k <= 0) return;
	if(dp[k].first == -1) {
		int best_pos = 0, best_cost = MAX, best_size = 0;
		for(int i = 0; i < c.size(); i++) {
			int curr_pos = std::max(0, k-v[i]);
			f(curr_pos, dp, c, v);
			int curr_cost = dp[curr_pos].first + c[i];
			if(curr_cost < best_cost) { 
				best_pos = i;
				best_cost = curr_cost;
				best_size = dp[curr_pos].second.size();
				if(dp[curr_pos].second.find(i) == dp[curr_pos].second.end()) best_size++;
			} else if(curr_cost == best_cost) {
				int size = dp[curr_pos].second.size();
				if(dp[curr_pos].second.find(i) == dp[curr_pos].second.end()) size++;
				if(best_size < size) {
					best_pos = i;
					best_size = size;
				} 
			} 
		}	
		PISI best = dp[std::max(0, k-v[best_pos])];
		best.second.insert(best_pos);
		best.first += c[best_pos];
		dp[k] = best;
	}
}

void testcase() {
	int n, k; std::cin >> n >> k;
	VI c(n), v(n);
	for(int i = 0; i < n; i++) {
		std::cin >> c[i] >> v[i];
	}
	DP_TABLE dp(k+1, PISI(-1, SI()));
	dp[0] = PISI(0, SI());
	f(k, dp, c, v);
	std::cout << dp[k].first << " " << dp[k].second.size() << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
