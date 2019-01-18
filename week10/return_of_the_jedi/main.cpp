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
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t

typedef std::vector<int> VI;
typedef std::vector<VI> VII;
typedef std::vector<std::vector<std::pair<int, int> > > DFS_G;

void dfs(DFS_G& primGraph, int root, VI& differences, VI& visited, int curr_max) {
	visited[root] = 1;
	differences[root] = curr_max;
	for(std::pair<int, int> neighbor : primGraph[root]) {
		if(visited[neighbor.first] == 0) {
			dfs(primGraph, neighbor.first, differences, visited, std::max(curr_max, neighbor.second));
		}	
	}
}

// Functions
// ========= 
void testcases() {
	// Create Graph, Vertices and Edges
	// ================================
	int V, start; std::cin >> V >> start;
	start -= 1;
	Graph G(V);	// creates an empty graph on n vertices
	WeightMap weightmap = boost::get(boost::edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38
	for (int i = 0; i < V-1; ++i) {
		for(int j = i+1; j < V; j++) {
			Edge e;	bool success;
			Vertex u = i, v = j;
			int w; std::cin >> w;
			boost::tie(e, success) = boost::add_edge(u, v, G);	// Adds edge from u to v. If parallel edges are allowed, success is always true.
			weightmap[e] = w;			// Otherwise it is false in case of failure when the edge is a duplicate
		}
	}
	// Prim minimum spanning tree
	// ==========================
	std::vector<Vertex> primpredmap(V);	// We MUST use this vector as an Exterior Property Map: Vertex -> Prim Predecessor
	boost::prim_minimum_spanning_tree(G, boost::make_iterator_property_map(primpredmap.begin(), boost::get(boost::vertex_index, G)),	// Prim from user-defined start,
			boost::root_vertex(start));									// old primpredmap gets reset first!	

	DFS_G primGraph(V, std::vector<std::pair<int, int> >(0));

	// iterate over all vertices
	for (int i = 0; i < V; ++i) {
		// OutEdgeIterators
		// ================
		Vertex u = i;
		OutEdgeIt oebeg, oeend;
		for (boost::tie(oebeg, oeend) = boost::out_edges(u, G); oebeg != oeend; ++oebeg) {
			Vertex v = boost::target(*oebeg, G);	// source(*oebeg, G) is guaranteed to be u, even in an undirected graph.
			if (primpredmap[u] == v) {
				primGraph[u].push_back(std::make_pair(v, weightmap[*oebeg]));
				primGraph[v].push_back(std::make_pair(u, weightmap[*oebeg]));
			}
		}
	}

	VII max(V, VI(V, std::numeric_limits<int>::max()));
	for(int i = 0; i < V; i++) {
		VI visited(V, 0);
		dfs(primGraph, i, max[i], visited, 0);	
	}

	int totalweight = 0;
	for (int i = 0; i < V; ++i) {
		if (primpredmap[i] != i) {
			Edge e; bool success;
			boost::tie(e, success) = boost::edge(i, primpredmap[i], G);
			totalweight += weightmap[e];
		}
	}

	int min_diff = std::numeric_limits<int>::max();
	for (int i = 0; i < V; ++i) {
		Vertex u = i;
		OutEdgeIt oebeg, oeend;
		for (boost::tie(oebeg, oeend) = boost::out_edges(u, G); oebeg != oeend; ++oebeg) {
			Vertex v = boost::target(*oebeg, G);	
			if (primpredmap[u] != v && primpredmap[v] != u) {
				int curr_max = max[u][v];	
				min_diff = std::min(min_diff, weightmap[*oebeg] - curr_max);
			}
		}
	}
	std::cout << totalweight + min_diff << std::endl;	
}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	std::cin >> T;
	while(T--)	testcases();
	return 0;
}


