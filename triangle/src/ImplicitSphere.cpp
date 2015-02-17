#include "ImplicitSphere.hpp"

using namespace Implicit;

Sphere::Sphere(float(*fieldFunc)(float), float radius) :
	ImplicitModel(fieldFunc),
	m_color(),
	m_radius(radius),
	m_radiusSq(radius * radius)
{ }

Sphere::Sphere(float(*fieldFunc)(float), ColorRGB color, float radius) :
	ImplicitModel(fieldFunc),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius * radius)
{ }

Sphere::Sphere(float(*fieldFunc)(float), float coeff, ColorRGB color, float radius) :
	ImplicitModel(fieldFunc, coeff),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius * radius)
{ }

float Sphere::getFieldValue(vec3 pt)
{
	return m_coeff * m_fieldFunc(getDistanceSq(pt) / m_radiusSq);
}

float Sphere::getDistanceSq(vec3 pt)
{
	return (pt.x * pt.x + pt.y * pt.y + pt.z * pt.z);
}

bool Sphere::contains(vec3 pt, float tolerance)
{
	return getDistanceSq(pt) <
		(m_radius + tolerance) * (m_radius + tolerance);
}

Point Sphere::getPoint(vec3 pt)
{
	return Point(m_color, normalize(pt));
}

