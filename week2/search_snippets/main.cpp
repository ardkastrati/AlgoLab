#include <iostream>
#include <utility>
#include <vector>
#include <set>

using namespace std;
typedef vector<int> VI;
typedef vector<VI > VVI;
typedef pair<int, int> PII;
typedef set<pair<int, int> > SI;

void testcase() {
	int n; cin >> n;
	VI m(n, 0);
	for(int i = 0; i < n; i++) {
		cin >> m[i];
	}

	VVI data(n);	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m[i]; j++) {
			int c; cin >> c;
			data[i].push_back(c);	
		}
	}	
	
	SI acc;
	for(int i = 0; i < n; i++) {
		acc.insert(std::make_pair(data[i][0], i));
	}

	bool still = true;
	int best_size = (1 << 30) + 1;
	VI next(n, 1);

	while(still) {
		int size = acc.rbegin()->first - acc.begin()->first + 1;
		if(size < best_size) best_size = size;

		int i = acc.begin()->second;
		if(next[i] >= data[i].size()) break;
		acc.erase(acc.begin());
		acc.insert(std::make_pair(data[i][next[i]], i));
		next[i]++;
	}
	cout << best_size << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for(int i = 0; i < t; i++) {
		testcase();
	}
	return 0;
}
