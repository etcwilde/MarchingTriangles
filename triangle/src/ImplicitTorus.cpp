#include "ImplicitTorus.hpp"

using namespace Implicit;

Torus::Torus(float (*fieldFunc)(float), float innerRadius, float outerRadius) :
	Primitive(fieldFunc),
	m_color(ColorRGB(0, 0, 0)),
	m_innerRadius(innerRadius),
	m_outerRadius(outerRadius)
{
	m_width = outerRadius - innerRadius;
	m_widthSq = m_width * m_width;
	m_centerRadius = innerRadius + m_width  / 2;
}
Torus::Torus(float (*fieldFunc)(float), ColorRGB color, float innerRadius, 
		float outerRadius) :
	Primitive(fieldFunc),
	m_color(color),
	m_innerRadius(innerRadius),
	m_outerRadius(outerRadius)

{
	m_width = outerRadius - innerRadius;
	m_widthSq = m_width * m_width;
	m_centerRadius = innerRadius + m_width  / 2;
}


Torus::Torus(float (*fieldFunc)(float), float coeff, ColorRGB color, 
		float innerRadius, float outerRadius) :
	Primitive(fieldFunc, coeff),
	m_color(color),
	m_innerRadius(innerRadius),
	m_outerRadius(outerRadius)

{
	m_width = outerRadius - innerRadius;
	m_widthSq = m_width * m_width;
	m_centerRadius = innerRadius + m_width  / 2;
}

glm::vec3 Torus::getNearestPoint(glm::vec3 pt)
{
	// project
	pt.z = 0;
	return glm::normalize(pt) * m_centerRadius;
}

float Torus::getFieldValue(glm::vec3 pt)
{
	return m_fieldCoefficient * m_fieldFunc(getDistanceSq(pt)/(m_widthSq*.25f));
}

float Torus::getDistanceSq(glm::vec3 pt)
{
	glm::vec3 nearest = getNearestPoint(pt);
	return (
			((pt.x - nearest.x) * (pt.x - nearest.x)) +
			((pt.y - nearest.y) * (pt.y - nearest.y)) +
			((pt.z - nearest.z) * (pt.z - nearest.z)));


}

float Torus::getDistance(glm::vec3 pt)
{
	return std::sqrt(getDistanceSq(pt));
}

bool Torus::contains(glm::vec3 pt, float errorMargin)
{
	return getDistanceSq(pt) <= ((m_width/2)+errorMargin)*((m_width/2)+errorMargin);
}

std::list<glm::vec3> Torus::getPointsInObject()
{
	std::list<glm::vec3>points;
	points.push_back(glm::vec3(m_centerRadius, 0.f, 0.f));
	return points;
}

PointFlavour Torus::getFlavour(glm::vec3 pt)
{
	glm::vec3 normal = pt - getNearestPoint(pt);
	return PointFlavour(m_color, glm::normalize(normal));
}

