#include <iostream>
#include <cassert>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact integral type
typedef CGAL::Gmpz ET;
typedef CGAL::Quotient<ET> Q;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::vector<int> VI;

double floor_to_double(const Q& x) {
	double a = std::floor(CGAL::to_double(x));
	while (a > x) a -= 1;
	while (a+1 <= x) a += 1;
	if (a == 0) a = 0;
	return a;
}

void testcase(int n, int m) {
	Program lp (CGAL::SMALLER, true, 0, false, 0);

	for(int i = 0; i < n; i++) {
		int min, max; std::cin >> min >> max;
		lp.set_b(2*i, min);
		lp.set_r(2*i, CGAL::LARGER);
		lp.set_b(2*i + 1, max);
		lp.set_r(2*i + 1, CGAL::SMALLER);
	}

	for(int i = 0; i < m; i++) {
		int p; std::cin >> p; 
		lp.set_c(i, p);

		for(int j = 0; j < n; j++) {	
			int C; std::cin >> C;
			lp.set_a(i, 2*j, C); lp.set_a(i, 2*j+1, C);
		}
	}

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_linear_program(lp, ET());

	// output solution
	if(s.status() == CGAL::QP_INFEASIBLE) std::cout << "No such diet." << std::endl;
	else  std::cout << std::setprecision(0) << std::fixed << floor_to_double(s.objective_value()) << std::endl;

}

int main() {
	int n, m; std::cin >> n >> m;
	while(n != 0 && m != 0) {
		testcase(n, m);
		std::cin >> n >> m;
	}
	return 0;
}
