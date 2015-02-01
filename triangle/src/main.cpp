#include <iostream>
#include "Vector.hpp"
#include "floatlibs.hpp"

#ifdef TEST

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include "../tests/vector_test.h"

#endif //TEST

int main()
{
#ifdef TEST
	CppUnit::TextUi::TestRunner vector_tests;
	vector_tests.addTest(Vector2DTest::suite());
	vector_tests.addTest(Vector3DTest::suite());
	vector_tests.addTest(Vector4DTest::suite());
	vector_tests.run();
#endif //TEST

	/*Vector3D<int> a(5, 6, 7);
	Vector3D<int> b(1, 2, 3);
	Vector3D<int> c;
	std::cout << 'a' << a << '\n';
	std::cout << 'b' << b << '\n';
	std::cout << "a + b " << a + b << '\n';
	std::cout << "a + b - b " << a + (b - b) << '\n'; */
	/*Vector3D<double> a(1, 2, 3);
	std::cout << a << '\n'; */

	Vector2D<int> a(1, 2);
	Vector2D<float> b(1.0, 2.4);
	return 0;
}
