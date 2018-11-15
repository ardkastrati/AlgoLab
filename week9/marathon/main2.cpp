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

bool too_big(int lmax, Graph& G, int v_source, int v_target, int one_cost, Edge& e, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap) {
	capacitymap[e] = lmax;
	capacitymap[revedgemap[e]] = 0;
	boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
	int cost = boost::find_flow_cost(G);
	if(cost == one_cost*lmax) return false;
	else return true;
}

void testcase() {
	int n, m, s, f; std::cin >> n >> m >> s >> f;
	const int N = n + 1;
	const int v_source = N;
	const int v_target = f;

	// Create Graph and Maps
	Graph G(N);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);


	int max_flow = 0;
	for(int i = 0; i < m; i++) {
		int a, b, c, d; std::cin >> a >> b >> c >> d;
		eaG.addEdge(a, b, c, d);
		eaG.addEdge(b, a, c, d);
		max_flow += c;
	}
	eaG.addEdge(v_source, s, 1, 0);
	Edge control;
	boost::tie(control, boost::tuples::ignore) = boost::edge(v_source, s, G);

	boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
	int init_cost = boost::find_flow_cost(G);
	int init_flow = capacitymap[control] - rescapacitymap[control];

	if(init_flow == 0) {
		std::cout << 0 << std::endl;
		return;
	}

	int lmin = 1, lmax = 2;
	while(!too_big(lmax, G, v_source, v_target, init_cost, control, capacitymap, revedgemap) && lmax < max_flow) lmax *= 2;

	while(lmin != lmax) {
		int p = (lmin+lmax+1)/2;
		if(too_big(p, G, v_source, v_target, init_cost, control, capacitymap, revedgemap)){
		       	lmax = p-1;
		} else {
			lmin = p;
		}
	}
	std::cout << lmin << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int T; std::cin >> T;
	while(T--) testcase();
	return 0;
}
