#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <cmath>

// typedefs
typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;

double ceil_to_double(const K::FT& x) {
	double a = std::ceil(CGAL::to_double(x));
	while(a < x) a += 1;
	while(a - 1 >= x) a -= 1;
	return a;
}

void testcase(int n) {
  K::Point_2 P[n];
  
  for (int i = 0; i < n; ++i) {
	  long x, y; std::cin >> x >> y;
	 	 P[i] = K::Point_2(x, y);
 	} 
  Min_circle mc(P, P+n, true);
  Traits::Circle c = mc.circle();
  std::cout << std::fixed << std::setprecision(0) <<  ceil_to_double(CGAL::sqrt(c.squared_radius())) << std::endl;
}

int main() {
	int n; std::cin >> n;
	while(n) {
		testcase(n);
		std::cin >> n;
	}
	return 0;
}
