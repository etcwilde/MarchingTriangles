#include "ImplicitGroup.hpp"

using namespace Implicit;

Group::Group() :
	Object(),
	m_recursiveObjects(),
	m_baseObjects(),
	m_maxDepth(0),
	m_depth(0)
{}

Group::Group(int maxDepth) :
	Object(),
	m_recursiveObjects(),
	m_baseObjects(),
	m_maxDepth(maxDepth),
	m_depth(0)
{}

void Group::addBaseObject(Object* object)
{
	m_baseObjects.push_back(object);
}

void Group::addRecursiveObject(Object* object)
{
	m_recursiveObjects.push_back(object);
}

float Group::getFieldValue(glm::vec3 point)
{
	float fieldSum = 0.f;
	if (m_depth < m_maxDepth)
	{
		m_depth++;
		fieldSum = getFieldFromObjects(m_recursiveObjects, point);
		m_depth--;
	}
	else if (m_depth == m_maxDepth)
	{
		m_depth++;
		fieldSum = getFieldFromObjects(m_baseObjects, point);
		m_depth--;
	}
	return fieldSum;
}

PointFlavour Group::getFlavour(glm::vec3 point)
{
	PointFlavour flavour;
	if (m_depth < m_maxDepth)
	{
		m_depth++;
		flavour = getFlavourFromObjects(m_recursiveObjects, point);
		m_depth--;
	}
	else if (m_depth == m_maxDepth)
	{
		m_depth++;
		flavour = getFlavourFromObjects(m_baseObjects, point);
		m_depth--;
	}
	return flavour;
}

bool Group::contains(glm::vec3 point, float errorMargin)
{
	bool result = false;
	if (m_depth < m_maxDepth)
	{
		m_depth++;
		result = containedInObjects(m_recursiveObjects, point,
				errorMargin);
		m_depth--;
	}
	else if (m_depth == m_maxDepth)
	{
		m_depth++;
		result = containedInObjects(m_baseObjects, point, errorMargin);
		m_depth--;
	}
	return result;
}

std::list<glm::vec3> Group::getPointsInObject()
{
	std::list<glm::vec3> result;
	if (m_depth < m_maxDepth)
	{
		m_depth++;
		result = getPointsInObjects(m_recursiveObjects);
		m_depth--;
	}
	else if (m_depth == m_maxDepth)
	{
		m_depth++;
		result = getPointsInObjects(m_baseObjects);
		m_depth--;
	}
	return result;
}

//

bool Group::containedInObjects(std::list<Object*> objects, glm::vec3 point,
		float errorMargin)
{
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
		if ((*it)->contains(point, errorMargin)) return true;
	return false;
}

std::list<glm::vec3> Group::getPointsInObjects(std::list<Object*> objects)
{
	std::list<glm::vec3> points;
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
		points.insert(points.end(), (*it)->getPointsInObject().begin(),
				(*it)->getPointsInObject().end());
	return points;
}

PointFlavour Group::getFlavourFromObjects(std::list<Object*> objects,
		glm::vec3 point)
{
	glm::vec3 normal(0.f, 0.f, 0.f);
	float fieldSum = 0.f;
	float field[objects.size()];

	float r, g, b;
	r = g = b = 0.f;

	int i = 0;
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++, i++)
	{
		field[i] = (*it)->getFieldValue(point);
		fieldSum += field[i];
		PointFlavour sample = (*it)->getFlavour(point);
		normal += sample.normal() * field[i];
		r += sample.color().r()*field[i];
		g += sample.color().g()*field[i];
		b += sample.color().b()*field[i];
	}
	if (fieldSum == 0.f) fieldSum = 1.f;
	normal = glm::normalize(normal);

	ColorRGB color((r/fieldSum) * 255, (g/fieldSum) * 255, (b/fieldSum) * 255);
	return PointFlavour(color, normal);
}

