// ALGOLAB BGL Tutorial 2
// Flow example demonstrating
// - interior graph properties for flow algorithms
// - custom edge adder

// Compile and run with one of the following:
// g++ -std=c++11 -O2 flows.cpp -o flows ./flows
// g++ -std=c++11 -O2 -I path/to/boost_1_58_0 flows.cpp -o flows; ./flows

// Includes
// ========
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <utility>
// BGL includes
#include <boost/functional/hash.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
// Namespaces
// using namespace std;
// using namespace boost;


// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	boost::adjacency_list_traits<boost::setS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::setS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
// Interior Property Maps
typedef	boost::property_map<Graph, boost::edge_capacity_t>::type		EdgeCapacityMap;
typedef	boost::property_map<Graph, boost::edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	boost::property_map<Graph, boost::edge_reverse_t>::type		ReverseEdgeMap;
typedef	boost::graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	boost::graph_traits<Graph>::edge_descriptor			Edge;
typedef	boost::graph_traits<Graph>::edge_iterator			EdgeIt;

typedef std::string S;
typedef std::vector<int> VI;
typedef std::vector<VI> VII;
typedef std::vector<char> VC;
typedef std::vector<VC> VCC;
typedef std::pair<int, int> P;
typedef std::map<P, int> Map;

int LETTERS = 26;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	void addEdge(int from, int to, long capacity) {
		Edge e, rev_e;
		bool success;
		boost::tie(e, success) = boost::add_edge(from, to, G);
		boost::tie(rev_e, success) = boost::add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[rev_e] = 0; // reverse edge has no capacity!
		revedgemap[e] = rev_e;
		revedgemap[rev_e] = e;
	}
};


// Functions
// =========
// Function for an individual testcase
void testcases() {
	// Create Graph and Maps
	int V = LETTERS*LETTERS + LETTERS + 2;
	Graph G(V);
	Vertex source = V-2;
	Vertex target = V-1;
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);
	
	int h, w; std::cin >> h >> w;
	S note; std::cin >> note;
	int n = note.size();
	
	VII matrix(LETTERS, VI(LETTERS, 0));

	VCC front(h, VC(w)), back(h, VC(w));
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			std::cin >> front[i][j];
		}
	}
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			std::cin >> back[i][w-j-1];
		}
	}
	
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			int a = front[i][j] - 'A', b = back[i][j] - 'A';
			matrix[a][b]++;
		}
	}

	for(int i = 0; i < LETTERS; i++) {
		for(int j = 0; j < LETTERS; j++) {
			eaG.addEdge(source, i*LETTERS + j, matrix[i][j]);
			eaG.addEdge(i*LETTERS + j, LETTERS*LETTERS + i, matrix[i][j]);
			eaG.addEdge(i*LETTERS + j, LETTERS*LETTERS + j, matrix[i][j]);
		}
	}

	VI out(LETTERS, 0);
	for(int i = 0; i < n; i++) {
		out[note[i] - 'A']++;
	}
	for(int i = 0; i < LETTERS; i++) {
		eaG.addEdge(LETTERS*LETTERS + i, target, out[i]);
	}

	// Calculate flow
	// If not called otherwise, the flow algorithm uses the interior properties
	// - edge_capacity, edge_reverse (read access),
	// - edge_residual_capacity (read and write access).
	long flow1 = boost::push_relabel_max_flow(G, source, target);

	if(flow1 == n) std::cout << "Yes" << std::endl;
	else std::cout << "No" << std::endl;

}

// Main function to loop over the testcases
int main() {
	std::ios_base::sync_with_stdio(false);
	int T;	std::cin >> T;
	for (; T > 0; --T)	testcases();
	return 0;
}
