#include <iostream>
#include <queue>

int main() {
	typedef std::queue<int> QI;
	typedef std::deque<int> DI;
	DI test = {1,2,3,4,5,6,7};
	QI a;
	QI b(test);

	std::cout << b.front() << std::endl;
	b.push(19);
	std::cout << b.size() << std::endl;
	std::cout << b.front() << std::endl;
	std::cout << b.back() << std::endl;

	b.pop();
	std::cout << b.front() << " " << b.back() << std::endl;
}
