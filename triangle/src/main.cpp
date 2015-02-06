#include <iostream>
#include "floatlibs.hpp"

#include <glm/glm.hpp>
#include "Rectangle.hpp"
#include "Window.hpp"


#include <ctime>

#ifdef TEST

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>

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

	Window w(1024, 640, "GLFW test", NULL, NULL);
	//Window w(1024, 768, "GLFW test", NULL, NULL);
	w.mainloop();
	w.destroyWindow();
	return EXIT_SUCCESS;
}
