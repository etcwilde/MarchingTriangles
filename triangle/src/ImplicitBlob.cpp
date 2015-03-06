#include "ImplicitBlob.hpp"

using namespace Implicit;

Blob::Blob(FieldFunction fieldFunc, float iso) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_iso(iso),
	m_center(),
	m_max_distance(1)
{ }

Blob::Blob(FieldFunction fieldFunc, float iso,
		float max_distance) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_iso(iso),
	m_center(),
	m_max_distance(max_distance)
{ }

Blob::Blob(FieldFunction fieldFunc, float iso, glm::vec3 center) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_iso(iso),
	m_center(center),
	m_max_distance(1)
{ }

Blob::Blob(FieldFunction fieldFunc, float iso,
				glm::vec3 center, float max_distance) :
	m_fieldFunc(fieldFunc),
	m_iso(iso),
	m_center(center),
	m_max_distance(max_distance)
{ }

float Blob::getFieldValue(glm::vec3 pt) const
{
	return m_fieldFunc(getDistance(pt), m_max_distance);
}

float Blob::getDistance(glm::vec3 pt) const
{
	return glm::length(pt - m_center);
}

glm::vec3 Blob::getStartPoint() const
{
	return project_to_surface(getCenter());
};

glm::vec3 Blob::getCenter() const
{
	return m_center;
}

glm::vec3 Blob::project_to_surface(glm::vec3 g0) const
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
	static const float eps = 0.001f;

	float dx = getFieldValue(T * eps);
	float dy = getFieldValue(N * eps);
	float dz = getFieldValue(B * eps);

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

	return direction * distance;
}

#define ROOT_ITERS 100
#define ROOT_EPS 0.000001f

float Blob::findRoot(float r) const
{
	float xi;
	float xi1 = r + 1;
	float xi2 = r;

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

float Blob::evaluate(float r) const
{
	return m_fieldFunc(r, m_max_distance) - m_iso;
}


