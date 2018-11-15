// ALGOLAB BGL Tutorial 3
// Code snippets demonstrating 
// - MinCostMaxFlow with arbitrary edge costs using cycle_canceling
// - MinCostMaxFlow with non-negative edge costs using successive_shortest_path_nonnegative_weights

// Compile and run with one of the following:
// g++ -std=c++11 -O2 bgl_mincostmaxflow.cpp -o bgl_mincostmaxflow; ./bgl_mincostmaxflow
// g++ -std=c++11 -O2 -I path/to/boost_1_58_0 bgl_mincostmaxflow.cpp -o bgl_mincostmaxflow; ./bgl_mincostmaxflow

// Includes
// ========
// STL includes
#include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// BGL Graph definitions
// ===================== 
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, Traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > Graph; // new!
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type      EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_weight_t >::type       EdgeWeightMap; // new!
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type       ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor          Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor            Edge;
typedef boost::graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

typedef std::vector<int> VI;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, rev_e;
        boost::tie(e, boost::tuples::ignore) = boost::add_edge(u, v, G);
        boost::tie(rev_e, boost::tuples::ignore) = boost::add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w; // new!
        capacitymap[rev_e] = 0;
        weightmap[rev_e] = -w; // new
        revedgemap[e] = rev_e; 
        revedgemap[rev_e] = e; 
    }
};

void testcase() {
	int n; std::cin >> n;
	VI a(n), c(n), s(n), p(n), v(n-1), e(n-1);
	for(int i = 0; i < n; i++) std::cin >> a[i] >> c[i];
	for(int i = 0; i < n; i++) std::cin >> s[i] >> p[i];
	for(int i = 0; i < n - 1; i++) std::cin >> v[i] >> e[i];

	const int N = n + 2;
	const int v_source = N - 2;
	const int v_target = N - 1;

	// Create Graph and Maps
	Graph G(N);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

	int all_students = 0;
	for(int i = 0; i < n; i++) {
		eaG.addEdge(v_source, i, a[i], c[i]);
		eaG.addEdge(i, v_target, s[i], 20-p[i]);
		if(i != n - 1) eaG.addEdge(i, i+1, v[i], e[i]);	
		all_students += s[i];
	}

	boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
	int cost2 = boost::find_flow_cost(G);
	int s_flow = 0;
	OutEdgeIt estart, eend;
	for(boost::tie(estart, eend) = boost::out_edges(boost::vertex(v_source,G), G); estart != eend; ++estart) s_flow += capacitymap[*estart] - rescapacitymap[*estart];

	if(s_flow == all_students) std::cout << "possible ";
	else std::cout << "impossible ";
	std::cout << s_flow << " " << -(cost2 - 20*s_flow) << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int T; std::cin >> T;
	while(T--) testcase();
	return 0;
}
