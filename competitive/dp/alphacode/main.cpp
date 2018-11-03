#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

typedef std::string S;
typedef std::vector<long long> VI;

int main() {	
	S enc; std::cin >> enc;
	while(enc[0] != '0') {
		VI dp(enc.size() + 2, 1);	
		dp[enc.size() + 1] = 0;
		for(int i = enc.size() - 1; i >= 0; i--) {
			if(enc[i] != '0') {
				dp[i] = dp[i+1];
				int number = (enc[i] - '0')*10 + (enc[i+1] - '0');
				if(number <= 26) {
					dp[i] += dp[i+2];
				}
			} else {
				dp[i] = 0;
			}
		}
		std::cout << dp[0] << std::endl;

		std::cin >> enc;
	}
	return 0;
}
