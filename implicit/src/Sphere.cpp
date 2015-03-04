#include "Sphere.hpp"

using namespace Implicit;

Sphere::Sphere(float (*fieldFunc)(float)) :
	m_fieldFunc(fieldFunc),
	m_radius(1)
{ }

Sphere::Sphere(float (*fieldFunc)(float), float radius) :
	m_fieldFunc(fieldFunc),
	m_radius(radius)
{ }

float Sphere::radius()
{
	return m_radius;
}

float Sphere::evaluate(glm::vec3 p)
{
	return (p.x * p.x + p.y * p.y + p.z * p.z) - (m_radius * m_radius);
}

float Sphere::getFieldFunc(float r)
{
	return m_fieldFunc(r);
}


