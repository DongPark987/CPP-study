#include <iostream>
#include <vector>


using namespace std;

template <typename T>
void print(T arg) {
	std::cout << arg << std::endl;
}

template <typename T, typename... Types>
void print(T arg, Types... args) {
	std::cout << arg << ", ";
	print(args...);
}

template<typename... Arguments> class vtclass;

vtclass< > vtinstance1;
vtclass<int> vtinstance2;
vtclass<float, bool> vtinstance3;
vtclass<long, std::vector<int>, std::string> vtinstance4;


int main() {
	print(1, 3.1, "abc");
	print(1, 2, 3, 4, 5, 6, 7);


}