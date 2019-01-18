#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <deque>
#include <string>

typedef std::vector<int> VI;
typedef std::string S;
typedef std::map<int, int> MII;
typedef std::map<S, int> MSI;
typedef std::map<int, S> MIS;

typedef std::vector<VI> Graph;
typedef std::deque<int> DI;
typedef std::vector<DI> VDI;

void dfs(Graph& G, int root, VI& path, VDI& query, VDI& solution, MII& species_age) {
	path.push_back(root);
	//Here handle queries
	for(auto q : query[root]) {
		//Binary search the solution
		int lmin = 0, lmax = path.size() - 1;
		while (lmin != lmax) {
			int p = (lmin + lmax)/2;
			if (species_age[path[p]] > q)
				lmin = p + 1;
			else
				lmax = p;
		}
		solution[root].push_back(path[lmin]);
	}
	for(auto neighbor : G[root]) {
		dfs(G, neighbor, path, query, solution, species_age);
	}
	path.pop_back();
}

void testcase() {
	int n, q; std::cin >> n >> q;
	MII species_age;
	MSI species_id;
	MIS species_rev_id;
	int root = 0; int old = 0;
	for(int i = 0; i < n; i++) {
		S s; std::cin >> s;
		int a; std::cin >> a;
		species_age[i] = a;
		species_id[s] = i;
		species_rev_id[i] = s;
		if(a > old) {
			root = i;
			old = a;
		}
	}

	Graph G(n);
	for(int i = 0; i < n-1; i++) {
		S s, p; std::cin >> s >> p;
		G[species_id[p]].push_back(species_id[s]);
	}

	VDI query(n), solution(n);
	VI queries_ordered(q);
	for(int i = 0; i < q; i++) {
		S s; std::cin >> s;
		int b; std::cin >> b;
		query[species_id[s]].push_back(b);
		queries_ordered[i] = species_id[s];
	}
	VI path;
	dfs(G, root, path, query, solution, species_age);
	for(auto q : queries_ordered) {
		std::cout << species_rev_id[solution[q].front()] << " ";
		solution[q].pop_front();
	}
	std::cout << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}

