#include <iostream>
#include <vector>
#include <map>

typedef std::vector<int> VI;
typedef std::tuple<int, int, int, int> Tuple;
typedef std::map<Tuple, int> Map;

void brute_force(Map& m, VI& l, int length) {
	int n = (int) l.size();
	//Split and List
	for(int s = 0; s < 1 << n; s++) {
		for(int s2 = 0; s2 < 1 << n; s2++) {
			int side0 = 0, side1 = 0, side2 = 0, side3 = 0;
			for(int i = 0; i < n; i++) {
				if(s & 1 << i) {
					if(s2 & 1 << i) {
						//side3
						side3 += l[i];
					} else {
						//side2
						side2 += l[i];
					}
				} else {
					if(s2 & 1 << i) {
						//side1
						side1 += l[i];

					} else {
						//side0
						side0 += l[i];
					}
				}
			}
			Tuple t;
			if(length == -1) {
				t = Tuple(side0, side1, side2, side3);
			} else {
				t = Tuple(length - side0, length - side1, length - side2, length - side3);
			}
			if(m.find(t) == m.end()) {
				m[t] = 1;
			} else {
				m[t] += 1;
			}
		}
	}	
}

void testcase() {
	int n; std::cin >> n;
	VI l1(n/2);
	VI l2(n - n/2);
	int sum = 0;
	for(int i = 0; i < n/2; i++) {
		std::cin >> l1[i];
		sum += l1[i];
	}
	for(int i = 0; i < n - n/2; i++) {
		std::cin >> l2[i];
		sum += l2[i];
	}

	int length = sum / 4;
	Map m1, m2;
	brute_force(m1, l1, -1);
	brute_force(m2, l2, length);
	long solution = 0;
	for(Map::iterator it = m1.begin(); it != m1.end(); it++) {
		if(m2.find(it->first) != m2.end()) {
			solution += it->second * m2[it->first];
		}
	}
	std::cout << solution/24 << std::endl;
}	


int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
