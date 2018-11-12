#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>
#include <algorithm>
#include <map>
#include <limits>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Vertex_iterator Vertex_iterator;

long MAX = std::numeric_limits<long>::max();

int time(double distance) {
	return (int) std::ceil(std::sqrt((std::sqrt(distance) - 1)/2));
}

void testcase(int n) {
	int l, b, r, t; std::cin >> l >> b >> r >> t;

	// read points
	std::vector<K::Point_2> pts;
	pts.reserve(n);
	for (std::size_t i = 0; i < n; ++i) {
		long x, y; std::cin >> x >> y;
		pts.push_back(P(x, y));
	}
	// construct triangulation
	Triangulation triang;
	triang.insert(pts.begin(), pts.end());
	std::vector<long> dist_to_border(n, MAX);
	
	int i = 0;
	for(Vertex_iterator it = triang.finite_vertices_begin(); it != triang.finite_vertices_end(); it++) { 
		K::Point_2 p = it->point();
		dist_to_border[i] = std::min(4 * (long) CGAL::squared_distance(p, P(l, p.y())), dist_to_border[i]); 
		dist_to_border[i] = std::min(4 * (long) CGAL::squared_distance(p, P(r, p.y())), dist_to_border[i]);
		dist_to_border[i] = std::min(4 * (long) CGAL::squared_distance(p, P(p.x(), b)), dist_to_border[i]);
		dist_to_border[i] = std::min(4 * (long) CGAL::squared_distance(p, P(p.x(), t)), dist_to_border[i]);
		
		Vertex_handle nearest = CGAL::nearest_neighbor(triang, it);
		if(nearest != NULL) {
			long dist = CGAL::squared_distance(p, nearest->point());
			dist_to_border[i] = std::min(dist, dist_to_border[i]);
		}	
		i++;
	}
	sort(dist_to_border.begin(), dist_to_border.end());
	std::cout << time(dist_to_border.front()) << " " << time(dist_to_border[dist_to_border.size()/2]) << " " << time(dist_to_border.back()) << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n; std::cin >> n;
	while(n > 0) {
		testcase(n);
		std::cin >> n;
	}
	return 0;
}
