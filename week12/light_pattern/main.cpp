#include <iostream>
#include <vector>

typedef std::vector<int> VI;
typedef std::vector<bool> VB;

int get_hamming(VB first, VB second) {
	int counter = 0;
	for(int i = 0; i < first.size(); i++) {
		if(first[i]^second[i]) counter++;
	}
	return counter;
}

void testcase()  {
	int n, k, x; std::cin >> n >> k >> x;
	VB pattern(k, false);
	for(int i = 0; i < k; i++) {
		if(x & 1 << i) {
			pattern[k - i - 1] = true;
		}
	}

	std::vector<VB> data;
	for(int i = 0; i < n/k; i++) {
		VB next(k, false);
		for(int j = 0; j < k; j++) {
			int a; std::cin >> a;
			if(a == 1) {
				next[j] = true;				
			}
		}
		data.push_back(next);
	}	
	
	VI sol(n/k);
	VI sol_rev(n/k);
	int hamming = get_hamming(pattern, data[0]);
	sol[0] = std::min(hamming, k - hamming + 1); 
	sol_rev[0] = std::min(k - hamming, hamming + 1);
		
	for(int i = 0; i < n/k; i++) {
		hamming = get_hamming(pattern, data[i]);	
		sol[i] = std::min(sol[i-1] + hamming, sol_rev[i-1] + (k - hamming) + 1);
		sol_rev[i] = std::min(sol_rev[i-1] + k - hamming, sol[i-1] + 1 + hamming); 
	}
	std::cout << sol[n/k - 1] << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
