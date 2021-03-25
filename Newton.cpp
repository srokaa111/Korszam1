#include <stdlib.h>
#include <iostream>
template<typename A, typename B,typename T>
void Newton(A f1, B f2,T x0,T done) {
	T x1 = x0, x2;
	int i = 0;
	std::cout.precision(16);
	while (true) {
		x2 = x1;
		x1 = x2 - (f1(x2) / f2(x2));
		i++;
		if (abs(x1 - x2) < done || i == 10000) {
			std::cout << x1;
				break;
		}
	}
}
int main() {
	Newton([](int x) { return x* x - 111;}, [](int x){ return 2.0 * x;}, 10.0,0.00001);
	return 0;
}