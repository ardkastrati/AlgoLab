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
#include <boost/graph/biconnected_components.hpp>


// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
		boost::no_property, boost::property<boost::edge_weight_t, std::size_t> >	Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type  ComponentMap;      // property map to access the interior property edge_weight_t


//STD
typedef std::vector<std::pair<Vertex, Vertex> > VPVV;
typedef std::vector<int> VI;

// Functions
// ========= 
void testcases() {
	// read input 
	// ================================
	int n, m; std::cin >> n >> m;
	int V = n, E = m;
	Graph G(V);	

	for (int i = 0; i < E; ++i) {
		Edge e;	bool success;
		Vertex u, v; std::cin >> u >> v;
		boost::tie(e, success) = boost::add_edge(u, v, G);
	}

	// Connected components
        // ====================
	ComponentMap biconnected_components = boost::get(boost::edge_weight, G);
        int nbcc = boost::biconnected_components(G, biconnected_components);

       	VI componentsize(nbcc, 0);
	EdgeIt ebeg, eend;
	for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg) {
		componentsize[biconnected_components[*ebeg]]++;
	}

	int k = 0;
	VPVV critical_edges;
	for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg) {
		Vertex u = source(*ebeg, G);
		Vertex v = target(*ebeg, G);
		if (componentsize[biconnected_components[*ebeg]] == 1) {
			k++;
			critical_edges.push_back(std::make_pair(std::min(u, v), std::max(u, v)));
		}
	}

	std::sort(critical_edges.begin(), critical_edges.end());
	std::cout << k << std::endl;
	for(int i = 0; i < k; i++) {
		std::cout << critical_edges[i].first << " " << critical_edges[i].second << std::endl;
	}
}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	std::cin >> T;
	while(T--)	testcases();
	return 0;
}

