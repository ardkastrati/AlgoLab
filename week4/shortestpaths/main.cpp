// ALGOLAB BGL Tutorial 1
// Code snippets demonstrating 
// - graph definitions
// - several algorithms (components, distance-based algorithms, maximum matching)
// - how to pass exterior property maps
// - use of iterators

// Compile and run with one of the following:
// g++ -std=c++11 -O2 bgl-code_snippets.cpp -o bgl-code_snippets; ./bgl-code_snippets
// g++ -std=c++11 -O2 -I path/to/boost_1_58_0 bgl-code_snippets.cpp -o bgl-code_snippets; ./bgl-code_snippets

// Includes
// ========
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>
#include <cassert>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

// STL definitions
// =====================
typedef std::vector<std::pair<int, int> > VPII;

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t


// Functions
// ========= 
void testcases() {
	// read input 
	// ================================	
	int n, m , q; std::cin >> n >> m >> q;
	VPII position(n);
	for(int i = 0; i < n; i++) {
		int lon, lat; std::cin >> lon >> lat;
		position[i] = std::make_pair(lon, lat);
	}	

	int V = n, E = m;
	Graph G(V);	// creates an empty graph on n vertices
	WeightMap weightmap = boost::get(boost::edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38
	for (int i = 0; i < E; ++i) {
		Edge e;	bool success;
		Vertex u, v; std::cin >> u >> v;
		int w; std::cin >> w;
		boost::tie(e, success) = boost::add_edge(u, v, G);
		weightmap[e] = w;	
	}
	for(int i = 0; i < q; i++) {
		int s, t; std::cin >> s >> t;
		// Dijkstra shortest paths
		// =======================
		std::vector<int> distmap(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
		Vertex start = s;
		boost::dijkstra_shortest_paths(G, start, distance_map(boost::make_iterator_property_map(distmap.begin(), boost::get(boost::vertex_index, G))));	
		if (distmap[t] < INT_MAX) {
			std::cout << distmap[t] << std::endl;
		} else {
			std::cout << "unreachable" << std::endl;
		}

	}
}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	T = 1;
	while(T--)	testcases();
	return 0;
}

