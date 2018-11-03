#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;
int main() {
	std::map<int, vector<int> > test;
	vector<int> tt = {1,2,3};
	test.insert(make_pair(2, tt)); 
	//std::cout << test[2] << std::endl;
}

