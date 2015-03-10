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

	return 10;
};

glm::vec3 Blend::getStartPoint()
{
	return glm::vec3(0, 0, 0);
}

float Blend::evaluate(float r)
{
	float value = 0;
	for (std::list<Object*>::iterator it = m_objects.begin();
			it != m_objects.end(); it++)
	{

	}
	return value - m_iso;
}

glm::vec3 Blend::normal(glm::vec3 pt)
{
	return glm::vec3(0, 0, 0);
}
