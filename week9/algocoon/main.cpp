// ALGOLAB BGL Tutorial 3
// Flow example demonstrating
// - breadth first search (BFS) on the residual graph

// Compile and run with one of the following:
// g++ -std=c++11 -O2 bgl_residual_bfs.cpp -o bgl_residual_bfs ./bgl_residual_bfs
// g++ -std=c++11 -O2 -I path/to/boost_1_58_0 bgl_residual_bfs.cpp -o bgl_residual_bfs; ./bgl_residual_bfs

// Includes
// ========
// STL includes
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
// Interior Property Maps
typedef	boost::property_map<Graph, boost::edge_capacity_t>::type		EdgeCapacityMap;
typedef	boost::property_map<Graph, boost::edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	boost::property_map<Graph, boost::edge_reverse_t>::type		ReverseEdgeMap;
typedef	boost::graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	boost::graph_traits<Graph>::edge_descriptor			Edge;
typedef	boost::graph_traits<Graph>::out_edge_iterator			OutEdgeIt;

int MAX = std::numeric_limits<int>::max();

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	void addEdge(int from, int to, long capacity) {
		Edge e, rev_e;
		bool success;
		boost::tie(e, success) = boost::add_edge(from, to, G);
		boost::tie(rev_e, success) = boost::add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[rev_e] = 0;
		revedgemap[e] = rev_e;
		revedgemap[rev_e] = e;
	}
};

void testcase() {
	int n, m; std::cin >> n >> m;

	const int N = n;
	Graph G(N);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	int src = 0;
	for(int i = 0; i < m; i++) {
		int a, b, c; std::cin >> a >> b >> c;
		eaG.addEdge(a, b, c);
	}
	int min_flow = MAX;
	int best = 0;

	for(int i = 1; i < n; i++) {
		int flow = boost::push_relabel_max_flow(G, src, i);
		if(min_flow > flow) {
			min_flow = flow;
			best = i;
		}
	}
	
	for(int i = 1; i < n; i++) {
		int flow = boost::push_relabel_max_flow(G, i, src);
		if(min_flow > flow) {
			min_flow = flow;
			best = -i;
		}
	}

	if(best < 0) {
		best = -best;
	       	std::swap(src, best);
	}
	boost::push_relabel_max_flow(G, src, best);


	// BFS to find vertex set S
	std::vector<int> vis(N, false); // visited flags
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	vis[src] = true; // Mark the source as visited
	Q.push(src);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		OutEdgeIt ebeg, eend;
		for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = boost::target(*ebeg, G);
			// Only follow edges with spare capacity
			if (rescapacitymap[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			Q.push(v);
		}
	}
	std::vector<int> take_home;
	for (int i = 0; i < N; ++i) {
		if (vis[i]) take_home.push_back(i);
	}
	std::cout << min_flow << std::endl;
	std::cout << take_home.size() << " ";
	for(auto a : take_home) std::cout << a << " ";
	std::cout << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
}
