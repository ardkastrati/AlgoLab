#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

// Includes
// ========
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <limits>
#include <cassert>
#include <tuple>
#include <queue>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;

typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Face_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;

typedef K::Point_2 P;
typedef K::FT FT;
typedef std::vector<P> VP;
typedef std::vector<FT> VFT;
typedef std::vector<int> VI;

typedef std::tuple<FT, int> Item; // weight, child
typedef std::priority_queue<Item> PQ;

long LMAX = std::numeric_limits<long>::max();
FT MAX = FT(LMAX)*FT(LMAX);

typedef std::vector<std::vector<Item> > Graph;

void testcase() {
	int n, m; FT r; std::cin >> n >> m >> r;

	// read points
	VP trees(n);
	for(int i = 0; i < n; ++i) {
		long x, y; std::cin >> x >> y;
		trees[i] = P(x, y);
	}

	VP balloon(m);
	VFT balloon_radius(m);
	for(int i = 0; i < m; i++) {
		long x, y, w; std::cin >> x >> y >> w;
		balloon[i] = P(x, y);
		balloon_radius[i] = FT(w);
	}

	// construct triangulation
	Triangulation triangulation;
	triangulation.insert(trees.begin(), trees.end());

	int V = 1;
	for(Face_iterator f = triangulation.finite_faces_begin(); f != triangulation.finite_faces_end(); f++) f->info() = V++;
	
	Graph G(V);	// creates an empty graph on n vertices
	PQ queue;
	for (Face_iterator f = triangulation.finite_faces_begin(); f != triangulation.finite_faces_end(); f++) {
		FT escape = CGAL::squared_radius(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point());
		G[0].push_back(std::make_tuple(escape, f->info()));
		G[f->info()].push_back(std::make_tuple(escape, 0));
		for(int i = 0; i < 3; i++) {
			int u = f->info();
			int v = f->neighbor(i)->info();
			if(triangulation.is_infinite(f->neighbor(i))) v = 0;
			FT w = CGAL::squared_distance(f->vertex((i+1)%3)->point(), f->vertex((i+2)%3)->point());
			G[u].push_back(std::make_tuple(w, v));
			G[v].push_back(std::make_tuple(w, u));
		}
	}

	
	VFT sol(V+1, -1);
	VI parent(V+1, -1);
	VFT prim(V+1, -1);
	queue.push(std::make_tuple(MAX, 0));
	sol[V] = MAX;
	prim[0] = MAX;
	parent[0] = V;
	
	while(!queue.empty()) {
		FT w; int v; std::tie(w, v) = queue.top();
		queue.pop();
		//unvisited node
		if(sol[v] == -1) {
			sol[v] = std::min(sol[parent[v]], w);

			for(Item a : G[v]) {
				FT w_next; int v_next; std::tie(w_next, v_next) = a;
				if(prim[v_next] == -1 || prim[v_next] < w_next) {
					queue.push(a);
					prim[v_next] = w_next;
					parent[v_next] = v;
				}
			}
		}
	}
	
	for(int i = 0; i < m; i++) {
		FT radii = 4*FT(r + balloon_radius[i])*FT(r + balloon_radius[i]);
		if(4*CGAL::squared_distance(balloon[i], triangulation.nearest_vertex(balloon[i])->point()) < radii) {
			std::cout << "n";
		} else {
			Face_handle f = triangulation.locate(balloon[i]);
			if(triangulation.is_infinite(f) || sol[f->info()] >= radii) {
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


