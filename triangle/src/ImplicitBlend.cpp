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
	// Get the sum of the field values of each object
	float field_value = 0.f;
#ifdef DEBUG
	unsigned int counter = 0;
#endif
	for (std::list<Object*>::iterator obj = m_objects.begin();
			obj != m_objects.end(); obj++)
	{
#ifdef DEBUG
		std::cout << "Object " << counter << ": " << (*obj)->getFieldValue(pt) << '\n';
		counter++;
#endif
		field_value += (*obj)->getFieldValue(pt);
	}

#ifdef DEBUG
	std::cout << "Blend Field value: " << field_value << '\n';
#endif
	return field_value;

};

glm::vec3 Blend::getStartPoint()
{
	return glm::vec3(0, 0, 0);
}

float Blend::evaluate(float r)
{
	float value = 0;
	for (std::list<Object*>::iterator obj = m_objects.begin();
			obj != m_objects.end(); obj++)
	{
		value += (*obj)->evaluate(r);
	}
	return value - m_iso;
}

glm::vec3 Blend::normal(glm::vec3 pt)
{
	return glm::vec3(0, 0, 0);
}
