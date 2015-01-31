#include <iostream>
#include "Vector.hpp"

int main()
{
	Vector3D<int> a(5, 6, 7);
	Vector3D<int> b(1, 2, 3);
	Vector3D<int> c;
	std::cout << 'a' << a << '\n';
	std::cout << 'b' << b << '\n';
	std::cout << "a + b " << a + b << '\n';
	std::cout << "a + b - b " << a + (b - b) << '\n';
	return 0;
}
