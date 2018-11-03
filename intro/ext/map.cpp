#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
	typedef vector<int> vi;
	
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) {
		int q; std::cin >> q;
		std::map<std::string, vi> mapping;
		for (int j = 0; j < q; j++) {
			int a;
			std::string b;
			std::cin >> a >> b;
			if (a == 0) {
				mapping.erase(b);	
			} else {
				if (mapping.find(b) != mapping.end()) {
					mapping[b].push_back(a);
				} else {
					vector<int> v;
					v.push_back(a);
					mapping[b] = v;
				}
			}
		}
		string test; cin >> test;
		if (mapping.find(test) == mapping.end()) {
			cout << "Empty" << endl;
		} else {
			vi vec = mapping[test];
			sort(vec.begin(), vec.end());
			for(auto n : vec) {
				cout << n << " ";
			}
			cout << endl;
		}
	}
}
