
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <limits>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

long MAXLONG = std::numeric_limits<long>::max();

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

	long best = MAXLONG;	
	// output all edges
	for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
		best = std::min(best, (long)t.segment(e).squared_length());

	std::cout << std::ceil(std::sqrt(best)*50) << std::endl;
}

int main() {
	int n; std::cin >> n;
	while(n > 0) {
		testcase(n);
		std::cin >> n;
	}
	return 0;
}
