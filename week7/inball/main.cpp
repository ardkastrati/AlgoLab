#include <iostream>
#include <cassert>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

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
	return a;
}


int norm(VI& a) {
	int sum = 0;
	for(int i = 0; i < a.size(); i++) {
		sum += a[i]*a[i];
	}
	int norm = (int) (std::sqrt(sum) + 0.5);
	return norm;
}

void testcase(int n, int d) {
	Program lp (CGAL::SMALLER, false, 0, false, 0);
	
	for(int i = 0; i < n; i++) {
		VI a(d);
		for(int j = 0; j < d; j++) {
			std::cin >> a[j]; 
			lp.set_a(j, i, a[j]);
		}
		int n = norm(a);
		lp.set_a(d, i, n);
		int b; std::cin >> b;
		lp.set_b(i, b);
	}
	lp.set_l(d, true, 0);
	lp.set_c(d, -1);
		
	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_linear_program(lp, ET());
	if(s.status() == CGAL::QP_INFEASIBLE) std::cout << "none" << std::endl;
	else if(s.status() == CGAL::QP_UNBOUNDED) std::cout << "inf" << std::endl;
	else std::cout << std::fixed << std::setprecision(0) << floor_to_double(-s.objective_value()) << std::endl;
}

int main() {
	int n; std::cin >> n;
	while(n != 0) {
		int d; std::cin >> d;
		testcase(n, d);
		std::cin >> n;
	}
	return 0;
}
