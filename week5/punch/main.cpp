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
		PISI best(MAX, SI());
		for(int i = 0; i < c.size(); i++) {
			f(k-v[i], dp, c, v);
			PISI current = dp[std::max(0, k-v[i])];
		  	current.second.insert(i);		
			current.first += c[i];
			if(current.first < best.first || (current.first == best.first && current.second.size() > best.second.size())) {
				best = current;
			} 
		}	
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
