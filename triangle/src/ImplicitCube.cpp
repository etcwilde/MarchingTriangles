#include "ImplicitCube.hpp"

using namespace Implicit;

Cube::Cube(float (*fieldFunc)(float), float radius, float sides) :
	Primitive(fieldFunc),
	m_color(ColorRGB(128, 128, 128)),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_x(sides/2.f),
	m_y(sides/2.f),
	m_z(sides/2.f)
{}
Cube::Cube(float (*fieldFunc)(float), ColorRGB color, float radius, float sides) :
	Primitive(fieldFunc),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_x(sides/2.f),
	m_y(sides/2.f),
	m_z(sides/2.f)
{}
Cube::Cube(float (*fieldFunc)(float), float coeff, ColorRGB color, float radius, float sides) :
	Primitive(fieldFunc, coeff),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_x(sides/2.f),
	m_y(sides/2.f),
	m_z(sides/2.f)
{}
Cube::Cube(float (*fieldFunc)(float), float radius, float x, float y, float z) :
	Primitive(fieldFunc),
	m_color(ColorRGB(128, 128, 128)),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_x(x/2.f),
	m_y(y/2.f),
	m_z(z/2.f)
{}
Cube::Cube(float (*fieldFunc)(float), ColorRGB color, float radius, float x, float y, float z) :
	Primitive(fieldFunc),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_x(x/2.f),
	m_y(y/2.f),
	m_z(z/2.f)
{}
Cube::Cube(float (*fieldFunc)(float), float coeff, ColorRGB color, float radius, float x, float y, float z) :
	Primitive(fieldFunc, coeff),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_x(x/2.f),
	m_y(y/2.f),
	m_z(z/2.f)
{}

float Cube::getFieldValue(glm::vec3 pt)
{
	return m_fieldCoefficient * m_fieldFunc((getDistanceSq(pt)/(m_radiusSq)));
}


glm::vec3 Cube::getNearestPoint(glm::vec3 pt)
{
	return glm::vec3((pt.x < -m_x) ? -m_x : ((pt.x > m_x) ? m_x : pt.x),
			(pt.y < -m_y) ? -m_y : ((pt.y > m_y) ? m_y : pt.y),
			(pt.z < -m_z) ? -m_z : ((pt.z > m_z) ? m_z : pt.z));
}

float Cube::getDistanceSq(glm::vec3 pt)
{
	glm::vec3 nearest = getNearestPoint(pt);
	return ((pt.x - nearest.x) * (pt.x - nearest.x)) +
		((pt.y - nearest.y) * (pt.y - nearest.y)) +
		((pt.z - nearest.z) * (pt.z - nearest.z));
}

float Cube::getDistance(glm::vec3 pt)
{
	return std::sqrt(getDistanceSq(pt));
}

bool Cube::contains(glm::vec3 pt, float errorMargin)
{
	return getDistanceSq(pt) < ((m_radius + errorMargin) * (m_radius + errorMargin));
}

std::list<glm::vec3> Cube::getPointsInObject()
{
	std::list<glm::vec3> l;
	l.push_back(glm::vec3(0.f, 0.f, 0.f));
	return l;
}

PointFlavour Cube::getFlavour(glm::vec3 pt)
{
	glm::vec3 normal = pt - getNearestPoint(pt);
	if (glm::length(normal) < 0.01f) // FLT_MIN
	{
		if (std::abs(pt.x) > std::abs(pt.y) &&
				std::abs(pt.x) > std::abs(pt.z))
		{
			return PointFlavour(m_color, glm::vec3(pt.x, 0.f, 0.f));
		}
		else if (std::abs(pt.y) > std::abs(pt.z))
		{
			return PointFlavour(m_color, glm::vec3(0.f, pt.y, 0.f));
		}
		else return PointFlavour(m_color, glm::vec3(0.f, 0.f, pt.z));
	}
}
