
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

glm::vec3 geometric_project(Implicit::Sphere s, glm::vec3 pt)
{

	glm::vec3 N = glm::normalize(s.gradient(pt));
	return N * s.radius();

	/*
	glm::vec3 N;
	glm::vec3 T;
	glm::vec3 B;

	N = glm::normalize(s.gradient(pt));

	// Computer tangent space
	if (N.x > 0.5f || N.y > 0.5f) T = glm::vec3(N.y, -N.x, 0.f);
	else T = glm::vec3(-N.z, 0.f, N.x);
	B = glm::cross(N, T);
	T = glm::normalize(T);
	B = glm::normalize(B); */

/*
	std::cout << "Normal: " << N << '\n';
	std::cout << "Tangent: " << T << '\n';
	std::cout << "Binormal: " << B << '\n';

	std::cout << "Dot: " << glm::dot((pt - T), N) << '\n';
	std::cout << "DotN: " <<  glm::dot((pt - T), N) * N << '\n'; */

	//glm::vec3 out = (pt - (glm::dot((pt - T), N) * N));
	//std::cout << "Out: " << out << '\n';

	// Map to object
	//return out;
}

void test(Implicit::Sphere s, float r)
{
	glm::vec3 pt(r, 0, 0);
	std::cout << "Sphere: Radius: " << s.radius()  << " | Test radius: "
		<< r << '\n'
		<< "Geometric evaluation: " << s.evaluate(pt)
		<< '\n'
		<< "Field Function evaluation: " << s.getFieldFunc(r)
		<< '\n'
		<< "Mapped Point: Original Point: " << pt << " Projection: " <<
		geometric_project(s, pt) << '\n'
		<< "Geometric Project Test: "
		<< s.evaluate(geometric_project(s, pt))
		<< '\n' << '\n';
	pt = glm::vec3(0, r, r);
	std::cout << "Sphere: Radius: " << s.radius()  << " | Test radius: "
		<< r << '\n'
		<< "Geometric evaluation: " << s.evaluate(pt)
		<< '\n'
		<< "Field Function evaluation: " << s.getFieldFunc(r)
		<< '\n'
		<< "Mapped Point: Original Point: " << pt << " Projection: " <<
		geometric_project(s, pt) << '\n'
		<< "Geometric Project Test: "
		<< s.evaluate(geometric_project(s, pt))
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
