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
Object* Model::setRoot(Object* r)
{
	m_root = r;
	return r;
}

Object* Model::addObject(Object* o)
{
	m_objects.push_back(o);
	return o;
}

Group* Model::addGroup(Group* g)
{
	m_objects.push_back(g);
	return g;
}

// Implicit Group
Group::Group() :
	Object(),
	m_recursive_objects(),
	m_base_objects(),
	m_max_depth(0),
	m_depth(0)
{ }

Group::Group(unsigned int max_depth) :
	Object(),
	m_recursive_objects(),
	m_base_objects(),
	m_max_depth(max_depth),
	m_depth(0)
{ }

void Group::addBaseObject(Object* obj)
{
	m_base_objects.push_back(obj);
}

void Group::addRecursiveObject(Object* obj)
{
	m_recursive_objects.push_back(obj);
}

float Group::getFieldValue(vec3 pt)
{
	float sum = 0.0f;
	if (m_depth < m_max_depth)
	{
		m_depth++;
		sum = getFieldFromObjects(m_recursive_objects, pt);
		m_depth--;
	}
	else if (m_depth == m_max_depth)
	{
		m_depth++;
		sum = getFieldFromObjects(m_base_objects, pt);
		m_depth--;
	}
	return sum;
}

Point Group::getPoint(vec3 pt)
{
	Point pnt;
	if (m_depth < m_max_depth)
	{
		m_depth++;
		pnt = getPointsFromObjects(m_recursive_objects, pt);
		m_depth--;
	}
	else if (m_depth == m_max_depth)
	{
		m_depth++;
		pnt = getPointsFromObjects(m_base_objects, pt);
		m_depth--;
	}
	return pnt;
}

bool Group::contains(vec3 pt, float tolerance)
{
	bool result = false;
	if (m_depth < m_max_depth)
	{
		m_depth++;
		result = containedInObjects(m_recursive_objects, pt, tolerance);
		m_depth--;
	}
	else if (m_depth = m_max_depth)
	{
		m_depth++;
		result = containedInObjects(m_base_objects, pt, tolerance);
		m_depth--;
	}
	return result;
}

Point Group::getPointsFromObjects(std::list<Object*> objs, vec3 pt)
{
	vec3 normal;
	float fieldSum = 0.f;
	float field[objs.size()];


	float r = 0.0f; float g = 0.0f; float b = 0.0f;
	unsigned int i = 0;
	for(std::list<Object*>::iterator obj_it = objs.begin();
			obj_it != objs.end(); obj_it++, i++)
	{
		field[i] = (*obj_it)->getFieldValue(pt);
		fieldSum += field[i];
		Point sample = (*obj_it)->getPoint(pt);
		normal += sample.normal() * (float)field[i];
		r += sample.color().r() * (float)field[i];
		g += sample.color().g() * (float)field[i];
		b += sample.color().b() * (float)field[i];
	}
	if (fieldSum == 0.0f) fieldSum = 1.f;
	normal = normalize(normal);
	ColorRGB color(r / fieldSum, g / fieldSum, b / fieldSum);
	return Point(color, normal);
}

bool Group::containedInObjects(std::list<Object*> objs, vec3 pt, float t)
{
	for(std::list<Object*>::iterator obj_it = objs.begin();
			obj_it != objs.end(); ++obj_it)
		if ((*obj_it)->contains(pt, t)) return true;
	return false;
}

// Blend
Blend::Blend() :
	Group()
{}

Blend::Blend(unsigned int max_depth) :
	Group(max_depth)
{}

float Blend::getFieldFromObjects(std::list<Object*> objs, vec3 pt)
{
	float f_sum = 0.f;
	for (std::list<Object*>::iterator obj_it = objs.begin();
			obj_it != objs.end(); obj_it++)
		f_sum += (*obj_it)->getFieldValue(pt);
	return f_sum;
}

// Ricci Blend
RicciBlend::RicciBlend(float power) :
	Group(),
	m_power(power),
	m_invPower(1.f/power)
{ }

