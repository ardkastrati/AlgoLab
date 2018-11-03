#include <iostream>
#include <queue>
#include <set>
#include <vector>


typedef std::vector<int> VI;
typedef std::vector<std::set<int> > GRAPH;
typedef std::queue<int> QI;

int testcase() {
	int n, m, v; std::cin >> n >> m >> v;
	GRAPH g(n);
	for(int i = 0; i < m; i++) {
		int a, b; std::cin >> a >> b;
		g[a].insert(b);
		g[b].insert(a);
	}

	QI q;
	q.push(v);
	int timestamp = 0;
	VI distance(n, -1);
	distance[v] = 0; 

	while(not q.empty()) {
		int current = q.front();
		q.pop();

		for(auto it = g[current].begin(); it != g[current].end(); it++) {
			if(distance[*it] == -1) {
				distance[*it] = distance[current] + 1;
				q.push(*it);
			}
		}
	}

	for(int i : distance) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int main() {
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) {
		testcase();
	}
}
