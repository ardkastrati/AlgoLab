#include <iostream>
#include <tuple>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;

typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Edge_circulator Edge_circulator;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef Triangulation::Finite_edges_iterator Edge_iterator;

typedef K::Point_2 P;
typedef std::vector<P> VP;
typedef std::vector<int> VI;
typedef K::FT FT;

int dfs(Vertex_handle root, VI& color, VI& component, int component_num, Triangulation& t, int use_color, Triangulation& t0, Triangulation& t1, FT& rr, int first_call) {
	int toReturn = 1;
	if(color[root->info()] == -1) {
		component[root->info()] = component_num;
		color[root->info()] = use_color;
		if(use_color == 0) t0.insert(root->point());
		else t1.insert(root->point()); 

		use_color = 1 - use_color;

		Edge_circulator circulator = t.incident_edges(root);
  		do { 
			Vertex_handle v1 = circulator->first->vertex((circulator->second + 1) % 3);
			Vertex_handle v2 = circulator->first->vertex((circulator->second + 2) % 3);
			Vertex_handle next;
			if(v1->point() == root->point()) {
				next = v2;
			} else {
				next = v1;	
			}
    			if (!t.is_infinite(next) && CGAL::squared_distance(v1->point(), v2->point()) <= rr) {		
				toReturn = dfs(next, color, component, component_num, t, use_color, t0, t1, rr, 0);
			}

  		} while (toReturn == 1 && ++circulator != t.incident_edges(root));

	} else if(first_call == 0 && color[root->info()] != use_color) {
		toReturn = -1;
	}
	return toReturn;
}

void testcase() {
	int n, m, r; std::cin >> n >> m >> r;
	FT rr = CGAL::square(FT(r));

	// read points
	VP station(n);
	for (int i = 0; i < n; ++i) {
		int x, y; std::cin >> x >> y;
		station[i] = P(x, y);
	}
	VP clue_a(m);
	VP clue_b(m);
	for(int i = 0; i < m; i++) {
		int a, b, c, d; std::cin >> a >> b >> c >> d;
		clue_a[i] = P(a, b);
		clue_b[i] = P(c, d);
	}

	// construct triangulation
	Triangulation t;
	t.insert(station.begin(), station.end());
	
	int V = 0;	
	for(Vertex_iterator it = t.finite_vertices_begin(); it != t.finite_vertices_end(); it++) it->info() = V++;

	VI color(V, -1);
	VI component(V, -1);
	int component_num = 0;
	Triangulation t0, t1;
	int bicolor_possible = 1;
	for(Vertex_iterator it = t.finite_vertices_begin(); it != t.finite_vertices_end() && bicolor_possible == 1; it++) {
		bicolor_possible = dfs(it, color, component, component_num, t, 0, t0, t1, rr, 1);
		component_num++;
	}

	for(Edge_iterator eit = t0.finite_edges_begin(); eit != t0.finite_edges_end() && bicolor_possible == 1; eit++) {
		Vertex_handle v1 = eit->first->vertex((eit->second + 1) % 3);
                Vertex_handle v2 = eit->first->vertex((eit->second + 2) % 3);
		if(CGAL::squared_distance(v1->point(), v2->point()) <= rr) {
			bicolor_possible = -1;
		}
	}
	for(Edge_iterator eit = t1.finite_edges_begin(); eit != t1.finite_edges_end() && bicolor_possible == 1; eit++) {
		Vertex_handle v1 = eit->first->vertex((eit->second + 1) % 3);
                Vertex_handle v2 = eit->first->vertex((eit->second + 2) % 3);
		if(CGAL::squared_distance(v1->point(), v2->point()) <= rr) {
			bicolor_possible = -1;
		}
	}

	for(int i = 0; i < m; i++) {
		if(bicolor_possible == -1) {
			std::cout << "n";
		} else if(CGAL::squared_distance(clue_a[i], clue_b[i]) <= rr) {
			std::cout << "y";
		} else {
			Vertex_handle v1 = t.nearest_vertex(clue_a[i]);
			Vertex_handle v2 = t.nearest_vertex(clue_b[i]);
			if(CGAL::squared_distance(v1->point(), clue_a[i]) <= rr && CGAL::squared_distance(v2->point(), clue_b[i]) <= rr && component[v1->info()] == component[v2->info()]) {
			  	std::cout << "y";
			} else {
				std::cout << "n";
			}
		}
	}
	std::cout << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}