// Blend
float Blend::getFieldFromObjects(std::list<Object*> objects, glm::vec3 point)
{
	float fieldSum = 0.f;
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
		fieldSum += (*it)->getFieldValue(point);
	return fieldSum;
}

// Ricci
float RicciBlend::getFieldFromObjects(std::list<Object*> objects, glm::vec3 point)
{
	double fieldSum = 0.f;
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
		fieldSum += std::pow((*it)->getFieldValue(point), m_power);
	if (fieldSum == 0.f) return 0.f;
	return std::pow(fieldSum, m_invPower);
}

// Union
float Union::getFieldFromObjects(std::list<Object*> objects, glm::vec3 point)
{
	float field;
	float result = 0.f;
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
	{
		field = (*it)->getFieldValue(point);
		result = field > result ? field : result;
	}
	return result;
}

PointFlavour Union::getFlavourFromObjects(std::list<Object*> objects,
		glm::vec3 point)
{
	PointFlavour result;
	float field;
	float max_field = 0.f;
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
	{
		field = (*it)->getFieldValue(point);
		if (field > max_field)
		{
			max_field = field;
			result = (*it)->getFlavour(point);
		}
	}
	return result;
}

// Intersect
float Intersect::getFieldFromObjects(std::list<Object*> objects, glm::vec3 point)
{
	float field;
	float result = FLT_MAX;

	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
	{
		field = (*it)->getFieldValue(point);
		result = field < result ? field : result;
	}

	return result;
}

PointFlavour Intersect::getFlavourFromObjects(std::list<Object*> objects,
		glm::vec3 point)
{
	PointFlavour result;
	float field;
	float minField = FLT_MAX;
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
	{
		field = (*it)->getFieldValue(point);
		if (field < minField)
		{
			minField = field;
			result = (*it)->getFlavour(point);
		}
	}
	return result;
}

std::list<glm::vec3> Intersect::getPointsInObjects(std::list<Object*> objects)
{
	std::list<glm::vec3> points;
	glm::vec3 point;
	int sum = 0;
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
	{
		std::list<glm::vec3> pnts = (*it)->getPointsInObject();
		for (std::list<glm::vec3>::iterator pit = pnts.begin();
				pit != pnts.end(); pit++)
		{
			sum++;
			point += (*pit);
		}
	}
	points.push_back(point/(float)sum);
	return points;
}

// Difference
float Difference::getFieldFromObjects(std::list<Object*> objects,
		glm::vec3 point)
{
	if(objects.size() == 0) return 0.f;
	float field = (*(objects.begin()))->getFieldValue(point);
	float result = field;
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
	{
		field = (2 * m_iso) - (*it)->getFieldValue(point);
		result = field < result ? field : result;
	}
	return result;
}

PointFlavour Difference::getFlavourFromObjects(std::list<Object*> objects,
		glm::vec3 point)
{
	if (objects.size() == 0) return PointFlavour();
	float field = (*(objects.begin()))->getFieldValue(point);
	float minField = field;
	PointFlavour result = (*(objects.begin()))->getFlavour(point);
	for (std::list<Object*>::iterator it = objects.begin();
			it != objects.end(); it++)
	{
		field = (2 * m_iso) - (*it)->getFieldValue(point);
		if (field <= minField)
		{
			minField = field;
			result = (*it)->getFlavour(point);
			result *= -1;
		}
	}
	return result;
}

// Not quite, but close enough
// TODO Make it actually determine if it is within the surface
bool Difference::containedInObjects(std::list<Object*> objects,
		glm::vec3 point, float errorMargin)
{
	if (objects.size() == 0) return false;
	if (!(*(objects.begin()))->contains(point, errorMargin)) return false;
	return true;
}

std::list<glm::vec3> Difference::getPointsInObjects(std::list<Object*> objects)
{
	if (objects.size() == 0) return std::list<glm::vec3>();
	return (*(objects.begin()))->getPointsInObject();
}
