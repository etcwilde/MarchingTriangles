#include "ImplicitBlob.hpp"

using namespace Implicit;

Blob::Blob(FieldFunction fieldFunc, float iso) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_iso(iso),
	m_center(),
	m_max_distance(1)
{ }

Blob::Blob(FieldFunction fieldFunc, float iso,
		float max_distance) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_iso(iso),
	m_center(),
	m_max_distance(max_distance)
{ }

Blob::Blob(FieldFunction fieldFunc, float iso, glm::vec3 center) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_iso(iso),
	m_center(center),
	m_max_distance(1)
{ }

Blob::Blob(FieldFunction fieldFunc, float iso,
				glm::vec3 center, float max_distance) :
	m_fieldFunc(fieldFunc),
	m_iso(iso),
	m_center(center),
	m_max_distance(max_distance)
{ }

float Blob::getFieldValue(glm::vec3 pt)
{
	return m_fieldFunc(getDistance(pt), m_max_distance);
}

float Blob::getDistance(glm::vec3 pt) const
{
	return glm::length(pt - m_center);
}

glm::vec3 Blob::getStartPoint() 
{
#ifdef DEBUG
	std::cout << "Center Vertex: " << getCenter() << '\n';
#endif
	return project_to_surface(getCenter());
};

glm::vec3 Blob::getCenter() const
{
	return m_center;
}




float Blob::evaluate(float r)
{
	return m_fieldFunc(r, m_max_distance) - m_iso;
}

