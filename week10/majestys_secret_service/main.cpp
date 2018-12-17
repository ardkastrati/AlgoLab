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
#include <climits>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
        boost::property<boost::edge_capacity_t, long,
                boost::property<boost::edge_residual_capacity_t, long,
                        boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > >   Graph;
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type                EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type       ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type         ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor                   Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor                     Edge;
typedef boost::graph_traits<Graph>::edge_iterator                       EdgeIt;


// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,             // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
                boost::no_property,                             // interior properties of vertices
                boost::property<boost::edge_weight_t, int>              // interior properties of edges
                >                                       GraphD;
typedef boost::graph_traits<GraphD>::edge_descriptor             EdgeD;           // Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<GraphD>::vertex_descriptor           VertexD;         // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).
typedef boost::graph_traits<GraphD>::edge_iterator               EdgeItD;         // to iterate over all edges
typedef boost::graph_traits<GraphD>::out_edge_iterator           OutEdgeItD;      // to iterate over all outgoing edges of a vertex
typedef boost::property_map<GraphD, boost::edge_weight_t>::type  WeightMapD;      // property map to access the interior property edge_weight_t

typedef std::vector<int> VI;
typedef std::vector<VI> VII;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
        Graph &G;
        EdgeCapacityMap &capacitymap;
        ReverseEdgeMap  &revedgemap;

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
                capacitymap[rev_e] = 0; // reverse edge has no capacity!
                revedgemap[e] = rev_e;
                revedgemap[rev_e] = e;
        }
};

bool too_small(VII& bipartite_Graph, int p, int a, int s, int c, int d) {
	// Create Graph and Maps
	Graph G(a + c*s);
        EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
        ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
        EdgeAdder eaG(G, capacitymap, revedgemap);

	for(int i = 0; i < a; i++) {
		for(int j = 0; j < s; j++) {
			if(bipartite_Graph[i][j] != -1 && bipartite_Graph[i][j] + d <= p) eaG.addEdge(i, a + j, 1);
			if(c == 2 && bipartite_Graph[i][j] != -1 && bipartite_Graph[i][j] + 2*d <= p) eaG.addEdge(i, a + s + j, 1);
		}
	}


        // Add source and sink
        Vertex source = boost::add_vertex(G);
        Vertex target = boost::add_vertex(G);
	for(int i = 0; i < a; i++) {
		eaG.addEdge(source, i, 1);
	}
	for(int i = 0; i < s; i++) {
		eaG.addEdge(a + i, target, 1);
		if(c == 2) eaG.addEdge(a + s + i, target, 1);
	}
        // Calculate flow
        // If not called otherwise, the flow algorithm uses the interior properties
        // - edge_capacity, edge_reverse (read access),
        // - edge_residual_capacity (read and write access).
        long flow1 = boost::push_relabel_max_flow(G, source, target);
	return flow1 != a;
}
	

void testcase() {
	int n, m, a, s, c, d; std::cin >> n >> m >> a >> s >> c >> d;
	// Create Graph, Vertices and Edges
	// ================================
	int V = n;
	int E = m;
	GraphD G(V);     // creates an empty graph on n vertices
	WeightMapD weightmap = boost::get(boost::edge_weight, G);        // start by defining property maps for all interior properties defined in Lines 37, 38
	for (int i = 0; i < E; ++i) {
		Edge e; bool success;
		char w; int x, y, z; std::cin >> w >> x >> y >> z;
		boost::tie(e, success) = boost::add_edge(x, y, G);      
		weightmap[e] = z;                  
		if(w == 'L') {
			boost::tie(e, success) = boost::add_edge(y, x, G);
			weightmap[e] = z;
		}
	}
	VI agent(a), shelter(s);
	for(int i = 0; i < a; i++) std::cin >> agent[i];
	for(int i = 0; i < s; i++) std::cin >> shelter[i];

	VII bipartite_Graph(a, VI(s, -1));

	// Dijkstra shortest paths
	// =======================
	VI distmap(V);
	for(int i = 0; i < a; i++) {
		boost::dijkstra_shortest_paths(G, agent[i], distance_map(boost::make_iterator_property_map(distmap.begin(), boost::get(boost::vertex_index, G))));
		for(int j = 0; j < s; j++) {
			if(distmap[shelter[j]] < INT_MAX) {
				bipartite_Graph[i][j] = distmap[shelter[j]];
			}
		}
	}

	int lmin = 0, lmax = 1;
	while (too_small(bipartite_Graph, lmax, a, s, c, d)) lmax *= 2;
	while (lmin != lmax) {
		int p = (lmin + lmax)/2;
		if (too_small(bipartite_Graph, p, a, s, c, d))
			lmin = p + 1;
		else
			lmax = p;
	}
	std::cout << lmin << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
