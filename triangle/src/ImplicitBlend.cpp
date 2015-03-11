#include "ImplicitBlend.hpp"

using namespace Implicit;

Blend::Blend() :
	Object(),
	m_objects()
{ }

Blend::Blend(float iso) :
	Object(iso),
	m_objects()
{ }

Blend::Blend(float iso, glm::vec3 center) :
	Object(center, iso),
	m_objects()
{ }

void Blend::AddObject(Object* obj)
{
	m_objects.push_back(obj);
}

float Blend::Evaluate(glm::vec3 point)
{
	return FieldValue(point) - m_iso;
}

float Blend::FieldValue(glm::vec3 point)
{
	float ret_val = 0.f;
	for (std::list<Object*>::iterator obj = m_objects.begin();
			obj != m_objects.end(); obj++)
		ret_val += (*obj)->FieldValue(point);
	return ret_val;
}

glm::vec3 Blend::Normal(glm::vec3 point)
{
	float total_field_value = FieldValue(point);
	glm::vec3 normal;
	for (std::list<Object*>::iterator obj = m_objects.begin();
			obj != m_objects.end(); obj++)
	{
		float partial_field_value = (*obj)->FieldValue(point);
		normal += (partial_field_value / total_field_value) 
			* (*obj)->Normal(point);
	}
	return normal;
}
