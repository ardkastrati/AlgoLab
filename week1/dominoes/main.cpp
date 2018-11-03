#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void testcase() {
	int n; cin >> n;
	vector<int> dominos(n);
	for(int i = 0; i < n; i++) {
		cin >> dominos[i];
	}
	
	int fall = 1;
	int right = dominos[0] - 1;
	for(int i = 1; i < n; i++) {
		if(right > 0) fall++; else break;
		right = max(right - 1, dominos[i] - 1);	
	}
	cout << fall << endl;
}

int main() {
	int t; cin >> t;
	for(int i = 0; i < t; i++) {
		testcase();
	}
	return 0;
}
