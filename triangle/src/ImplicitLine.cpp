#include "ImplicitLine.hpp"

using namespace Implicit;

Line::Line(float (*fieldFunc)(float), float radius, float length) :
	Primitive(fieldFunc),
	m_color(ColorRGB(0, 0, 0)),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_length(length),
	m_lengthSq(length*length),
	m_endPoint1(glm::vec3(length/-2.f, 0.f, 0.f)),
	m_endPoint2(glm::vec3(length/2.f, 0.f, 0.f))
{ }

Line::Line(float (*fieldFunc)(float), ColorRGB color, float radius,
		float length) :
	Primitive(fieldFunc),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_length(length),
	m_lengthSq(length*length),
	m_endPoint1(glm::vec3(length/-2.f, 0.f, 0.f)),
	m_endPoint2(glm::vec3(length/2.f, 0.f, 0.f))
{ }

Line::Line(float (*fieldFunc)(float), float coeff, ColorRGB color,
		float radius, float length) :
	Primitive(fieldFunc, coeff),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_length(length),
	m_lengthSq(length*length),
	m_endPoint1(glm::vec3(length/-2.f, 0.f, 0.f)),
	m_endPoint2(glm::vec3(length/2.f, 0.f, 0.f))
{ }


glm::vec3 Line::getNearestPoint(glm::vec3 pt)
{
	float proj = glm::dot(pt - m_endPoint1, m_endPoint2 - m_endPoint1) / m_lengthSq;
	if (proj < 0.f) return m_endPoint1;
	if (proj > 1.f) return m_endPoint2;
	return m_endPoint1 + proj* (m_endPoint2 - m_endPoint1);
}

float Line::getFieldValue(glm::vec3 pt)
{
	return m_fieldCoefficient * m_fieldFunc(getDistanceSq(pt)/(m_radiusSq));
}

float Line::getDistanceSq(glm::vec3 pt)
{
	// Treat it as a dot
	if (m_radiusSq <= 0.05f)
	{
		return
			((pt.x - m_endPoint1.x) * (pt.x - m_endPoint1.x)) +
			((pt.y - m_endPoint1.y) * (pt.y - m_endPoint1.y)) +
			((pt.z - m_endPoint1.z) * (pt.z - m_endPoint1.z));
	}
	glm::vec3 nearest = getNearestPoint(pt);
	return
		((pt.x - nearest.x) * (pt.x - nearest.x)) +
		((pt.y - nearest.y) * (pt.y - nearest.y)) +
		((pt.z - nearest.z) * (pt.z - nearest.z));
}

float Line::getDistance(glm::vec3 pt)
{
	return std::sqrt(getDistanceSq(pt));
}



bool Line::contains(glm::vec3 pt, float errorMargin)
{
	return getDistanceSq(pt) < ((m_radius + errorMargin) * (m_radius + errorMargin));
}
std::list<glm::vec3> Line::getPointsInObject()
{
	std::list<glm::vec3> result;
	result.push_back(glm::vec3(0.f, 0.f, 0.f));
	return result;
}

PointFlavour Line::getFlavour(glm::vec3 pt)
{
	glm::vec3 normal = pt - getNearestPoint(pt);
	return PointFlavour(m_color, normalize(normal));
}

