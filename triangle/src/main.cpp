#include <iostream>
#include "floatlibs.hpp"

#include <glm/glm.hpp>
#include "Rectangle.hpp"


#include <ctime>

#ifdef TEST

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include "../tests/vector_test.h"

#endif //TEST

int main()
{
#ifdef TEST
	/*CppUnit::TextUi::TestRunner vector_tests;
	vector_tests.addTest(Vector2DTest::suite());
	vector_tests.addTest(Vector3DTest::suite());
	vector_tests.addTest(Vector4DTest::suite());
	vector_tests.run(); */
#endif //TEST

	Rectangle rect(0, 0, 1, 2);
	std::cout << rect.area() << '\t' << rect.perimeter() << '\n';
	std::cout << "Rectangle: " << rect.width() << 'x' << rect.height() << '\n';

	return 0;
}
