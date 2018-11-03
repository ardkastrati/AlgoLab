#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

typedef std::string S;
typedef std::vector<int> VI;
typedef std::vector<VI> VII;

int f(int start, int end, S& word, VII& dp) {
	if (start >= end) return 0;
	if(dp[start][end] == -1) {
		int sol1 = 1 + f(start + 1, end, word, dp);
		int sol2 = 1 + f(start, end - 1, word, dp);
		int sol3 = word[start] == word[end-1] ? f(start+1, end-1, word, dp) : 7000;
		dp[start][end] = std::min(std::min(sol1, sol2), sol3);
	}
	return dp[start][end];
		
}

void testcase() {
	S word; std::cin >> word;
	VII dp(word.size(), VI(word.size()+1, -1)); 
	std::cout << f(0, word.size(), word, dp) << std::endl;
}

int main() {
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
