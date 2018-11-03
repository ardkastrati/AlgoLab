#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<std::pair<int, int> > VPII;
int MAX = std::numeric_limits<int>::max();

void testcase() {
	int n; std::cin >> n;
	VPII boat(n);
	for(int i = 0; i < n; i++) {
		int a, b; std::cin >> a >> b;
		boat[i] = std::make_pair(b, a);
	}
	std::sort(boat.begin(), boat.end());

	int left = boat[0].first;
	int sol = 1;
	int curr_best = MAX;
	for(int i = 1; i < boat.size(); i++) {
		int pos = boat[i].first, length = boat[i].second;
		if(pos >= curr_best) {
			sol++;
			left = curr_best; 
			curr_best = MAX;
		}
		int new_best = left + length < pos ? pos : left + length;
		curr_best = std::min(curr_best, new_best);		
	}
	if(curr_best != MAX) sol++;
	std::cout << sol << std::endl;
}

int main() {
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
