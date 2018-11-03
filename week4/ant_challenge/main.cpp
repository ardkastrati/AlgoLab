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
#include <climits>
#include <cassert>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/max_cardinality_matching.hpp>


// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t

//std
typedef std::vector<int> VI;
typedef std::vector<VI> VII;


// Functions
// ========= 
void testcases() {
	// ================================
	// read input
	int n, e, s, a, b; std::cin >> n >> e >> s >> a >> b;
	int V = n, E = e;
	VI hive(s);
	VII edge(e, VI(s+2));
	for(int i = 0; i < e; i++) {
		std::cin >> edge[i][0] >> edge[i][1];
		for(int j = 2; j < s+2; j++) {
			std::cin >> edge[i][j];
		}
	}
	for(int i = 0; i < s; i++) {
		std::cin >> hive[i];
	}

	Graph MasterG(V);	
	WeightMap master_weightmap = boost::get(boost::edge_weight, MasterG);

	for(int i = 0; i < s; i++) {
		Graph G(V);
		WeightMap weightmap = boost::get(boost::edge_weight, G);
		for (int j = 0; j < E; ++j) {
			Edge e;	bool success;
			Vertex u = edge[j][0];
			Vertex v = edge[j][1];
			int w = edge[j][i+2];
			boost::tie(e, success) = boost::add_edge(u, v, G);
			weightmap[e] = w;		
		}
			
		// Prim minimum spanning tree
		// ==========================
		std::vector<Vertex> primpredmap(V);	// We MUST use this vector as an Exterior Property Map: Vertex -> Prim Predecessor
		Vertex start = hive[i];
		boost::prim_minimum_spanning_tree(G, boost::make_iterator_property_map(primpredmap.begin(), boost::get(boost::vertex_index, G)),	// Prim from user-defined start,
				boost::root_vertex(start));									// old primpredmap gets reset first!	
		for (int i = 0; i < V; ++i) {
			if (primpredmap[i] != i) {
				Edge e, master_e; bool success;
				boost::tie(e, success) = boost::edge(i, primpredmap[i], G);
				boost::tie(master_e, success) = boost::add_edge(i, primpredmap[i], MasterG);
				weightmap[master_e] = weightmap[e];
			}
		}

	}

	// Dijkstra shortest paths
	// =======================
	std::vector<int> distmap(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	Vertex start = a;
	boost::dijkstra_shortest_paths(MasterG, start, // We MUST provide at least one of the two maps
		distance_map(boost::make_iterator_property_map(distmap.begin(), boost::get(boost::vertex_index, MasterG))));	// distance map as Named Parameter
	
	std::cout << distmap[b] << std::endl;

}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	std::cin >> T;
	while(T--)	testcases();
	return 0;
}

