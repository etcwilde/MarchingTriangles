#include "ImplicitCube.hpp"

using namespace Implicit;

Cube::Cube(float(*fieldFunc)(float), float radius, float sides) :
	ImplicitModel(fieldFunc),
	m_color(ColorRGB(0, 0, 0)),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_x(sides/2.f),
	m_y(sides/2.f),
	m_z(sides/2.f)
{ }

Cube::Cube(float(*fieldFunc)(float), ColorRGB color, float r, float sides) :
	ImplicitModel(fieldFunc),
	m_color(color),
	m_radius(r),
	m_radiusSq(r*r),
	m_x(sides/2.f),
	m_y(sides/2.f),
	m_z(sides/2.f)
{ }

Cube::Cube(float(*fieldFunc)(float), float coeff, ColorRGB color, float r, 
		float sides) :
	ImplicitModel(fieldFunc, coeff),
	m_color(color),
	m_radius(r),
	m_radiusSq(r*r),
	m_x(sides/2.f),
	m_y(sides/2.f),
	m_z(sides/2.f)
{ }

Cube::Cube(float (*fieldFunc)(float), float radius, float x, float y, float z) :
	ImplicitModel(fieldFunc),
	m_color(ColorRGB(0, 0, 0)),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_x(x/2.f),
	m_y(y/2.f),
	m_z(z/2.f)
{ }


Cube::Cube(float (*fieldFunc)(float), ColorRGB color, float radius, float x, float y, float z) :
	ImplicitModel(fieldFunc),
	m_color(color),
	m_radius(radius),
	m_radiusSq(radius*radius),
	m_x(x/2.f),
	m_y(y/2.f),
	m_z(z/2.f)
{ }

float Cube::getFieldValue(vec3 pt)
{
	return m_coeff * m_fieldFunc(getDistanceSq(pt) / m_radiusSq);
}

vec3 Cube::getNearestPoint(vec3 pt)
{
	return vec3((pt.x < -m_x) ? -m_x : ((pt.x > m_x) ? m_x : pt.x),
			(pt.y < -m_y) ? -m_y : ((pt.y > m_y) ? m_y : pt.y),
			(pt.z < -m_z) ? -m_z : ((pt.z > m_z) ? m_z : pt.z));


}

float Cube::getDistanceSq(vec3 pt)
{
	vec3 nearest = getNearestPoint(pt);
	return ((pt.x - nearest.x) * (pt.x - nearest.x)) +
		((pt.y - nearest.y) * (pt.y - nearest.y)) +
		((pt.z - nearest.z) * (pt.z - nearest.z));
}

bool Cube::contains(vec3 pt, float tolerance)
{
	return getDistanceSq(pt) < ((m_radius + tolerance) * m_radius + tolerance);
}

bool Cube::touches(vec3 pt, float tolerance)
{
	return (getDistanceSq(pt) < (m_radius + tolerance) * (m_radius + tolerance))
		&&
		(getDistanceSq(pt) > (m_radius - tolerance) * (m_radius - tolerance));
}


Point Cube::getPoint(vec3 pt)
{
	vec3 normal = pt - getNearestPoint(pt);
	if (length(normal) < 0.01f)
	{
		if ((std::abs(pt.x) > std::abs(pt.y)) &&
				(std::abs(pt.x) > std::abs(pt.z)))
			normal = vec3(pt.x, 0.f, 0.f);
		else if (std::abs(pt.y) > std::abs(pt.z))
			normal = vec3(0.f, pt.y, 0.f);
		else
			normal = vec3(0.f, 0.f, pt.z);
	}
	return Point(m_color, normalize(normal));
}

