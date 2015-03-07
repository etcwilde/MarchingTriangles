#include "ImplicitBlend.hpp"

using namespace Implicit;

Blend::Blend() :
	m_objects(),
	m_iso(0.5f)
{ }


Blend::Blend(float iso) :
	m_objects(),
	m_iso(iso)
{ }

void Blend::addObject(Object* obj)
{
	m_objects.push_back(obj);
}

float Blend::getFieldValue(glm::vec3 pt)
{
	float field_value = 0.f;
	for (std::list<Implicit::Object*>::iterator it = m_objects.begin();
			it != m_objects.end(); it++)
		field_value += (*it)->getFieldValue(pt);
	return field_value;
};

glm::vec3 Blend::getStartPoint()
{
	// Hopefully the start point of one of the children will be close
	// enough
	// TODO Ensure that this actually works
	return project_to_surface((*m_objects.begin())->getStartPoint());
}

float Blend::evaluate(float r)
{
	float field_value = 0.f;
	for (std::list<Implicit::Object*>::iterator it = m_objects.begin();
			it != m_objects.end(); it++)
	{
		field_value += (*it)->evaluate(r);
	}
	return field_value;
}


