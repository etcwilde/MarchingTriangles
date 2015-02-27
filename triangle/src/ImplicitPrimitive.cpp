#include "ImplicitPrimitive.hpp"

using namespace Implicit;
Primitive::Primitive(float (*fieldFunc)(float)) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_fieldCoefficient(1.f)
{}
Primitive::Primitive(float (*fieldFunc)(float), float coeff) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_fieldCoefficient(coeff)
{}

void Primitive::setFieldFunc(float (*fieldFunc)(float))
{
	m_fieldFunc = fieldFunc;
}

void Primitive::setFieldCoefficient(float coeff)
{
	m_fieldCoefficient = coeff;
}

float Primitive::getFieldValue(glm::vec3 point)
{
	return m_fieldCoefficient * m_fieldFunc(getDistanceSq(point));
}


