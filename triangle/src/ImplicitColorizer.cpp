#include "ImplicitColorizer.hpp"

using namespace Implicit;

Colorizer::Colorizer(Object* obj) :
	Object(),
	m_obj(obj)
{}

float Colorizer::getFieldValue(glm::vec3 pt)
{
	return m_obj->getFieldValue(pt);
}

PointFlavour Colorizer::getFlavour(glm::vec3 pt)
{
	PointFlavour flavour = m_obj->getFlavour(pt);
	return  PointFlavour(transformColor(pt, flavour.color()), flavour.normal());
}

bool Colorizer::contains(glm::vec3 pt, float errorMargin)
{
	return m_obj->contains(pt, errorMargin);
}

std::list<glm::vec3> Colorizer::getPointsInObject()
{
	return m_obj->getPointsInObject();
}

void Colorizer::setObject(Object* obj)
{
	m_obj = obj;
}


