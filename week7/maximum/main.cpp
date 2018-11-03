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


double floor_to_double(const Q& x) {
	double a = std::floor(CGAL::to_double(x));
	while (a > x) a -= 1;
	while (a+1 <= x) a += 1;
	if (a == 0) a = 0;
	return a;
}

double ceil_to_double(const Q& x) {
	double a = std::ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a-1 >= x) a -= 1;
	if (a == 0) a = 0;
	return a;
}

void function1(int a, int b) {
	Program qp (CGAL::SMALLER, true, 0, false, 0);

	// now set the non-default entries
	const int X = 0;
	const int Y = 1;
	qp.set_a(X, 0,  1); qp.set_a(Y, 0, 1); qp.set_b(0, 4);  //  x + y  <= 4
	qp.set_a(X, 1,  4); qp.set_a(Y, 1, 2); qp.set_b(1, a*b);  // 4x + 2y <= ab
	qp.set_a(X, 2, -1); qp.set_a(Y, 2, 1); qp.set_b(2, 1);  // -x +  y <= 1

	qp.set_d(X, X, 2*a); 
	qp.set_c(Y, -b);                                      

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(qp, ET());

	// output solution
	if(s.status() == CGAL::QP_INFEASIBLE) std::cout << "no" << std::endl;
	else if(s.status() == CGAL::QP_UNBOUNDED) std::cout << "unbounded" << std::endl;
	else  std::cout << std::setprecision(0) << std::fixed << floor_to_double(-s.objective_value()) << std::endl;

}

void function2(int a, int b) {
	Program qp (CGAL::SMALLER, false, 0, false, 0);
	// now set the non-default entries
	const int X = 0;
	const int Y = 1;
	const int T = 2;
	qp.set_a(X, 0, -1); qp.set_a(Y, 0,-1); qp.set_a(T, 0, 0); qp.set_b(0, 4);  
	qp.set_a(X, 1, -4); qp.set_a(Y, 1,-2); qp.set_a(T, 1,-1); qp.set_b(1, a*b); 
	qp.set_a(X, 2,  1); qp.set_a(Y, 2,-1); qp.set_a(T, 2, 0); qp.set_b(2, 1);
	qp.set_u(X, true, 0);
	qp.set_u(Y, true, 0);
	qp.set_l(T, true, 0);

	qp.set_d(X, X, 2*a); 
	qp.set_d(T, T, 2);
	qp.set_c(Y, b);                                      

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(qp, ET());

	// output solution
	if(s.status() == CGAL::QP_INFEASIBLE) std::cout << "no" << std::endl;
	else if(s.status() == CGAL::QP_UNBOUNDED) std::cout << "unbounded" << std::endl;
	else {
		Solution::Variable_value_iterator opt = s.variable_values_begin(); 
		Q z_squared = *(opt + T); 
		std::cout << std::setprecision(0) << std::fixed << ceil_to_double(s.objective_value()) << std::endl;
	}
}

int main() {
	int p, a, b; std::cin >> p;
	while(p != 0) {
		std::cin >> a >> b;
		if(p == 1) function1(a, b); else function2(a, b);
		std::cin >> p;
	}
	return 0;
}
