#include <iostream>
#include "Vector.hpp"
#include "Matrix.hpp"
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

	Matrix2x2<double> ident;
	Matrix2x2<double> other(1, 2, 3, 4);
	Matrix2x2<double> double_mat(2, 0, 0, 2);
	std::cout << ident << '\n';
	other *= ident;
	std::cout << other << '\n';
	other *= double_mat;
	std::cout << other << '\n';

	return 0;
}
