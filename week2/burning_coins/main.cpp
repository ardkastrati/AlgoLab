#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;

int f(int a, int b, VI& coin, VI& prefix, VII& dp) {
	if(dp[a][b] == -1) {
		int win1 = coin[a] + prefix[b+1] - prefix[a+1] - f(a+1, b, coin, prefix, dp);
		int win2 = coin[b] + prefix[b] - prefix[a] - f(a, b-1, coin, prefix, dp);	
		dp[a][b] = std::max(win1, win2);
	}	
	return dp[a][b];
}

void testcase() {
	int n; std::cin >> n;
	VI coin(n);
	for(int i = 0; i < n; i++) {
		std::cin >> coin[i];
	}
	VI prefix(n+1, 0);
	for(int i = 1; i <= n; i++) {
		prefix[i] = prefix[i-1] + coin[i-1];	
	}

	VII dp(n, VI(n, -1));
	for(int i = 0; i < n; i++) dp[i][i] = coin[i];	
	std::cout << f(0, n-1, coin, prefix, dp) << std::endl;	
}

int main() {
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) {
		testcase();
	}
	return 0;
}
