#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;
typedef std::vector<std::pair<int, int> > VPII;

typedef std::vector<VI> Graph;

void dfs(int root, 
	 Graph& G, VI& dfs_num, VI& dfs_low, VI& dfs_parent, VPII& critical_bridges, 
	 int& counter) {

	dfs_num[root] = dfs_low[root] = counter++;
	for(auto el : G[root]) {
		if(dfs_num[el] == -1) {
			dfs_parent[el] = root;
			dfs(el, G, dfs_num, dfs_low, dfs_parent, critical_bridges, counter);
			if(dfs_low[el] > dfs_num[root]) critical_bridges.push_back(std::make_pair(std::min(root, el), std::max(root, el)));
			dfs_low[root] = std::min(dfs_low[root], dfs_low[el]);
		} else if (el != dfs_parent[root]) {
			dfs_low[root] = std::min(dfs_low[root], dfs_num[el]);
		}
	}
}

int testcase() {
	int n, m; std::cin >> n >> m;
	Graph G(n);
	for(int i = 0; i < m; i++) {
		int a, b; std::cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	VPII critical_bridges;

	int counter = 0;
	VI dfs_num(n, -1);
	VI dfs_low(n, -1);
	VI dfs_parent(n, -1);
	
	if(n > 0) dfs(0, G, dfs_num, dfs_low, dfs_parent, critical_bridges, counter);	

	std::sort(critical_bridges.begin(), critical_bridges.end());
	std::cout << critical_bridges.size() << std::endl;
	for(auto el : critical_bridges) {
		std::cout << el.first << " " << el.second << std::endl;
	}
}

int main() {
	int T; std::cin >> T;
	while(T--) testcase();
}
