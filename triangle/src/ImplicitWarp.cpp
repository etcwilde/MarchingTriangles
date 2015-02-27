#include "ImplicitWarp.hpp"

using namespace Implicit;

Warp::Warp(Object* obj, glm::vec3 offest, glm::vec3 direction) :
	Object(),
	m_object(obj),
	m_transform(),
	m_inverseTransform()
{
	glm::vec3 up(0, 1, 0);
	if (direction != up)
		m_transform = glm::lookAt(offest, offest + direction, up);
	m_inverseTransform = glm::inverse(m_transform);
}

glm::vec3 Warp::warpPoint(glm::vec3 pt)
{
	pt = glm::vec3(glm::vec4(pt, 1) * m_transform);
	return glm::vec3(glm::vec4(warpFunction(pt), 1) * m_inverseTransform);
}

float Warp::getFieldValue(glm::vec3 pt)
{
	return m_object->getFieldValue(warpPoint(pt));
}

PointFlavour Warp::getFlavour(glm::vec3 pt)
{
	PointFlavour result = m_object->getFlavour(warpPoint(pt));
	srand((int)pt.x + (int)pt.y*57 + (int)pt.z*123);
	glm::mat4 trans;
	glm::vec3 normal(0, 0, 0);
	for (int i = 0; i < 9; i++)
	{
		trans = glm::mat4();
		trans = glm::rotate(trans, i * 20.f + (rand()%2000)/100.f,
				glm::vec3(0.f, 0.f, 1.f)); // TODO check 010
		trans = glm::rotate(trans, (rand()%36000)/100.f,
				glm::vec3(0.f, 1.f, 0.f));
		for (int j = 0; j < 8; j++)
		{
			float rot = (rand()%4500)/100.f;
			trans = glm::rotate(trans, rot, glm::vec3(0.f, 1.f, 0.f));
			glm::vec3 sample = glm::vec3(glm::vec4(0, 1, 0, 1) * trans);
			float field = m_object->getFieldValue(warpPoint(pt + 0.5f*sample));
			normal += sample * -1.f * field;
			trans = glm::rotate(trans, 45.f - rot, glm::vec3(0.f, 1.f, 0.f));
		}
	}

	return PointFlavour(result.color(), glm::normalize(normal));
}

bool Warp::contains(glm::vec3 pt, float errorMargin)
{
	return m_object->contains(warpPoint(pt), errorMargin);
}

std::list<glm::vec3> Warp::getPointsInObject()
{
	return m_object->getPointsInObject();
}

// Twist
Twist::Twist(Object* obj) :
	Warp(obj, glm::vec3(0), glm::vec3(0,1,0)),
	m_coeff(1.f)
{}

Twist::Twist(Object* obj, float coeff) :
	Warp(obj, glm::vec3(0), glm::vec3(0,1,0)),
	m_coeff(coeff)
{}

Twist::Twist(Object* obj, glm::vec3 offset, glm::vec3 direction, float coeff) :
	Warp(obj, offset, direction),
	m_coeff(coeff)
{}

// TODO Check that this is in fact correct
// Original code z was up direction
// New code y is up direction
glm::vec3 Twist::warpFunction(glm::vec3 pt)
{
	return glm::vec3(
			(pt.x * std::cos(m_coeff * pt.z)) -
			(pt.y * std::sin(m_coeff * pt.z)),
			(pt.x * std::sin(m_coeff * pt.z)) +
			(pt.y * std::cos(m_coeff * pt.z)),
			pt.z);
}

// Taper
Taper::Taper(Object* obj) :
	Warp(obj, glm::vec3(0), glm::vec3(0, 1, 0)),
	m_min(1.f),
	m_max(0.f)
{ }

Taper::Taper(Object* obj, float max, float min) :
	Warp(obj, glm::vec3(0), glm::vec3(0, 1, 0)),
	m_min(min),
	m_max(max)
{ }

Taper::Taper(Object* obj, glm::vec3 offset, glm::vec3 direction,
		float max, float min) :
	Warp(obj, offset, direction),
	m_min(min),
	m_max(max)
{ }

// TODO Check that this is in fact correct
// Original code z was up direction
// New code y is up direction
glm::vec3 Taper::warpFunction(glm::vec3 pt)
{
	float scale = (m_max - pt.z) / (m_max - m_min);
	return glm::vec3(pt.x / scale,
			pt.y/scale, pt.z);
}


// Bend
Bend::Bend(Object* obj) :
	Warp(obj, glm::vec3(0), glm::vec3(0, 1, 0)),
	m_rate(1.f)
{}

Bend::Bend(Object* obj, float rate) :
	Warp(obj, glm::vec3(0), glm::vec3(0, 1, 0)),
	m_rate(rate)
{ }

Bend::Bend(Object* obj, glm::vec3 offset, glm::vec3 direction,
	float rate) :
	Warp(obj, offset, direction),
	m_rate(rate)
{ }


glm::vec3 Bend::warpFunction(glm::vec3 pt)
{
	return glm::vec3(
			(-0.1f*std::sin((pt.x+1.5f)*m_rate)*(pt.y-1.f/m_rate)-1.5f),
			(std::cos((pt.x+1.5f)*m_rate)*(pt.y-1.f/m_rate)+1.f/m_rate),
			pt.z);
}
