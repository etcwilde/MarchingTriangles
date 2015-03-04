
#include <iostream>

#include <glm/glm.hpp>

#include "fieldFunctions.hpp"
#include "Sphere.hpp"

void position(Implicit::Sphere s, glm::vec3 pt)
{
	float v = s.evaluate(pt);
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

std::ostream& operator<<(std::ostream& os, glm::vec3 v)
{
	os << '[' << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}

void test(Implicit::Sphere s, float r)
{
	std::cout << "Sphere: Radius: " << s.radius()  << " | Test radius: "
		<< r << '\n'
		<< "Geometric evaluation: " << s.evaluate(glm::vec3(r, 0, 0))
		<< '\n'
		<< "Field Function evaluation: " << s.getFieldFunc(r)
		<< '\n' << '\n';
}

int main()
{
	float r1 = 1.f;
	float r2 = 3.f;
	float r3 = 0.5f;

	Implicit::Sphere sphere(Implicit::inverseFunction);

	test(sphere, r1);
	test(sphere, r2);
	test(sphere, r3);


	/*position(sphere, glm::vec3(r1, 0, 0));
	position(sphere, glm::vec3(r2, 0, 0));
	position(sphere, glm::vec3(r3, 0, 0)); */




	/*std::cout << "Surface: " << r1 << " : " << Implicit::inverseFunction(r1) << '\n';
	std::cout << "Outside: " << r2 << " : " << Implicit::inverseFunction(r2) << '\n';
	std::cout << "Inside : " << r3 << " : " << Implicit::inverseFunction(r3) << '\n'; */

	return 0;
}
