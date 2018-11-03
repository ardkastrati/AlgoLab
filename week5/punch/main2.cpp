#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>
#include <set>

typedef std::vector<int> VI;
typedef std::set<int> SI;
typedef std::vector<SI> VSI;

int MAX = std::numeric_limits<int>::max();

void testcase() {
	int n, k; std::cin >> n >> k;
	VI c(n), v(n);
	for(int i = 0; i < n; i++) {
		std::cin >> c[i] >> v[i];
	}
	VI dp(k+1, -1);
	dp[0] = 0;
	for(int i = 1; i <= k; i++) {
		int best = MAX;
		for(int i = 0; i < c.size(); i++)  best = std::min(dp[std::max(0, k-v[i])] + c[i], best);
		dp[k] = best;
	} 
	//reconstruct
	VSI dp2(k+1, SI());
	for(int i = 0; i <= k; i++) {
		SI best;
		int best = MAX;
		int best_pos = -1;
		for(int i = 0; i < c.size(); i++) {
			SI* curr = &dp2[std::max(0, k-v[i]];
			int curr_best = curr->size();
			if(curr->find(i) != curr->end()) curr_best++;
			if(curr_best < best) {
				best_pos = i;
				best = curr_best;
			}
		}

	}
	std::cout << dp[k] << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
