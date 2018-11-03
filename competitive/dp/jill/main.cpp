#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::pair<int, int> PII;
typedef std::vector<PII> VPII;

int testcase(int t) {
	int s; std::cin >> s;
	VI nice(s);
	for(int i = 1; i < s; i++) {
		std::cin >> nice[i];
	}

	VPII sol(s);
	sol[s-1] = std::make_pair(nice[s-1], 1);
	for(int i = s-2; i > 0; i--) {
		sol[i] = std::max(std::make_pair(nice[i], 1), std::make_pair(nice[i] + sol[i+1].first, sol[i+1].second + 1));
	}
	for(int i = 1; i < s; i++) {
		std::cout << sol[i].first << " " << sol[i].second << std::endl;
	}
	auto nicest = std::max_element(sol.begin() + 1, sol.end());
	int pos = std::distance(sol.begin(), nicest);
	if(nicest->first > 0) std::cout << "The nicest part of route " << t << " is between stops " << pos << " and " << pos + nicest->second << std::endl;
	else std::cout << "Route " << t << " has no nice parts" << std::endl; 	

	return 0;
}


int main() {
	int b; std::cin >> b;
	for(int i = 1; i <= b; i++) {
		testcase(i);
	}
	return 0;
}
