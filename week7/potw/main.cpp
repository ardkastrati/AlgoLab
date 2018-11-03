#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

typedef std::vector<int> VI;
typedef std::pair<int, int> PII;
typedef std::vector<PII> VP;

int dfs(VI& graph, int root, VI& visited, int& time) {
	if(root >= graph.size()) return 0;
	if(visited[root] == 1) return 0;
	int a = dfs(graph, 2*root + 1, visited, time);
	int b = dfs(graph, 2*root + 2, visited, time);
	if(time >= graph[root]) return 1;
	visited[root] = 1;	
	time++;
	return std::max(a, b);
}

void testcase() {
	int n; std::cin >> n;
	VI explosion(n);
	VP sorted_explosion(n);
	for(int i = 0; i < n; i++) {
		std::cin >> explosion[i];
		sorted_explosion[i] = std::make_pair(explosion[i], i);
	}
	std::sort(sorted_explosion.begin(), sorted_explosion.end());
	
	int time = 0;
	VI visited(n, 0);
	bool sol = true;
	for(int i = 0; i < n; i++) {
		if(dfs(explosion, sorted_explosion[i].second, visited, time) == 1) {
			sol = false;
			break;
		}	
	}
	if(sol == false) std::cout << "no" << std::endl;
	else std::cout << "yes" << std::endl;
}

int main() {
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
