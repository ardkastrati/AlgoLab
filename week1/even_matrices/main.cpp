#include <iostream>
#include <vector>

using namespace std;

void testcase() {
	int n; cin >> n;
	vector<vector<int> > matrix(n, vector<int>(n));

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}

	vector<vector<int> > sum(n, vector<int>(n));

	sum[0][0] = matrix[0][0];
	//sum the first row and column
	for(int k = 1; k < n; k++) {
		sum[0][k] = sum[0][k-1] + matrix[0][k];
	       	sum[k][0] = sum[k-1][0] + matrix[k][0];
	}

	//sum the other matrices
	for(int i = 1; i < n; i++) {
		for(int j = 1; j < n; j++) { 
			sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + matrix[i][j];
		}	
	}

	//count evens
	int even = 0;
	for(int i = 0; i < n; i++) {
		for(int j = i; j < n; j++) {
			int current_track_even = 0;
			for(int k = 0; k < n; k++) {
				int s = sum[j][k];
				if(i > 0) s -= sum[i-1][k];
				if(s % 2 == 0) current_track_even++;
			}
			even += current_track_even*(current_track_even - 1)/2 + (n - current_track_even)*(n-current_track_even - 1)/2 + current_track_even;
		}
	}

	cout << even << endl;
}


int main() {
	int t; cin >> t;
	for(int i = 0; i < t; i++) {
		testcase();
	}
	return 0;
}
