// Includes
// CGAL includes
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <climits>
#include <cassert>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, long> 		// interior properties of edges
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>  Triangulation;
typedef Triangulation::Face_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;

typedef std::vector<long> VL;

long MAX = std::numeric_limits<long>::max()/4;

long find_min_in_path(int k, std::vector<Vertex>& primpredmap, VL& sol, WeightMap& weightmap, Graph& G) {
	if(sol[k] == -1) {
		Edge e; bool success;
		boost::tie(e, success) = boost::edge(k, primpredmap[k], G);
		sol[k] = std::min(MAX - weightmap[e], find_min_in_path(primpredmap[k], primpredmap, sol, weightmap, G));
	}
	return sol[k];
}

void testcase(int n) {
	// read points
	std::vector<K::Point_2> pts;
	pts.reserve(n);
	for (std::size_t i = 0; i < n; ++i) {
		K::Point_2 p;
		std::cin >> p;
		pts.push_back(p);
	}
	// construct triangulation
	Triangulation t;
	t.insert(pts.begin(), pts.end());
	int V = 1;
	for (Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f) f->info() = V++;

	Graph G(V);	// creates an empty graph on n vertices
	WeightMap weightmap = boost::get(boost::edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38

	for (Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f) {
		for(int i = 0; i < 3; i++) {
			Vertex u = f->info(), v;
			if(t.is_infinite(f->neighbor(i))) v = 0;
			else v = f->neighbor(i)->info();
			Edge e; bool success;
			boost::tie(e, success) = boost::add_edge(u, v, G);
			weightmap[e] = MAX - (long) CGAL::squared_distance(f->vertex((i+1)%3)->point(), f->vertex((i+2)%3)->point());
		}
	}
	// Prim minimum spanning tree
        // ==========================
        std::vector<Vertex> primpredmap(V);     // We MUST use this vector as an Exterior Property Map: Vertex -> Prim Predecessor
        Vertex start = 0;
        boost::prim_minimum_spanning_tree(G, boost::make_iterator_property_map(primpredmap.begin(), boost::get(boost::vertex_index, G)),        // Prim from user-defined start,
                        boost::root_vertex(start));                                                                     // old primpredmap gets reset first!
	VL sol(V, -1);
	sol[0] = MAX;
        for (int i = 1; i < V; ++i) {
		sol[i] = find_min_in_path(i, primpredmap, sol, weightmap, G);
        }

	int m; std::cin >> m;
	for(int i = 0; i < m; i++) {
		K::Point_2 p;
		std::cin >> p;	
		long d; std::cin >> d;
		if(CGAL::squared_distance(t.nearest_vertex(p)->point(), p) < d) std::cout << "n";
		else {
			Face_handle f = t.locate(p);	
			if(t.is_infinite(f) || sol[f->info()] >= 4*d) std::cout << "y";
			else std::cout << "n";
		}
	}
	std::cout << std::endl;
}

int main() {
	int n; std::cin >> n;
	while(n > 0) {
		testcase(n);
		std::cin >> n;
	}
	return 0;
}
