#include "ImplicitPrimitive.hpp"

using namespace Implicit;

Primitive::Primitive(FieldFunction f) :
	Object(),
	m_fieldFunction(f),
	m_radius(1)
{ }

Primitive::Primitive(FieldFunction f, float iso) :
	Object(iso),
	m_fieldFunction(f),
	m_radius(1)
{ }

Primitive::Primitive(FieldFunction f, float iso, float radius) :
	Object(iso),
	m_fieldFunction(f),
	m_radius(radius)
{ }

Primitive::Primitive(FieldFunction f, glm::vec3 center, float iso,
		float radius) :
	Object(center, iso),
	m_fieldFunction(f),
	m_radius(radius)
{ }

void Primitive::SetRadius(float radius)
{
	m_radius = radius;
}

float Primitive::FieldValue(float r)
{
	return m_fieldFunction(r, m_radius);
}

float Primitive::Evaluate(float r)
{
	return FieldValue(r) - m_iso;
}

float Primitive::FieldValue(glm::vec3 pt)
{
	return FieldValue(getDistance(pt));
}

float Primitive::Evaluate(glm::vec3 pt)
{
	return FieldValue(pt) - m_iso;
}

glm::vec3 Primitive::StartPoint()
{
	return project(m_center);
}


// Protected Methods
float Primitive::getDistance(glm::vec3 pt)
{
	return glm::length(pt - m_center);
}

