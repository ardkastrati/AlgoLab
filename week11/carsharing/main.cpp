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
#include <map>
#include <set>
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
typedef std::map<int, int> Map;
typedef std::set<int> Set;

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

int testcase() {
	int N, S; std::cin >> N >> S;
	VI l(S);
	int s_flow = 0;
	for(int i = 0; i < S; i++) {
		std::cin >> l[i];
		s_flow += l[i];
	}
	VI s(N), t(N), d(N), a(N), p(N);
	Set times;
	for(int i = 0; i < N; i++) {
		std::cin >> s[i] >> t[i] >> d[i] >> a[i] >> p[i];
		s[i] -= 1;
		t[i] -= 1;
		times.insert(d[i]);
		times.insert(a[i]);
	}
	int counter = 0;
	Map timesMap;
	for (auto it = times.begin(); it != times.end(); ++it) {
		timesMap[*it] = counter;
		counter++;
	}

	// Create Graph and Maps
	Graph G(S*timesMap.size() + 2);
	int v_source = S*timesMap.size();
	int v_target = S*timesMap.size() + 1;

	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

	for(int i = 0; i < S; i++) {
		eaG.addEdge(v_source, i, l[i], 0);
	}
	VI need(S*timesMap.size(), 0);
	for(int i = 0; i < S; i++) {
		eaG.addEdge(S*(timesMap.size() - 1) + i, v_target, 1000, 0);
		need[S*(timesMap.size() - 1) + i] = 1;
	}


	//Requests
	for(int i = 0; i < N; i++) {
		eaG.addEdge(S*timesMap[d[i]] + s[i], S*timesMap[a[i]] + t[i], 1, 100*(timesMap[a[i]] - timesMap[d[i]]) - p[i]);
		need[S*timesMap[d[i]] + s[i]] = 1;
		need[S*timesMap[a[i]] + t[i]] = 1;
	}

	for(int i = 0; i < S; i++) {
		for(int j = 0; j < timesMap.size() - 1; j++) {
			int pos = j;
			while(need[S*(j + 1) + i] == 0) {
				j++;
			}
			eaG.addEdge(S*pos + i, S*(j + 1) + i, 1000, 100*(j + 1 - pos));
		}
	}

	// Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights
	boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
	int cost2 = boost::find_flow_cost(G);

	std::cout << s_flow*100*(timesMap.size() - 1) - cost2 << std::endl;

	return 0;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}

