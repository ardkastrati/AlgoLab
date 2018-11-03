#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;


int f(int pos, int player, VII& dp, VII& graph) {
	if(dp[pos][player] == -1) {
		int best;
		if(player == 0) {
			best = 50000;
			for(int i = 0; i < graph[pos].size(); i++) {
				best = std::min(best, 1 + f(graph[pos][i], 1, dp, graph));
			}	
		} else {
			best = 0;
			for(int i = 0; i < graph[pos].size(); i++) {
				best = std::max(best, 1 + f(graph[pos][i], 0, dp, graph));
			}
		}
		dp[pos][player] = best;
	}
	return dp[pos][player];
}

void testcase() {
	int n, m; std::cin >> n >> m;
	int r, b; std::cin >> r >> b;
	VII graph(n+1, VI(0));
	for(int i = 0; i < m; i++) {
		int a, b; std::cin >> a >> b;
		graph[a].push_back(b);
	}

	VII dp(n+1, VI(2, -1));
	dp[n][0] = dp[n][1] = 0;
       	f(r, 0, dp, graph);
	f(b, 0, dp, graph);	

	if(dp[r][0] < dp[b][0]) {
		std::cout << 0 << std::endl;
	} else if(dp[r][0] > dp[b][0]) {
		std::cout << 1 << std::endl;	
	} else {
		if(dp[r][0] % 2 == 0) {
			std::cout << 1 << std::endl; 
		} else {
			std::cout << 0 << std::endl;
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) {
		testcase();
	}
	return 0;
}
