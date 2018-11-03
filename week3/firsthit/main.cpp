#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

typedef CGAL::Exact_predicates_exact_constructions_kernel EK;
typedef EK::Point_2 P;
typedef EK::Ray_2 R;
typedef EK::Segment_2 S;

typedef std::vector<S> VS;


double floor_to_double(const EK::FT& x) {
	double a = std::floor(CGAL::to_double(x));
	while (a > x) a -= 1;
	while (a + 1 <= x) a += 1;
	return a;
}

int testcase(int n) {
	long x, y, a, b; std::cin >> x >> y >> a >> b;
	R phileasRay = R(P(x, y), P(a, b));
	
	VS obstacle(n);
	for(int i = 0; i < n; i++) {
		long r, s, t, u; std::cin >> r >> s >> t >> u;
		obstacle[i] = S(P(r,s), P(t,u));
	}
	std::random_shuffle(obstacle.begin(), obstacle.end());	

	bool solution = false;
	S phileasSegment;
	for(int i = 0; i < n; i++) {
		if((!solution && CGAL::do_intersect(phileasRay, obstacle[i])) || CGAL::do_intersect(phileasSegment, obstacle[i])) {
			solution = true; 
			auto o = CGAL::intersection(phileasRay, obstacle[i]);
			if(const P* op = boost::get<P>(&*o)) {
				phileasSegment = S(phileasRay.source(), *op);
			} else if (const S* os = boost::get<S>(&*o)) {
				if(CGAL::squared_distance(phileasRay.source(), os->source()) < CGAL::squared_distance(phileasRay.source(), os->target())) {
					phileasSegment = S(phileasRay.source(), os->source());
				} else {
					phileasSegment = S(phileasRay.source(), os->target());
				}
			} else {
				std::cout << "Shouldn't happen" << std::endl;	
			}
		}
	}
	if(solution) {
		std::cout << std::fixed << std::setprecision(0) << floor_to_double(phileasSegment.target().x()) << " " << floor_to_double(phileasSegment.target().y()) << std::endl;		
	} else {
		std::cout << "no" << std::endl;
	}
	return 0;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n; std::cin >> n;
	while(n) {
		testcase(n);
		std::cin >> n;
	}
}
