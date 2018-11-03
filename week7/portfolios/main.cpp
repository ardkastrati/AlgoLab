#include <iostream>
#include <cassert>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::vector<int> VI;


void testcase(int n, int m) {
	Program qp (CGAL::LARGER, true, 0, false, 0);
	
	VI c(n), r(n);
	for(int i = 0; i < n; i++) std::cin >> c[i] >> r[i];

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			int a; std::cin >> a;
		        if(j <= i) qp.set_d(i, j, 2*a);
		}
	}

	for(int i = 0; i < m; i++) {
		int C, R, V; std::cin >> C >> R >> V;

		for(int i = 0; i < n; i++) {
			qp.set_a(i, 0, r[i]);
			qp.set_a(i, 1, c[i]);
		}
		qp.set_b(0, R);
		qp.set_r(0, CGAL::LARGER);
		qp.set_b(1, C);
		qp.set_r(1, CGAL::SMALLER);
		
		// solve the program, using ET as the exact type
		Solution s = CGAL::solve_quadratic_program(qp, ET());
		if(s.status() == CGAL::QP_INFEASIBLE || s.objective_value() > ET(V)) std::cout << "No." << std::endl;
		else std::cout << "Yes." << std::endl;
	}
}

int main() {
	int n, m; std::cin >> n >> m;
	while(n != 0 && m != 0) {
		testcase(n, m);
		std::cin >> n >> m;
	}
	return 0;
}
