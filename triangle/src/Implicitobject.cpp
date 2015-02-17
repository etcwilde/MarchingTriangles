#include "Implicitobject.hpp"

using namespace Implicit;

Point::Point() :
	m_color(),
	m_normal()
{}

Point::Point(ColorRGB Color, vec3 normal) :
	m_color(Color),
	m_normal(normal)
{}

inline const ColorRGB& Point::color() const
{
	return m_color;
}

inline vec3 Point::normal()
{
	return m_normal;
}

void Point::operator *= (const mat4& mat)
{
	m_normal = vec3(vec4(m_normal, 1) * mat);
}

void Point::operator *= (const float s)
{
	m_normal = s * m_normal;
}

// Implicit Model

ImplicitModel::ImplicitModel(float (*fieldFunc)(float)) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_coeff(1.0f)
{ }

ImplicitModel::ImplicitModel(float (*fieldFunc)(float), float coeff) :
	Object(),
	m_fieldFunc(fieldFunc),
	m_coeff(coeff)
{ }

float ImplicitModel::getFieldValue(vec3 point)
{
	return m_coeff * m_fieldFunc(getDistanceSq(point));
}

void ImplicitModel::setFieldFunc(float(*fieldFunc)(float))
{
	m_fieldFunc = fieldFunc;
}

void ImplicitModel::setFieldCoeff(float coeff)
{
	m_coeff = coeff;
}

