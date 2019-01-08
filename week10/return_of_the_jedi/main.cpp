#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

typedef std::pair<int,int> Node;
typedef std::priority_queue<Node, std::vector<Node>, std::greater<Node> > PQ;
typedef std::vector<int> VI;
typedef std::vector<VI> Graph;

int prim(Graph& G, VI& visited, PQ& pq, int& min_difference) {
	if(pq.empty()) return 0;
	Node curr = pq.top();
	pq.pop();
	int w = 0;
	int id = curr.second;
	if(visited[id] == false) {
		w = curr.first;
		visited[id] = true;

		//find min difference
		Node next = pq.top();
		min_difference = std::min(min_difference, next.first - w);

		for(int i = 0; i < G[id].size(); i++) {
			if(visited[i] == false) pq.push(std::make_pair(G[id][i], i));	
		}	
	}
	return w + prim(G, visited, pq, min_difference);
}

void testcase() {
	int n, start; std::cin >> n >> start;
	Graph G(n, VI(n, 0));
	for(int i = 0; i < n-1; i++) {
		for(int j = i+1; j < n; j++) {
			int a; std::cin >> a;
			G[i][j] = a;
			G[j][i] = a;
		}
	}
	VI visited(n, 0);
	PQ queue;
	queue.push(std::make_pair(0, start-1));
	int min_difference = std::numeric_limits<int>::max();
	std::cout << prim(G, visited, queue, min_difference) + min_difference << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();
	return 0;
}
