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
// BGL
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>  Triangulation;
typedef Triangulation::Vertex_iterator Vertex_iterator;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;

typedef std::tuple<long, int, int> Edge;
typedef std::vector<Edge> VEdge;
typedef boost::disjoint_sets_with_storage<> DS;

typedef K::Point_2 P;

void testcase() {
	int n, m; std::cin >> n >> m;
	long p; std::cin >> p;
	// read points
	std::vector<P> pts;
	pts.reserve(n);
	for (int i = 0; i < n; ++i) {
		P p;
		std::cin >> p;
		pts.push_back(p);
	}
	
	std::vector<P> start(m);
	std::vector<P> end(m);
	for(int i = 0; i < m; i++) {
		std::cin >> start[i] >> end[i];
	}

	// construct triangulation
	Triangulation t;
	t.insert(pts.begin(), pts.end());

	int V = 0;
	for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) v->info() = V++;

	DS DSp(V);
	DS DSa(V);
	DS DSb(V);
	VEdge edges;

	for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
		Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
		Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
		int u = v1->info(), v = v2->info();
		long dist = CGAL::squared_distance(v1->point(), v2->point());
		Edge curr = std::make_tuple(dist, u, v);
		if(dist <= p) {
			DSp.union_set(u, v);
		}
		edges.push_back(curr);
	}

	std::sort(edges.begin(), edges.end());
	long a = 0, b = 0;
	int a_pos = 0, b_pos = 0;

	for(int i = 0; i < m; i++) {
		P p1 = start[i], p2 = end[i];
		Vertex_handle v1 = t.nearest_vertex(p1), v2 = t.nearest_vertex(p2);
		long dist1 = 4 * CGAL::squared_distance(v1->point(), p1);
		long dist2 = 4 * CGAL::squared_distance(v2->point(), p2);	

		if(dist1 > p || dist2  > p || DSp.find_set(v1->info()) != DSp.find_set(v2->info())) std::cout << "n";
		else {
			std::cout << "y";
			//Take care of b
			b = std::max(std::max(b, dist1), dist2);
			while(DSb.find_set(v1->info()) != DSb.find_set(v2->info())) {
				DSb.union_set(std::get<1>(edges[b_pos]), std::get<2>(edges[b_pos]));
				b = std::max(b, std::get<0>(edges[b_pos]));
				b_pos++;
			}
		}
		//Take care of a
		a = std::max(std::max(a, dist1), dist2);
		while(DSa.find_set(v1->info()) != DSa.find_set(v2->info())) {
			DSa.union_set(std::get<1>(edges[a_pos]), std::get<2>(edges[a_pos]));
			a = std::max(a, std::get<0>(edges[a_pos]));
			a_pos++;
		}

	}
	std::cout << std::endl;
	std::cout << a << std::endl;
        std::cout << b << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