RicciBlend::RicciBlend(float power, unsigned int max_depth) :
	Group(max_depth),
	m_power(power),
	m_invPower(1.f/power)
{ }

float RicciBlend::getFieldFromObjects(std::list<Object*> objs, vec3 pt)
{
	double fsum = 0.0f;
	for (std::list<Object*>::iterator obj_it = objs.begin();
			obj_it != objs.end(); obj_it++)
		fsum += std::pow((*obj_it)->getFieldValue(pt), m_power);
	if (fsum == 0.0f) return 0;
	return std::pow(fsum, m_invPower);
}

// Union
Union::Union() :
	Group()
{ }

Union::Union(unsigned int max_depth) :
	Group(max_depth)
{ }

float Union::getFieldFromObjects(std::list<Object*> objs, vec3 pt)
{
	float field;
	float result = 0.f;
	for (std::list<Object*>::iterator obj_it = objs.begin();
			obj_it != objs.end(); obj_it++)
	{
		field = (*obj_it)->getFieldValue(pt);
		result = (field > result) ? field : result;
	}
	return result;
}

Point Union::getPointsFromObjects(std::list<Object*> objs, vec3 pt)
{
	Point r;
	float field;
	float max_field = 0.0f;
	for (std::list<Object*>::iterator obj_it = objs.begin();
			obj_it != objs.end(); obj_it++)
	{
		field = (*obj_it)->getFieldValue(pt);
		if (field > max_field)
		{
			max_field = field;
			r= (*obj_it)->getPoint(pt);
		}
	}
	return r;
}


// Intersect
Intersect::Intersect() :
	Group()
{ }

Intersect::Intersect(unsigned int max_depth) :
	Group(max_depth)
{ }

float Intersect::getFieldFromObjects(std::list<Object*> objs, vec3 pt)
{
	float f;
	float r = FLT_MAX;
	for (std::list<Object*>::iterator obj_it = objs.begin();
			obj_it != objs.end(); obj_it++)
	{
		f = (*obj_it)->getFieldValue(pt);
		r = (f < r) ? f : r;
	}
	return r;
}

Point Intersect::getPointsFromObjects(std::list<Object*> objs, vec3 pt)
{
	Point p;
	float f;
	float minf = FLT_MAX;
	for (std::list<Object*>::iterator obj_it = objs.begin();
			obj_it != objs.end(); obj_it++)
	{
		f = (*obj_it)->getFieldValue(pt);
		if (f < minf)
		{
			minf = f;
			p = (*obj_it)->getPoint(pt);
		}
	}
	return p;
}

// Difference
Difference::Difference(float iso) :
	Group(),
	m_iso(iso)
{ }

Difference::Difference(float iso, unsigned int max_depth) :
	Group(max_depth),
	m_iso(iso)
{ }

float Difference::getFieldFromObjects(std::list<Object*>objs, vec3 pt)
{
	if (objs.size() == 0) return 0;
	float f = (*objs.begin())->getFieldValue(pt);
	float result = f;
	for (std::list<Object*>::iterator obj_it = ++objs.begin();
			obj_it != objs.end(); obj_it++)
	{
		f = (2 * m_iso) - (*obj_it)->getFieldValue(pt);
		result = (f < result) ? f : result;
	}
	return result;
}

Point Difference::getPointsFromObjects(std::list<Object*> objs, vec3 pt)
{
	if (objs.size() == 0) return Point();
	float f = (*objs.begin())->getFieldValue(pt);
	float f_min = f;
	Point result = (*objs.begin())->getPoint(pt);
	for (std::list<Object*>::iterator obj_it = ++objs.begin();
			obj_it != objs.end(); obj_it++)
	{
		f = (2 * m_iso) - ((*obj_it)->getFieldValue(pt) + 0.01f);
		if (f <= f_min)
		{
			f_min  = f;
			result = (*obj_it)->getPoint(pt);
			result *= -1;
		}
	}
	return result;
}

bool Difference::containsInObjects(std::list<Object*> objs, vec3 pt, float t)
{
	if (objs.size() == 0) return false;
	if (!(*objs.begin())->contains(pt, t)) return false;
	return true;
}



