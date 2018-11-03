#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef std::vector<int> VI;
typedef std::set<int> SI;
typedef std::vector<VI> VII;
typedef std::vector<SI> Graph;

int dfs(int root, Graph& G, VI& visited, VI& left, int counter, VI& topo_order) {
	visited[root] = counter++;
	for(auto el : G[root]) {
		if(visited[el] == -1) {
			counter = dfs(el, G, visited, left, counter, topo_order);
		}
	}
	left[root] = counter++;
	topo_order.push_back(root);
	return counter;
}

int testcase() {
	int n, m, v; std::cin >> n >> m >> v;
	Graph G(n);
	for(int i = 0; i < m; i++) {
		int a, b; std::cin >> a >> b;
		G[a].insert(b);
		G[b].insert(a);
	}

	int counter = 0;
	VI visited(n, -1), left(n, -1);
	VI topo_order;
	dfs(v, G, visited, left, counter, topo_order);	

	for(int i = 0; i < n; i++)
		std::cout << visited[i] << " ";
	std::cout << std::endl;	
	for(int i = 0; i < n; i++)	
		std::cout << left[i] << " ";
	std::cout << std::endl;	

	std::reverse(std::begin(topo_order), std::end(topo_order));
	for(auto e : topo_order) {
		std::cout << e << " ";
	}	
	std::cout << std::endl;
}

int main() {
	int T; std::cin >> T;
	while(T--) testcase();
}
