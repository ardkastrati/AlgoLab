#include <iostream>

struct Edge {
	int start, end;
	double weight;
	int visited;
	
	//Construtor
	Edge(int s, int e, double w, int v) :
		start(s), end(e), weight(w), visited(v)
	{}
};

int main() { 
	Edge e(0, 1, 0.5, 0);
	std::cout << e.start << " " << e.end << " " << e.weight << " " << e.visited << std::endl;
}
