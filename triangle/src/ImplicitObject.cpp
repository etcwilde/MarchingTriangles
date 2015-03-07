#include "ImplicitObject.hpp"

#ifdef DEBUG
#include <iostream>
#endif

using namespace Implicit;

void Object::get_tangent_space(const glm::vec3& N, glm::vec3& T, glm::vec3& B) const
{
	if (N.x > 0.5f || N.y > 0.5f) T = glm::vec3(N.y, -N.x, 0.f);
	else T = glm::vec3(-N.z, 0.f, N.x);
	B = glm::cross(N, T);
	T = glm::normalize(T);
	B = glm::normalize(B);
}

#define ROOT_ITERS 100
#define ROOT_EPS 0.000001f

float Object::findRoot(float r)
{
	float xi;
	register float xi1 = r + 1;
	register float xi2 = r;

	for (unsigned int i = 0; i < ROOT_ITERS; ++i)
	{
		register float fxi1 = evaluate(xi1);
		register float fxi2 = evaluate(xi2);
		xi = xi1 - fxi1 * ((xi1 - xi2) / (fxi1 - fxi2));
#ifdef DEBUG
		std::cout
			<< "i: " << i + 1
			<< " xi: " << xi
			<< " xi1: " << xi1
			<< " xi2: " << xi2
			<< '\n';
#endif
		if (xi == xi1) break;
		xi2 = xi1; xi1 = xi;
	}
	return xi;
}

glm::vec3 Object::project_to_surface(glm::vec3 g0)
{
	// Get direction of most change
	glm::vec3 N = glm::vec3(0, 1, 0);
	glm::vec3 T;
	glm::vec3 B;
	get_tangent_space(N, T, B);

#ifdef DEBUG
	std::cout << "Normal: " << N << '\n';
	std::cout << "Tangent: " << T << '\n';
	std::cout << "Binormal: " << B << '\n';
#endif
	const float eps = 0.001f;

	float dx = getFieldValue(g0 + (T * eps));
	float dy = getFieldValue(g0 + (N * eps));
	float dz = getFieldValue(g0 + (B * eps));

#ifdef DEBUG
	std::cout << "Dx: " << dx << "\tDy: " << dy << "\tDz: " << dz <<'\n';
#endif
	glm::vec3 direction = glm::normalize(glm::vec3(dx, dy, dz));

#ifdef DEBUG
	std::cout << "Movement direction: " << direction << '\n';
	std::cout << getFieldValue((direction * eps) + g0) << '\n';
#endif
	float distance = 1.f;
	distance = findRoot(distance);
	return g0 + direction * distance;


}
