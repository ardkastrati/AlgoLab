#include <stdio.h>
#include <vector>
#include <algorithm>
#include <bitset> 

const int range = 100001;
typedef std::vector<int> VI;
typedef std::bitset<range> BN;

int main() {	
	int N, Q; 
	std::scanf("%d %d", &N, &Q);
	BN dp;
	VI number(N);
	for(int i = 0; i < N; i++) std::scanf("%d", &number[i]);
	dp.set(number[0]);	
	for(int i = 1; i < N; i++) {
		dp = dp | dp << number[i];
		dp.set(number[i]);
	}		

	//prefix sum;
	VI prefix(range, 0);
	for(int i = 1; i < range; i++) {
		prefix[i] = dp.test(i) ? prefix[i-1]+1 : prefix[i-1];
	}

	for(int i = 0; i < Q; i++) {
		int B, E; std::scanf("%d %d", &B, &E);
		std::printf("%d\n", prefix[E] - prefix[B-1]);
	}
}
