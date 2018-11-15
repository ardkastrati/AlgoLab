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
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// BGL Graph definitions
// ===================== 
// Graph Type for this specific problem
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, Traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > Graph; 
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type      EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_weight_t >::type       EdgeWeightMap; // new!
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type       ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor          Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor            Edge;
typedef boost::graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator
typedef boost::graph_traits<Graph>::edge_iterator               EdgeIt;         // to iterate over all edges


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
		weightmap[e] = w;
		weightmap[rev_e] = w;
		capacitymap[rev_e] = 0;
		revedgemap[e] = rev_e; 
		revedgemap[rev_e] = e; 
	}
};

void testcase() {
	int n, m, s, f; std::cin >> n >> m >> s >> f;
	const int N = n;
	const int v_source = s;
	const int v_target = f;

	// Create Graph and Maps
	Graph G(N);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

	for(int i = 0; i < m; i++) {
		int a, b, c, d; std::cin >> a >> b >> c >> d;
		eaG.addEdge(a, b, c, d);
		eaG.addEdge(b, a, c, d);
	}

	// Dijkstra shortest paths
	// =======================
	int V = N;
	std::vector<long> distmap1(V);  
	Vertex start = s;
	boost::dijkstra_shortest_paths(G, start, 
			distance_map(boost::make_iterator_property_map(distmap1.begin(), boost::get(boost::vertex_index, G))).
			weight_map(weightmap));

        std::vector<long> distmap2(V);
        start = f;
        boost::dijkstra_shortest_paths(G, start, 
                        distance_map(boost::make_iterator_property_map(distmap2.begin(), boost::get(boost::vertex_index, G))).
                        weight_map(weightmap));

	Graph flowG(N);
	EdgeCapacityMap flowcapacitymap = boost::get(boost::edge_capacity, flowG);
        EdgeWeightMap flowweightmap = boost::get(boost::edge_weight, flowG);
        ReverseEdgeMap flowrevedgemap = boost::get(boost::edge_reverse, flowG);
        ResidualCapacityMap flowrescapacitymap = boost::get(boost::edge_residual_capacity, flowG);
        EdgeAdder floweaG(flowG, flowcapacitymap, flowweightmap, flowrevedgemap);

	// EdgeIterators
        // =============
        EdgeIt ebeg, eend;
        for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg) { 
                Vertex u = source(*ebeg, G);
                Vertex v = target(*ebeg, G);
		if(capacitymap[*ebeg] > 0 && distmap1[u] + weightmap[*ebeg] + distmap2[v] == distmap1[f]) {
			floweaG.addEdge(u, v, capacitymap[*ebeg], 0);
		}
        }
	std::cout <<  boost::push_relabel_max_flow(flowG, v_source, v_target) << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int T; std::cin >> T;
	while(T--) testcase();
	return 0;
}
