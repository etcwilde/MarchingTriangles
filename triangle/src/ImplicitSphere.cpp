#include "ImplicitSphere.hpp"

using namespace Implicit;

Sphere::Sphere(float (*fieldFunc)(float), float radius) :
	Primitive(fieldFunc),
	m_color(ColorRGB(0, 0, 0)),
	m_radius(radius),
	m_radiusSq(radius*radius)
{ }

Sphere::Sphere(float (*fieldFunc)(float), ColorRGB color, float radius) :
	Primitive(fieldFunc),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius)
{ }

Sphere::Sphere(float (*fieldFunc)(float), float coeff, ColorRGB color,
				float radius) :
	Primitive(fieldFunc, coeff),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius)
{ }

float Sphere::getFieldValue(glm::vec3 pt)
{
	return m_fieldCoefficient * m_fieldFunc(getDistanceSq(pt)/m_radiusSq);
}

float Sphere::getDistanceSq(glm::vec3 pt)
{
	return (pt.x * pt.x) + (pt.y * pt.y) + (pt.z * pt.z);
}

float Sphere::getDistance(glm::vec3 pt)
{
	return std::sqrt(getDistanceSq(pt));
}

bool Sphere::contains(glm::vec3 pt, float errorMargin)
{
	return getDistanceSq(pt) < (m_radius + errorMargin) * (m_radius * errorMargin);
}

std::list<glm::vec3> Sphere::getPointsInObject()
{
	std::list<glm::vec3> result;
	result.push_back(glm::vec3(0, 0, 0));
	return result;
}

PointFlavour Sphere::getFlavour(glm::vec3 pt)
{
	return PointFlavour(m_color, normalize(pt));

}

