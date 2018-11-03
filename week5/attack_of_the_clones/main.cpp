#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <limits>

typedef std::vector<int> VI;
typedef std::pair<int, int> PII;
typedef std::vector<PII> VP;

int MAX = std::numeric_limits<int>::max();

void generate_segments(VP& segments, int pos, int m, VP& new_segments, VP& over_pos_segments) {
	for(auto el : segments) {
		int first = el.first - pos + 1 > 0 ? el.first - pos + 1: el.first + m - pos + 1; 
		int second = el.second - pos + 1 > 0 ? el.second - pos + 1: el.second + m - pos + 1;
		if(second <= first) {
			new_segments.push_back(std::make_pair(first, second));
		} else {
			over_pos_segments.push_back(std::make_pair(first, second));
		}
	}
	std::sort(new_segments.begin(), new_segments.end());
}

int find_pos(VP& point, int s) {
	int last_pos = 1, curr_size = s;
	int best_pos = -1;
	int i = 0;
	while(i < point.size()) {
		int curr_pos = point[i].first;
		if(curr_pos - last_pos > 0 && curr_size <= 10) {
				best_pos = curr_pos;
				break;
		}
		while(i < point.size() && point[i].first == curr_pos && point[i].second == 0) {
			curr_size++;
			i++;
		}
		if(curr_size <= 10) {
			best_pos = curr_pos;
			break;
		}
		while(i < point.size() && point[i].first == curr_pos && point[i].second == 1) {
			curr_size--;
			i++;
		}
		last_pos = curr_pos + 1;
	}
	return best_pos;
}

void testcase() {
	int n, m; std::cin >> n >> m;
	VP point;
	VP segments;
	int s = 0;
	for(int i = 0; i < n; i++) {
		int a, b; std::cin >> a >> b;
		if(a > b) s++;
		point.push_back(std::make_pair(a, 0));
		point.push_back(std::make_pair(b, 1));
		segments.push_back(std::make_pair(b, a));
	}
	std::sort(point.begin(), point.end());
	int pos = find_pos(point, s);

	VP new_segments, over_pos_segments;
	generate_segments(segments, pos, m, new_segments, over_pos_segments);	
	//Greedy
	int best_sol = 0;
	for(int i = -1; i < (int) over_pos_segments.size(); i++) {
		int left = 0, right = m+1;
		int curr_sol = 0;
		if(i != -1) {
			left = over_pos_segments[i].first;
			right = over_pos_segments[i].second;
			curr_sol++;
		}	
		for(auto el : new_segments) {
			if(el.second > left && el.first < right) {
				curr_sol++;
				left = el.first;
			}
		}	
		best_sol = std::max(curr_sol, best_sol); 
	}
	std::cout << best_sol << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
