// Includes
// CGAL includes
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <climits>
#include <cassert>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

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
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>  Triangulation;
typedef Triangulation::Face_iterator Face_iterator;
typedef Triangulation::Vertex_iterator Vertex_iterator;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;

typedef std::vector<long> VL;

bool too_small(int V, Triangulation& t, long p, std::vector<K::Point_2>& start, std::vector<K::Point_2>& end, int m) {
	Graph G(V);     // creates an empty graph on n vertices
	WeightMap weightmap = boost::get(boost::edge_weight, G);        // start by defining property maps for all interior properties defined in Lines 37, 38

	for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
		Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
		Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
		Vertex u = v1->info(), v = v2->info();
		if((long) CGAL::squared_distance(v1->point(), v2->point()) <= p) {
			Edge e; bool success;
			boost::tie(e, success) = boost::add_edge(u, v, G);
		}
	}
	// Connected components
	// ====================
	std::vector<int> componentmap(V);       // We MUST use such a vector as an Exterior Property Map: Vertex -> Component
	int ncc = boost::connected_components(G, boost::make_iterator_property_map(componentmap.begin(), boost::get(boost::vertex_index, G)));

	for(int i = 0; i < m; i++) {
		K::Point_2 p1 = start[i], p2 = end[i];
		Vertex_handle v1 = t.nearest_vertex(p1);
		Vertex_handle v2 = t.nearest_vertex(p2);
		if(4 * (long) CGAL::squared_distance(v1->point(), p1) > p || 4 * (long) CGAL::squared_distance(v2->point(), p2) > p) return true;
		else if (componentmap[v1->info()] != componentmap[v2->info()]) return true;
	}
	return false;
}

void testcase() {
	int n, m; std::cin >> n >> m;
	long p; std::cin >> p;
	// read points
	std::vector<K::Point_2> pts;
	pts.reserve(n);
	for (int i = 0; i < n; ++i) {
		K::Point_2 p;
		std::cin >> p;
		pts.push_back(p);
	}
	
	std::vector<K::Point_2> start(m);
	std::vector<K::Point_2> end(m);
	for(int i = 0; i < m; i++) {
		std::cin >> start[i] >> end[i];
	}

	// construct triangulation
	Triangulation t;
	t.insert(pts.begin(), pts.end());

	int V = 0;
	for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) v->info() = V++;

	Graph G(V);	// creates an empty graph on n vertices
	WeightMap weightmap = boost::get(boost::edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38
	
	for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
		Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
		Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
		Vertex u = v1->info(), v = v2->info();
		if((long) CGAL::squared_distance(v1->point(), v2->point()) <= p) {
			Edge e; bool success;
			boost::tie(e, success) = boost::add_edge(u, v, G);
		}
	}
	// Connected components
        // ====================
        std::vector<int> componentmap(V);       // We MUST use such a vector as an Exterior Property Map: Vertex -> Component
        int ncc = boost::connected_components(G, boost::make_iterator_property_map(componentmap.begin(), boost::get(boost::vertex_index, G)));

	std::vector<K::Point_2> new_start;
	std::vector<K::Point_2> new_end;

	for(int i = 0; i < m; i++) {
		K::Point_2 p1 = start[i], p2 = end[i];
		Vertex_handle v1 = t.nearest_vertex(p1);
		Vertex_handle v2 = t.nearest_vertex(p2);
		if((long) 4 * CGAL::squared_distance(v1->point(), p1) > p || (long) 4 * CGAL::squared_distance(v2->point(), p2) > p) std::cout << "n";
		else if (componentmap[v1->info()] == componentmap[v2->info()]) {
			std::cout << "y";
			new_start.push_back(p1);
			new_end.push_back(p2);
		}
		else std::cout << "n";	
	}
	std::cout << std::endl;

	long lmin = 0, lmax = 1;
        while(too_small(V, t, lmax, start, end, m)) lmax *= 2;

	while (lmin != lmax) {
		long p = (lmin + lmax)/2;
		if (too_small(V, t, p, start, end, m))
			lmin = p + 1;
		else
			lmax = p;
	}
	long a = lmin;
	std::cout << a << std::endl;

        lmin = 0, lmax = p;
        while (lmin != lmax) {
                long p = (lmin + lmax)/2;
                if (too_small(V, t, p, new_start, new_end, new_start.size()))
                        lmin = p + 1;
                else
                        lmax = p;
        }
        long b = lmin;
        std::cout << b << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
