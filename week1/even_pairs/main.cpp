#include <iostream>
#include <vector>

using namespace std;



void testcase(){
	int n; cin >> n;
	vector<int> data(n);
	vector<int> sum(n);

	for(int i = 0; i < n; i++) {
		cin >> data[i];
	}

	sum[0] = data[0];
	
	int even = sum[0] % 2 == 0 ? 1 : 0;
	int odd = 1 - even;
	
	for(int i = 1; i < n; i++) {
		sum[i] = sum[i-1] + data[i];
		if(sum[i] % 2 == 0) even++; else odd++;
	}
        cout << even*(even - 1)/2 + odd*(odd - 1)/2 + even << endl;
}

int main() {
	int t; cin >> t;

	for(int i = 0; i < t; i++) {
		testcase();
	}
	return 0;
}
