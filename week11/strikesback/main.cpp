#include <iostream>
#include <cassert>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;

// choose exact integral type
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef K::Point_2 P;

typedef std::vector<int> VI;
typedef std::vector<long> VL;
typedef std::vector<P> VP;

void testcase() {
	int a, s, b; std::cin >> a >> s >> b;
	double e; std::cin >> e;
	VP ap(a);
	VI ad(a);

	VP sp(s);

 	VP bp(b);

	for(int i = 0; i < a; i++) std::cin >> ap[i] >> ad[i];
	for(int i = 0; i < s; i++) std::cin >> sp[i];
	for(int i = 0; i < b; i++) std::cin >> bp[i];

	Triangulation t;
	t.insert(bp.begin(), bp.end());

	VL sr(s);
	for(int i = 0; i < s; i++) {
		Vertex_handle v = t.nearest_vertex(sp[i]);
		if(v != NULL) sr[i] = (long) CGAL::squared_distance(v->point(), sp[i]);	
		else sr[i] = -1;
	}

	// by default, we have a nonnegative LP with Ax >= b
	Program lp (CGAL::LARGER, true, 0, false, 0);

	for(int i = 0; i < a; i++) {
		for(int j = 0; j < s; j++) {
			long d = (long) CGAL::squared_distance(ap[i], sp[j]);
			if(sr[j] == -1 || d < sr[j]) {
				long denom = d == 0 ? 1 : d;
				lp.set_a(j, i, ET(1)/denom);	
			} else {
				lp.set_a(j, i, 0);
			}
		}
		lp.set_b(i, ad[i]);
	}

	for(int i = 0; i < s; i++) {
		lp.set_c(i, 1);
	}

	// solve the program, using ET as the exact type
	Solution solution = CGAL::solve_nonnegative_linear_program(lp, ET());
	if(solution.is_infeasible()) {
		std::cout << "n" << std::endl;
	} else if (CGAL::to_double(solution.objective_value()) <= e) {
		std::cout << "y" << std::endl;	
	} else {
		std::cout << "n" << std::endl;
	}
}


int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
