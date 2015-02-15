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

/**
 * \mainpage Marching Triangles Documentation
 *
 *
 * The marching triangles algorithm is a polygonization algorithm, like the
 * marching cubes algorithm. Given an implicit surface, it will generate a
 * triangle mesh. It works by creating a seed triangle at some point on the
 * surface, then begins to grow like a mold until the surface is covered.
 *
 * Basic Layout:
 * The Window contains a World
 * The World contains all of the objects in the scene, and the Camera.
 * The Camera handles user movement through the scene and handles most of the
 * OpenGL calls for processing the viewport matrices including the View matrix
 * and the Perspective matrix.
 *
 * This program makes use of the glm matrix libraries.
 *
 * \author Evan Wilde <etcwilde@uvic.ca>
 */

int main()
{
#ifdef TEST
	/*CppUnit::TextUi::TestRunner vector_tests;
	vector_tests.addTest(Vector2DTest::suite());
	vector_tests.addTest(Vector3DTest::suite());
	vector_tests.addTest(Vector4DTest::suite());
	vector_tests.run(); */
#endif //TEST

	Window w(1024, 640, "Marching Triangles", NULL, NULL);
	w.mainloop();
	w.destroyWindow();
	return EXIT_SUCCESS;
}
