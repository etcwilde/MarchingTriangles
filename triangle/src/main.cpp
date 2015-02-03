#include <iostream>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "floatlibs.hpp"

#include <glm/glm.hpp>

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
	CppUnit::TextUi::TestRunner vector_tests;
	vector_tests.addTest(Vector2DTest::suite());
	vector_tests.addTest(Vector3DTest::suite());
	vector_tests.addTest(Vector4DTest::suite());
	vector_tests.run();
#endif //TEST

	/*Matrix2x2<double> ident;
	Matrix2x2<double> other(1, 2, 3, 4);
	Matrix2x2<double> double_mat(2, 0, 0, 2);
	std::cout << ident << '\n';
	other *= ident;
	std::cout << other << '\n';
	other *= double_mat;
	std::cout << other << '\n'; */

	unsigned int glm_time = 0;
	unsigned int my_time = 0;

	for (unsigned int repeats = 0; repeats < 10000; ++repeats)
	{

		clock_t glm_start_time = clock();
		glm::vec3 ga(1, 0, 0);
		glm::vec3 gb(2, 2, 2);

		glm::vec3 gc = glm::cross(ga, gb);
		gc = glm::cross(gb, ga);
		int gd = glm::dot(ga, gb);
		float g_length = glm::length(gb);
		glm::vec3 g_norm = glm::normalize(gb);

		for (unsigned int i = 0; i < 1000; ++i) 
			ga += glm::vec3(1, 2, 3);
		for (unsigned int i = 0; i < 1000; ++i) 
			ga -= glm::vec3(1, 2, 3);

		clock_t glm_end_time = clock();

		Vector3D<int> a(1, 0, 0);
		Vector3D<int> b(2, 2, 2);

		Vector3D<int> c = a.Cross(b);
		c = b.Cross(a);
		int dot = a.Dot(b);
		float len = b.Length();
		Vector3D<int> norm = b.Normalized();

		for (unsigned int i = 0; i < 1000; ++i) 
			a += Vector3D<int> (1, 2, 3);
		for (unsigned int i = 0; i < 1000; ++i) 
			a -= Vector3D<int> (1, 2, 3);

		clock_t end_time = clock();
		glm_time += (unsigned int)(glm_end_time - glm_start_time);
		my_time += (unsigned int)(end_time - glm_end_time);
	}
	glm_time / 10000;
	my_time / 10000;



	//std::cout << "start: " << glm_start_time << '\t' << "glm_end: " << glm_end_time << '\t' << "total end: " << end_time << '\n';
	std::cout << "GLM runtime:\t" << glm_time << '\n' << "My runtime:\t" << my_time << '\n';



	/*glm::vec3 a(1, 0, 0);
	glm::vec3 b(2, 2, 2);
	glm::vec3 c = glm::cross(a, b);


	std::cout << glm::dot(a, b) << '\n';
	std::cout << c[0] << c[1] << c[2] << '\n';
	std::cout << glm::length(a) << '\n';
	std::cout << glm::length(b) << '\n'; */
	return 0;
}
