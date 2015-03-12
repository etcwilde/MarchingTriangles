
#include <iostream>

#include <glm/glm.hpp>

#include "fieldFunctions.hpp"
#include "Sphere.hpp"

std::ostream& operator<<(std::ostream& os, glm::vec3 v)
{
	os << '[' << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}

void position(Implicit::Sphere s, glm::vec3 pt)
{
	float v = trunc(s.evaluate(pt));
	if (v == 0)
	{
		std::cout << "[ "
		<< pt.x << ", "
		<< pt.y << ", "
		<< pt.z << " ] is on sphere\n";
	}
	else if(v < 0)
	{
		std::cout << "[ "
		<< pt.x << ", "
		<< pt.y << ", "
		<< pt.z << " ] is inside sphere\n";
	}
	else if(v > 0)
	{
		std::cout << "[ "
		<< pt.x << ", "
		<< pt.y << ", "
		<< pt.z << " ] is outside sphere\n";
	}

}






void test(Implicit::Sphere s, float r)
{

	srand(time(NULL));
	glm::vec3 delta(rand() /(float) rand(),rand() /(float) rand(),rand() /(float) rand() );
	glm::vec3 pt(r, 0, 0);
	glm::vec3 proj;

	std::cout << "Test Sphere: " << s.radius() << '\n';
	std::cout << "Testing: " << pt << '\n';
	std::cout << "Geometric Value: " << s.evaluate(pt) << '\n';
	std::cout << "Distance: " << s.distance(pt) << '\n';
	std::cout << "Field: " << s.getFieldValue(s.distance(pt)) << '\n';
	position(s, pt);
	proj = s.project(pt);
	std::cout << "Projection: " << proj << '\n';
	std::cout << "Geometric Value: " << s.evaluate(proj) << '\n';
	std::cout << "Distance: " << s.distance(proj) << '\n';
	std::cout << "Field: " << s.getFieldValue(s.distance(proj)) << '\n';
	position(s, proj);
	std::cout << '\n';


	pt = pt + delta;
	std::cout << "Testing: " << pt << '\n';
	std::cout << "Geometric Value: " << s.evaluate(pt) << '\n';
	std::cout << "Distance: " << s.distance(pt) << '\n';
	std::cout << "Field: " << s.getFieldValue(s.distance(pt)) << '\n';
	position(s, pt);
	proj = s.project(pt);
	std::cout << "Projection: " << proj << '\n';
	std::cout << "Geometric Value: " << s.evaluate(proj) << '\n';
	std::cout << "Distance: " << s.distance(proj) << '\n';
	std::cout << "Field: " << s.getFieldValue(s.distance(proj)) << '\n';
	position(s, proj);
	std::cout << '\n' << '\n' << '\n';

}

int main()
{
	float r1 = 1.f;
	float r2 = 3.f;
	float r3 = 0.5f;

	Implicit::Sphere sphere(Implicit::metaballFunction);
	Implicit::Sphere s2(Implicit::metaballFunction, 2);

	std::cout << "--------- Test 1 Sphere radius 1 -------------\n";
	test(sphere, 0.0f);
	test(sphere, r1);
	test(sphere, r2);
	test(sphere, r3);
	std::cout << "--------- Test 2 Sphere radius 2 -------------\n";
	test(s2, r1);
	test(s2, r2);
	test(s2, r3);


	/*position(sphere, glm::vec3(r1, 0, 0));
	position(sphere, glm::vec3(r2, 0, 0));
	position(sphere, glm::vec3(r3, 0, 0)); */

	/*std::cout << "Surface: " << r1 << " : " << Implicit::inverseFunction(r1) << '\n';
	std::cout << "Outside: " << r2 << " : " << Implicit::inverseFunction(r2) << '\n';
	std::cout << "Inside : " << r3 << " : " << Implicit::inverseFunction(r3) << '\n'; */

	return 0;
}
