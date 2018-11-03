#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;
typedef K::Segment_2 S;

typedef std::vector<S> VS;

int testcase(int n) {
	long x, y, a, b; std::cin >> x >> y >> a >> b;
	R phileas = R(P(x, y), P(a, b));
	
	VS obstacle(n);
	for(int i = 0; i < n; i++) {
		long r, s, t, u; std::cin >> r >> s >> t >> u;
		obstacle[i] = S(P(r,s), P(t,u));
	}
	
	for(int i = 0; i < n; i++) {
		if(CGAL::do_intersect(phileas, obstacle[i])) {
			std::cout << "yes" << std::endl;
			return 0;
		}
	}
	std::cout << "no" << std::endl;
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
