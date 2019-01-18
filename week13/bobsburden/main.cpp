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
#include <limits>
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
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t

typedef std::pair<int, int> P;
typedef std::vector<P> VP;
typedef std::vector<VP> VVP;


// Functions
// ========= 
void testcases() {
	int k; std::cin >> k;
	VVP balls(k);
	int counter = 0;
	for(int i = 0; i < k; i++) {
		for(int j = 0; j <= i; j++) {
			int a; std::cin >> a;
			balls[i].push_back(std::make_pair(a, counter));
			counter++;
		}
	}

	// Create Graph, Vertices and Edges
	// ================================
	int V = k*(k+1)/2;
	int first = 0;
	int second = k*(k+1)/2 - k;
	int third = k*(k+1)/2 - 1;

	Graph G(V);	// creates an empty graph on n vertices
	WeightMap weightmap = boost::get(boost::edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38

	for (int i = 0; i < k; ++i) {
		for(int j = 0; j <= i; j++) {
			Edge e;	bool success;
			Vertex u = balls[i][j].second;
			if(i > 0 && j < i) {
				boost::tie(e, success) = boost::add_edge(u, balls[i-1][j].second, G);	
				weightmap[e] = balls[i-1][j].first;			
			}
			if(i > 0 && j > 0) {
				boost::tie(e, success) = boost::add_edge(u, balls[i-1][j-1].second, G);	
				weightmap[e] = balls[i-1][j-1].first;			
			}
			if(j > 0) {
				boost::tie(e, success) = boost::add_edge(u, balls[i][j-1].second, G);	
				weightmap[e] = balls[i][j-1].first;			
			}
			if(j < i) {
				boost::tie(e, success) = boost::add_edge(u, balls[i][j+1].second, G);	
				weightmap[e] = balls[i][j+1].first;			
			}
			if(i < k-1) {
				boost::tie(e, success) = boost::add_edge(u, balls[i+1][j].second, G);	
				weightmap[e] = balls[i+1][j].first;		
				boost::tie(e, success) = boost::add_edge(u, balls[i+1][j+1].second, G);	
				weightmap[e] = balls[i+1][j+1].first;		
			}
		}
	}
	// Dijkstra shortest paths
	// =======================
	std::vector<int> distmap1(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	Vertex start = first;
	boost::dijkstra_shortest_paths(G, start, 
		distance_map(boost::make_iterator_property_map(distmap1.begin(), boost::get(boost::vertex_index, G))));	// distance map as Named Parameter

	// Dijkstra shortest paths
	// =======================
	std::vector<int> distmap2(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	start = second;
	boost::dijkstra_shortest_paths(G, start, 
		distance_map(boost::make_iterator_property_map(distmap2.begin(), boost::get(boost::vertex_index, G))));	// distance map as Named Parameter

	// Dijkstra shortest paths
	// =======================
	std::vector<int> distmap3(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	start = third;
	boost::dijkstra_shortest_paths(G, start, 
		distance_map(boost::make_iterator_property_map(distmap3.begin(), boost::get(boost::vertex_index, G))));	// distance map as Named Parameter

	int best = std::numeric_limits<int>::max();

	for(int i = 0; i < k; i++) {
		for(int j = 0; j <= i; j++) {
			best = std::min(best, distmap1[balls[i][j].second] + distmap2[balls[i][j].second] + distmap3[balls[i][j].second] - 2*balls[i][j].first);

		}
	}
	std::cout << best << std::endl;
	
}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	std::cin >> T;
	while(T--)	testcases();
	return 0;
}


