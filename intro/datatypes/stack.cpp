#include <iostream>
#include <stack>
#include <deque>

int main() {
	typedef std::stack<int> SI;
	typedef std::deque<int> DI;
	DI deque = {1,2,3,4,5};
	SI stack(deque);
	std::cout << stack.size() << std::endl;

	int last = stack.top();
	std::cout << last << std::endl;

	stack.push(10);
	stack.push(123);

	while(not stack.empty()) {
		std::cout << stack.top() << std::endl;
		stack.pop();
	}
}
