/**
 * ImplicitObject
 *
 * File: 	ImplicitObject.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 18 2015
 */

#include "ImplicitObject.hpp"

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

inline const vec3 Point::normal() const
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

Point operator * (const mat4& m, const Point& p)
{
	return Point(p.color(), vec3(vec4(p.normal(), 1) * m));
}

Point operator * (mat4& m, const Point& p)
{
	return Point(p.color(), vec3(vec4(p.normal(), 1) * m));
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


// Model
Model::Model() :
	m_objects(),
	m_root(NULL)
{ }

Model::~Model()
{
	for (std::list<Object*>::iterator obj_it = m_objects.begin();
			obj_it != m_objects.end(); ++obj_it)
	{
		delete *obj_it;
	}
}

Object* Model::getRoot()
{
	return m_root;
}

// Protected Methods
void Model::setRoot(Object* r)
{
	m_root = r;
}

void Model::addObject(Object* o)
{
	m_objects.push_back(o);
}
