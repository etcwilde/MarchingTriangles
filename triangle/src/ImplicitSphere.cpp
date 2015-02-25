/**
 * ImplicitSphere
 *
 * File: 	ImplicitSphere.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 16 2015
 */

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

// TODO Remove this
#include <iostream>

float Sphere::getFieldValue(vec3 pt)
{
	/*std::cout << "Distance^2: " << getDistanceSq(pt) << '\n'
		<< "Radius^2: " << m_radiusSq << '\n'
		<< "D/R: " << getDistanceSq(pt)/m_radiusSq << '\n'
		<< "Coefficient: " << m_coeff << '\n'
		<< "Field Value: " << m_fieldFunc(getDistanceSq(pt) / m_radiusSq)<<'\n'; */

	return m_coeff * m_fieldFunc(getDistanceSq(pt) / m_radiusSq);
}

float Sphere::getDistanceSq(vec3 pt)
{
	//std::cout << pt.x * pt.x + pt.y * pt.y + pt.z * pt.z << '\n';
	return (pt.x * pt.x + pt.y * pt.y + pt.z * pt.z);
}

bool Sphere::contains(vec3 pt, float tolerance)
{
	return getDistanceSq(pt)
		< (m_radius + tolerance) * (m_radius + tolerance);
}

bool Sphere::touches(vec3 pt, float tolerance)
{
	return (getDistanceSq(pt) < (m_radius + tolerance) * (m_radius + tolerance))
		&&
		(getDistanceSq(pt) > (m_radius - tolerance) * (m_radius - tolerance));
}

Point Sphere::getPoint(vec3 pt)
{
	return Point(m_color, normalize(pt));
}
