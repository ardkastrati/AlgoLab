#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Triangle_2 T;

typedef std::vector<int> VI;
typedef std::vector<VI> VII;
typedef std::vector<P> VP;

double ceil_to_double(const K::FT& x) {
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a - 1 >= x) a -= 1; 
  return a;
}

void testcase() {
    
    int m, n; std::cin >> m >> n;
    
    VP path;
    for(int i = 0; i < m; i++) {
        int x, y; std::cin >> x >> y;
        P p(x,y);
        path.push_back(p);
    }
    
    VII triangleCovers(n);
    for(int i = 0; i < n; i++) {
        int a, b;
       	VP triangle; 
	for(int j = 0; j < 6; j++) {
		int a, b; std::cin >> a >> b;
		P p(a, b);
		triangle.push_back(p);
	}

	for(int j = 0; j < 3; j++) {
		if(CGAL::right_turn(triangle[2*j], triangle[2*j +1], triangle[(2*j +2) % 6])) {
			std::swap(triangle[2*j], triangle[2*j+1]);
		}
	}
        
        for(int j = 0; j < m-1; j++) {
            P p1 = path[j];
            P p2 = path[j+1];
    
            if(!CGAL::right_turn(triangle[0], triangle[1], p1) && !CGAL::right_turn(triangle[2], triangle[3], p1) && !CGAL::right_turn(triangle[4], triangle[5], p1) &&
               !CGAL::right_turn(triangle[0], triangle[1], p2) && !CGAL::right_turn(triangle[2], triangle[3], p2) && !CGAL::right_turn(triangle[4], triangle[5], p2)) {
                triangleCovers[i].push_back(j);
            }
        }
    }
    //Slide Window
    int totalCovered = 0;
    VI leg_coverage(m-1, 0);
    
    int left = 0, right = 0;
    int bestSolution = n;

    while(left < n) {
        
        if(totalCovered == (m - 1) && (right - left) < bestSolution) bestSolution = right - left;
        if(totalCovered == (m-1)) {
            for(int i = 0; i < triangleCovers[left].size(); i++){
                leg_coverage[triangleCovers[left][i]]--;
                if(leg_coverage[triangleCovers[left][i]] == 0)  totalCovered--;
            }
            left++; 
        } else {
            if(right < n) {
                for(int i = 0; i < triangleCovers[right].size(); i++) {
                    if(leg_coverage[triangleCovers[right][i]] == 0) totalCovered++;
                    leg_coverage[triangleCovers[right][i]]++;
                }
		right++;	
            } else {
		break;
	    }
        }
    }
    std::cout << bestSolution << std::endl;
}


int main(void) {
    std::ios_base::sync_with_stdio(false);
    int T; std::cin >> T;
    while(T--) testcase(); 
    return 0;
}
