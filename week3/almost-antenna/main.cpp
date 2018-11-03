#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <cmath>
#include <vector>

// typedefs
typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
typedef	 K::Point_2 P;
typedef  std::vector<P> VP;

double ceil_to_double(const K::FT& x) {
	double a = std::ceil(CGAL::to_double(x));
	while(a < x) a += 1;
	while(a - 1 >= x) a -= 1;
	return a;
}

void testcase(int n) {
	VP point(n);
  
	for (int i = 0; i < n; ++i) {
		long x, y; std::cin >> x >> y;
	 	point[i] = P(x, y);
 	} 

  	Min_circle mc(point.begin(), point.end(), true);
  	Traits::Circle c = mc.circle();
	K::FT best = c.squared_radius();
	
	for (int i = 0; i < mc.number_of_support_points(); i++) {
		P p = mc.support_point(i);
		VP new_points;
		for(int j = 0; j < n; j++) {
			if(p == point[j]) {
				new_points = VP(point.begin(), point.begin() + j);
				if(j < n-1)	new_points.insert(new_points.end(), point.begin() + j + 1, point.end());
			}
		}
		Min_circle new_mc(new_points.begin(), new_points.end(), true);
		c = new_mc.circle();
		K::FT new_best = c.squared_radius();
		if(best > new_best) best = new_best;
	}

  	std::cout << std::fixed << std::setprecision(0) <<  ceil_to_double(CGAL::sqrt(best)) << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int n; std::cin >> n;
	while(n) {
		testcase(n);
		std::cin >> n;
	}
	return 0;
}

