#include "ImplicitTransform.hpp"

using namespace Implicit;

Transform::Transform(Object* obj) :
	Object(),
	m_object(obj),
	m_transform(),
	m_invTransform(),
	m_normalTransform()
{}


Transform::Transform(Object* obj, glm::mat4 transform) :
	Object(),
	m_object(obj),
	m_transform(transform),
	m_invTransform(),
	m_normalTransform()
{
	setTransform(transform);
}

float Transform::getFieldValue(glm::vec3 pt)
{
	applyInverseTransform(&pt);
	return m_object->getFieldValue(pt);
}

PointFlavour Transform::getFlavour(glm::vec3 pt)
{
	applyInverseTransform(&pt);
	return m_object->getFlavour(pt);
}

bool Transform::contains(glm::vec3 pt, float errorMargin)
{
	applyInverseTransform(&pt);
	return m_object->contains(pt, errorMargin);
}

std::list<glm::vec3> Transform::getPointsInObject()
{
	std::list<glm::vec3> points = m_object->getPointsInObject();
	for (std::list<glm::vec3>::iterator it = points.begin();
			it != points.end(); it++)
		applyTransform(&(*it));
	return points;
}


void Transform::setTransform(glm::mat4 transform)
{
	m_transform = transform;
	Transform *trans = dynamic_cast<Transform*>(m_object);
	if (trans != NULL)
		m_transform = transform * trans->getTransform();
	else m_transform = transform;
	m_invTransform = glm::inverse(m_transform);
	m_normalTransform = glm::transpose(m_invTransform);

	m_normalTransform[3].x = 0;
	m_normalTransform[3].y = 0;
	m_normalTransform[3].z = 0;
	m_normalTransform[0].w = 0;
	m_normalTransform[1].w = 0;
	m_normalTransform[2].w = 0;
}

glm::mat4 Transform::getTransform()
{
	return m_transform;
}


Object* Transform::getObject()
{
	return m_object;
}

void Transform::applyTransform(glm::vec3 *pt)
{
	*pt = glm::vec3(m_transform * glm::vec4((*pt), 1));
}

void Transform::applyInverseTransform(glm::vec3 *pt)
{
	*pt = glm::vec3(m_invTransform*glm::vec4((*pt), 1));
}

// Translate
Translate::Translate(Object* obj, glm::vec3 t) :
	Transform(obj)
{
	setTransform(glm::translate(glm::mat4(), t));
}

Translate::Translate(Object* obj, float x, float y, float z) :
	Transform(obj)
{
	setTransform(glm::translate(glm::mat4(), glm::vec3(x, y, z)));
}

// Rotate
Rotate::Rotate(Object* obj, float x, float y, float z) :
	Transform(obj)
{
	glm::mat4 rotation = glm::rotate(glm::mat4(), x, glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, y, glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, z, glm::vec3(0, 0, 1));

	setTransform(rotation);
}

Rotate::Rotate(Object* obj, glm::vec3 axis, float degree) :
	Transform(obj)
{
	setTransform(glm::rotate(glm::mat4(), degree, axis));
}

// Scale
Scale::Scale(Object* obj, float scale) :
	Transform(obj)
{
	setTransform(glm::scale(glm::mat4(), glm::vec3(scale, scale, scale)));
}

Scale::Scale(Object* obj, float x, float y, float z) :
	Transform(obj)
{
	setTransform(glm::scale(glm::mat4(), glm::vec3(x, y, z)));
}

Scale::Scale(Object* obj, glm::vec3 scale) :
	Transform(obj)
{
	setTransform(glm::scale(glm::mat4(), scale));
}

