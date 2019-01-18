#include <iostream>
#include <cassert>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::vector<ET> VI;

int degree = 30;

void testcase() {
	int h, t; std::cin >> h >> t;
	VI healthy_x(h), healthy_y(h), healthy_z(h);
	VI tumor_x(t), tumor_y(t), tumor_z(t);
	for(int i = 0; i < h; i++) std::cin >> healthy_x[i] >> healthy_y[i] >> healthy_z[i];
	for(int i = 0; i < t; i++) std::cin >> tumor_x[i] >> tumor_y[i] >> tumor_z[i];

	// by default, we have a nonnegative LP with Ax <= b
	Program lp (CGAL::SMALLER, false, 0, false, 0);

	int degree_solved = -1;

	for(int d = 0; d <= degree && degree_solved == -1; d++) {
		int row = 0;
		for(int point = 0; point < h; point++) {
			int column = 0;
			ET x = 1;
			for(int i = 0; i <= d; i++) {
				ET y = 1;
				for(int j = 0; j <= d - i; j++) {
					ET z = 1;
					for(int k = 0; k <= d - i - j; k++) {
						lp.set_a(column, row, x*y*z);
						z *= healthy_z[point];
						column++;
					}
					y *= healthy_y[point];
				}
				x *= healthy_x[point];
			}
			lp.set_r(row, CGAL::SMALLER);
			lp.set_b(row, -1);
			row++;
		}

		for(int point = 0; point < t; point++) {
			int column = 0;
			ET x = 1;
			for(int i = 0; i <= d; i++) {
				ET y = 1;
				for(int j = 0; j <= d - i; j++) {
					ET z = 1;
					for(int k = 0; k <= d - i - j; k++) {
						lp.set_a(column, row, x*y*z);
						z *= tumor_z[point];
						column++;
					}
					y *= tumor_y[point];
				}
				x *= tumor_x[point];
			}
			lp.set_b(row, 1);
			lp.set_r(row, CGAL::LARGER);
			row++;
		}

		CGAL::Quadratic_program_options options;
		options.set_pricing_strategy(CGAL::QP_BLAND);
		Solution s = CGAL::solve_linear_program(lp, ET(), options);
		if(!s.is_infeasible()) {
			degree_solved = d;
		}
	}
	if(degree_solved == -1) {
		std::cout << "Impossible!" << std::endl;
	} else {
		std::cout << degree_solved << std::endl;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}


