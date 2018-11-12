#include <iostream>
#include <cassert>
#include <algorithm>
#include <limits>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact integral type
typedef CGAL::Gmpz ET;
typedef CGAL::Quotient<ET> Q;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::pair<int, int> P;
typedef std::vector<P> VP;

double MAX = std::numeric_limits<double>::max();

double ceil_to_double(const Q& x) {
        double a = std::ceil(CGAL::to_double(x));
        while (a < x) a += 1;
        while (a-1 >= x) a -= 1;
        if (a == 0) a = 0;
        return a;
}

void testcase(int kali) {
	int n, m, h, w; std::cin >> n >> m >> h >> w;

	VP free_nails(n);
	VP occupied_nails(m);

	for(int i = 0; i < n; i++) {
		int x, y; std::cin >> x >> y;
		free_nails[i] = std::make_pair(x, y);
	}

	for(int i = 0; i < m; i++) {
		int x, y; std::cin >> x >> y;
		occupied_nails[i] = std::make_pair(x, y);
	}

	// by default, we have a nonnegative LP with Ax <= b
	Program lp (CGAL::SMALLER, true, 1, false, 0);

	//take care of old posters
	int k = 0;	
	for(int i = 0; i < n; i++) {
		//Find the nearest
		double dist = MAX; int best = -1;
		for(int j = 0; j < m; j++) {
			double dist1 = ((double) std::abs(free_nails[i].first - occupied_nails[j].first))/w;
			double dist2 = ((double) std::abs(free_nails[i].second - occupied_nails[j].second))/h;
			double new_dist = std::max(dist1, dist2);
			if(new_dist < dist) {
				dist = new_dist;
				best = j;
			}	
		}
		if(best != -1) {
			//Create now only one constraint
			double dist1 = ((double) std::abs(free_nails[i].first - occupied_nails[best].first))/w;
			double dist2 = ((double) std::abs(free_nails[i].second - occupied_nails[best].second))/h;
			if(dist1 > dist2) {
				//I should compare x's
				if(free_nails[i].first <= occupied_nails[best].first) {
					lp.set_a(i, k, w); lp.set_b(k, 2*(occupied_nails[best].first - free_nails[i].first) - w);
				} else {
					lp.set_a(i, k, w); lp.set_b(k, -2*(occupied_nails[best].first - free_nails[i].first) - w);
				}
			}  else {
				if(free_nails[i].second <= occupied_nails[best].second) {
					lp.set_a(i, k, h); lp.set_b(k, 2*(occupied_nails[best].second - free_nails[i].second) - h);
				} else {
					lp.set_a(i, k, h); lp.set_b(k, -2*(occupied_nails[best].second - free_nails[i].second) - h);
				}
			}
			k++;
		}
	}

	//take care of new posters;
	for(int i = 0; i < n; i++) {
                for(int j = i+1; j < n; j++) {
                        double dist1 = ((double) std::abs(free_nails[i].first - free_nails[j].first))/w;
                        double dist2 = ((double) std::abs(free_nails[i].second - free_nails[j].second))/h;
                        if(dist1 > dist2) {
                                //I should compare x's
                                if(free_nails[i].first <= free_nails[j].first) {
                                        lp.set_a(i, k, w); lp.set_a(j, k, w); lp.set_b(k, 2*(free_nails[j].first - free_nails[i].first));
                                } else {
                                        lp.set_a(j, k, w); lp.set_a(i, k, w); lp.set_b(k, -2*(free_nails[j].first - free_nails[i].first));
                                }
                        }  else {
                                if(free_nails[i].second <= free_nails[j].second) {
                                        lp.set_a(i, k, h); lp.set_a(j, k, h); lp.set_b(k, 2*(free_nails[j].second - free_nails[i].second));
                                } else {
                                        lp.set_a(j, k, h); lp.set_a(i, k, h); lp.set_b(k, -2*(free_nails[j].second - free_nails[i].second));
                                }
                        }
                        k++;
                }
        }


	for(int i = 0; i < n; i++) {
		lp.set_c(i, -2*(h+w));
	}

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_linear_program(lp, ET());
	assert (s.solves_linear_program(lp));

	// output solution
	std::cout << std::setprecision(0) << std::fixed << ceil_to_double(-s.objective_value()) << std::endl;
}

int main() {
	int t; std::cin >> t;
	while(t--) testcase(t);
}
