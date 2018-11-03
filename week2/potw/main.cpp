#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double calc_probability(int money, int phase, vector<vector<double> >& memo, int n, int m, vector<double>& probability) {

	if(money >= m) return 1;
	if(phase >= n) return 0;
	if(memo[phase][money] != -1) return memo[phase][money];

	double prob = calc_probability(money, phase + 1, memo, n, m, probability);

	for(int i = 1; i <= money; i++) {
		double current = (1 - probability[phase]) * calc_probability(money - i, phase + 1, memo, n, m, probability);
		double current2 = probability[phase] * calc_probability(money + i, phase + 1, memo, n, m, probability);
		if (current + current2 > prob) prob = current + current2;
	}
	memo[phase][money] = prob;	

	return prob;
}

void testcase() {
	int n, k, m; cin >> n >> k >> m;

	vector<double> probability(n);
	for(int i = 0; i < n; i++) {	
		cin >> probability[i];
	}

	vector<vector<double> > memo(n, vector<double>(m+1, -1));
	cout << std::fixed << std::setprecision(5);
	cout << calc_probability(k, 0, memo, n, m, probability) << endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		testcase();
	}
	return 0;
}
