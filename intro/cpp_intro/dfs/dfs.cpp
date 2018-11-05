#include <iostream>
#include <stack>
#include <vector>
#include <set>

typedef std::vector<int> VI;
typedef std::vector<std::set<int> > VII;
typedef std::stack<int> SI;

int testcase() {
	int n, m, v; std::cin >> n >> m >> v;
	VII graph(n, std::set<int>());

	for(int i = 0; i < m; i++) {
		int a, b; std::cin >> a >> b;
		graph[a].insert(b);
		graph[b].insert(a);
	}	
	SI stack;
	stack.push(v);	
	int timestamp = 0;
	VI discovered(n, -1);
	VI finished(n, -1);	

	while(not stack.empty()) {
		int current = stack.top();
		if(discovered[current] == -1) {
			discovered[current] = timestamp++;
			for(auto it = graph[current].rbegin(); it != graph[current].rend(); it++) {
				if(discovered[*it] == -1) {
					stack.push(*it);
				}	
			}
		} else if (finished[current] == -1) {
			stack.pop();
			finished[current] = timestamp++;
		} else {
			stack.pop();
		}
	}

	for(int k : discovered) {
		std::cout << k << " ";
	}
	std::cout << std::endl;
	
	for(int k : finished) {
		std::cout << k << " ";
	}
	std::cout << std::endl;
}


int main() {
	int t; std::cin >> t;
	for(int i = 0; i < t; i++) { 
		testcase();
	}
}