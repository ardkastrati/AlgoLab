
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;

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

	int m; std::cin >> m;
	for (int i = 0; i < m; i++) {
		K::Point_2 p; std::cin >> p;
		Vertex_handle v = t.nearest_vertex(p);	
		std::cout << std::setprecision(0) << std::fixed << CGAL::squared_distance(p, v->point()) << std::endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n; std::cin >> n;
	while(n > 0) {
		testcase(n);
		std::cin >> n;
	}
}
