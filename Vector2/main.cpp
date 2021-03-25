#include "vector2.h"
int main() {
	Vector2d<double> v1, v2;
	v1 = {};
	v2 = {};
	double r;
	std::cout << "Vector 1: \n";
	std::cin >> v1;
	std::cout << "Vector 2: \n";
	std::cin >> v2;
	std::cout << "Sum: " << v1 + v2 << "\n";
	std::cout << "Difference: " << v1 - v2 << "\n";
	v2 *= 5;
	std::cout << "Vector 2 times 5: " << v2 << "\n";
	v2 /= 5;
	v2 += v1 * 2;
	std::cout << "Vector 2 plus double of vector 1: " << v2 << "\n";
	std::cout << "Half of vector 1: " << v1 / 2 << "\n";
	v2 -= v1 * 2;
	std::cout << "Dot product: " << dotprod(v1, v2) << "\n";
	std::cout << "Vector 2 mirrored vertically: " << mirrorvert(v2) << "\n";
	std::cout << "Vector 2 mirrored horizontally: " << mirrorhor(v2) << "\n";
	std::cout << "Length of vector 1: " << length(v1) << "\n";
	std::cout << "Normalized vector 1: " << norm(v1) << "\n";
	std::cout << "Rotate vector 1 by: (radians) \n";
	std::cin >> r;
	std::cout << rot(v1, r);
	return 0;
}