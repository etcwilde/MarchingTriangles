/**
 * main
 *
 * File: 	main.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Jan 30 2015
 */

#include <ctime>
#include <iostream>

#include <glm/glm.hpp>

#include "Window.hpp"
#include "fieldFunctions.hpp"
#include "floatlibs.hpp"

#include "ImplicitSystem.hpp"
#include "Snowman.hpp"

#include "fieldFunctions.hpp"

// FIXME remove this once we get rid of dumb find
#include <cstdlib>

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
 * Window Structuring:
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

// Hahahahahahaha -- this is dumb
float dumb_find(Implicit::Object* obj, int x, int y, int z, unsigned short trials)
{
	float value = 1.f;
	double range = 10;
	float t_x, t_y, t_z;
	//float val = obj->getFieldValue(glm::vec3(x, y, z));
	/*std::cout << "Value at: " << x << ", " << y << ", " << z << '\t';
	std::cout << val << '\n';*/
	/*while (trials)
	{
		std::cout << "Trial: " << trials << '\n';
		t_x = x + range * (rand() - 0.5);
		t_y = y + range * (rand() - 0.5);
		t_z = z + range * (rand() - 0.f);
		value = obj->getFieldValue(glm::vec3(t_x, t_y, t_z));
		std::cout << t_x << ", " << t_y << ", " << t_z << ", " <<
			"Value: " << value << '\n';
		if (value == 0) return value;
		range *= 1.005;
		trials--;
	}*/
	return value;
}

int main()
{
#ifdef TEST
	/*CppUnit::TextUi::TestRunner vector_tests;
	vector_tests.addTest(Vector2DTest::suite());
	vector_tests.addTest(Vector3DTest::suite());
	vector_tests.addTest(Vector4DTest::suite());
	vector_tests.run(); */
#endif //TEST

	Implicit::Sphere test(solidFunction, 2.f);
	dumb_find(&test, 0, 5, 0, 1000);
	Window w(1024, 640, "Marching Triangles", NULL, NULL);
	w.mainloop();
	w.destroyWindow();
	return EXIT_SUCCESS;
}
