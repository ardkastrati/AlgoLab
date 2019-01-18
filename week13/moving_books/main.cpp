#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::multiset<int, std::greater<int> > MI;

void testcase() {
	int n, m; std::cin >> n >> m;
	VI s(n);
       	MI w;

	int max_s = 0, max_w = 0;
	for(int i = 0; i < n; i++) {
		std::cin >> s[i];
		max_s = std::max(max_s, s[i]);
	}
	for(int i = 0; i < m; i++) {
		int a; std::cin >> a;
		w.insert(a);
		max_w = std::max(max_w, a);
	}
	if(max_w > max_s) {
		std::cout << "impossible" << std::endl;
		return;
	}
	std::sort(s.begin(), s.end(), std::greater<int>());

	int r = 0;
	while(!w.empty()) {
		r++;

		for(int i = 0; i < n; i++) {
			auto it = w.lower_bound(s[i]);
			if(it != w.end()) {
				w.erase(it);
			} else {
				break;
			}
		}
	}
	std::cout << 3*r - 1 << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}

