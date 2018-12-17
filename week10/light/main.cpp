#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;

typedef K::Point_2 P;
typedef std::vector<P> VP;
typedef std::vector<bool> VB;
typedef std::pair<P, long> Disk;
typedef std::vector<Disk> VDisk;

void testcase() {
	int n, m; std::cin >> m >> n;
	VDisk disks(m);
	VP lamps(n);
	for(int i = 0; i < m; i++) {
		int x, y; std::cin >> x >> y;
		P p = P(x, y); 
		int r; std::cin >> r;
		disks[i] = std::make_pair(p, r);
	}
	int h; std::cin >> h;
	for (std::size_t i = 0; i < n; ++i) {
		int x, y; std::cin >> x >> y;	
		P p = P(x, y);
		lamps[i] = p;
	}
	//Binary search the position where there is a winner (the biggest number that is not too big)
	int lmin = 0, lmax = n;
	Triangulation t_bin, t_next;
	int a = 0;
	while (lmin != lmax) {
		int p = (lmin + lmax + 1)/2;
		t_next.insert(lamps.begin() + a, lamps.begin() + p);
		
		bool isWinner = false;
		for(int i = 0; i < m; i++) {
			Vertex_handle v = t_next.nearest_vertex(disks[i].first);
			P p = v->point();
			if((h + disks[i].second)*(h + disks[i].second) <= CGAL::squared_distance(p, disks[i].first)) {
				isWinner = true;
				break;
			}
		}
		if (!isWinner) {
			lmax = p - 1;
			t_next = t_bin;
		} else {
			a = p;
			lmin = p;
			t_bin = t_next;
		}
	}

	Triangulation t;
	t.insert(lamps.begin(), lamps.begin() + lmin);
	if(lmin != 0) {
		VB winner(m, true);
		for(int i = 0; i < m; i++) {
			Vertex_handle v = t.nearest_vertex(disks[i].first);
			P p = v->point();
			if((h + disks[i].second)*(h + disks[i].second) > CGAL::squared_distance(p, disks[i].first)) {
				winner[i] = false;
			}
		}
		for(int i = 0; i < m; i++) {
			if(winner[i]) std::cout << i << " ";
		}
	}
	std::cout << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}


