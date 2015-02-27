#include "ImplicitPlane.hpp"

using namespace Implicit;

Plane::Plane(float (*fieldFunc)(float), float radius) :
	Primitive(fieldFunc),
	m_color(ColorRGB(0, 0, 0)),
	m_radius(radius),
	m_radiusSq(radius*radius)
{ }

Plane::Plane(float (*fieldFunc)(float), ColorRGB color, float radius) :
	Primitive(fieldFunc),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius)
{}

Plane::Plane(float (*fieldFunc)(float), float coeff, ColorRGB color,
		float radius) :
	Primitive(fieldFunc, coeff),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius)
{}

float Plane::getFieldValue(glm::vec3 pt)
{
	return m_fieldCoefficient * m_fieldFunc(getDistanceSq(pt) / m_radius);
}

float Plane::getDistanceSq(glm::vec3 pt)
{
	return getDistance(pt) * getDistance(pt);
}

float Plane::getDistance(glm::vec3 pt)
{
	return pt.y < 0.f ? pt.y / m_radius : 0.f;
}

bool Plane::contains(glm::vec3 pt, float errorMargin)
{
	return pt.y < m_radius + errorMargin;
}


std::list<glm::vec3> Plane::getPointsInObject()
{
	return std::list<glm::vec3>();
}

PointFlavour Plane::getFlavour(glm::vec3 pt)
{
	return PointFlavour(m_color, glm::vec3(0.f, 1.f, 0.f));
}
