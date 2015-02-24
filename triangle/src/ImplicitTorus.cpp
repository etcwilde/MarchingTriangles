#include "ImplicitTorus.hpp"

using namespace glm;
using namespace Implicit;

Torus::Torus(float(*fieldFunc)(float), float innerRadius, float outerRadius) :
	ImplicitModel(fieldFunc),
	m_color(ColorRGB(0, 0, 0)),
	m_innerRadius(innerRadius),
	m_outerRadius(outerRadius)
{
	m_width = outerRadius - innerRadius;
	m_widthSq = m_width * m_width;
	m_centerRadius = innerRadius + m_width / 2;
}

Torus::Torus(float (*fieldFunc)(float), ColorRGB color, float innerRadius,
	       float outerRadius) :
	ImplicitModel(fieldFunc),
	m_color(color),
	m_innerRadius(innerRadius),
	m_outerRadius(outerRadius)
{
	m_width = outerRadius - innerRadius;
	m_widthSq = m_width * m_width;
	m_centerRadius = innerRadius + m_width / 2;
}

Torus::Torus(float (*fieldFunc)(float), float coeff, float innerRadius,
				float outerRadius) :
	ImplicitModel(fieldFunc, coeff),
	m_innerRadius(innerRadius),
	m_outerRadius(outerRadius)
{
	m_width = outerRadius - innerRadius;
	m_widthSq = m_width*m_width;
	m_centerRadius = innerRadius + m_width / 2;
}

vec3 Torus::getNearestPoint(vec3 pt)
{
	vec3 result = pt;
	result.z = 0.f;
	return normalize(result) * m_centerRadius;
}

float Torus::getFieldValue(vec3 pt)
{
	return m_coeff * m_fieldFunc(getDistanceSq(pt) / (m_widthSq *0.25));
}

float Torus::getDistanceSq(vec3 pt)
{
	vec3 nearest = getNearestPoint(pt);
	return ((pt.x - nearest.x) * (pt.x - nearest.x)) +
		((pt.y - nearest.y) * (pt.y - nearest.y)) +
		((pt.z - nearest.z) * (pt.z - nearest.z));
}
bool Torus::contains(vec3 pt, float tolerance)
{
	return getDistanceSq(pt) <= ((m_width/2)+tolerance)*((m_width/2)+tolerance);
}

bool Torus::touches(vec3 pt, float tolerance)
{
	return (getDistanceSq(pt) < ((m_width/2)+ tolerance) * ((m_width/2) + tolerance))
		&&
		(getDistanceSq(pt) > ((m_width/2) - tolerance) * ((m_width/2) - tolerance));
}

Point Torus::getPoint(vec3 pt)
{
	vec3 normal = pt - getNearestPoint(pt);
	return Point(m_color, normalize(normal));
}
