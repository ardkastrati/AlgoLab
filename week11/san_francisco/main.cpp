#include <iostream>
#include <vector>
#include <tuple>

typedef std::tuple<int, int, int> Edge;
typedef std::vector<Edge> VE;
typedef std::vector<bool> VB;
typedef std::vector<long> VL;
typedef std::vector<VL> DP_TABLE;

void testcase() {
	int n, m; long x; int k; std::cin >> n >> m >> x >> k;
	VE edges(m);
	VB weayaya(n, true);
	for(int i = 0; i < m; i++) {
		int u, v, p; std::cin >> u >> v >> p;
		edges[i] = std::make_tuple(u, v, p);
		weayaya[u] = false;
	}

	DP_TABLE dp(k+1, VL(n, -1));
	dp[0][0] = 0;
	int min = -1;

	for(int i = 1; i <= k && min == -1; i++) {	
		for(int j = 0; j < m; j++) {
			int u, v, p; 
			std::tie(u, v, p) = edges[j];
			if(dp[i-1][u] != -1) {
				dp[i][v] = std::max(dp[i][v], dp[i-1][u] + p);
				if(dp[i][v] >= x) {
					min = i;
				}
			}
		}
		for(int j = 0; j < n; j++) {
			if(weayaya[j] == true) {
				dp[i][0] = std::max(dp[i][0], dp[i][j]);
			}
		}
	}
	/*
	for(int i = 0; i <= k; i++) {
		for(int j = 0; j < n; j++) {
			std::cout << dp[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	if(min == -1) {
		std::cout << "Impossible" << std::endl;
	} else {
		std::cout << min << std::endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int T; std::cin >> T;
	while(T--) testcase();
	return 0;
}

