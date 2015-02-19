#include "ImplicitTransforms.hpp"

using namespace Implicit;

Transform::Transform(Object* obj) :
	Object(),
	m_object(obj),
	m_transform(),
	m_inverse(),
	m_transformed_normal()
{ }

Transform::Transform(Object* obj, mat4 transform) :
	Object(),
	m_object(obj),
	m_transform(transform),
	m_inverse(),
	m_transformed_normal()
{
	setTransform(transform);
}

float Transform::getFieldValue(vec3 pt)
{
	applyInverseTransform(&pt);
	return m_object->getFieldValue(pt);
}

Point Transform::getPoint(vec3 pt)
{
	applyInverseTransform(&pt);
	(m_object->getPoint(pt));
	//return m_transformed_normal * (m_object->getPoint(pt));
	return m_object->getPoint(pt);

	//return (m_object->getPoint(pt)) * m_transformed_normal;
	//return m_transformed_normal * (m_object->getPoint(pt));
	// TODO: Fix multiplication between point and matrix
}

bool Transform::contains(vec3 pt, float tolerance)
{
	applyInverseTransform(&pt);
	return m_object->contains(pt, tolerance);
}


// Protected Methods

void Transform::setTransform(const mat4& t)
{
	m_transform = t;
	Transform *tr = dynamic_cast<Transform*>(m_object);
	if (tr != NULL)
	{
		m_transform = t * tr->getTransform();
		m_object = tr->getObject();
	}
	else
	{
		// Not a transform
	}

	m_inverse = inverse(t);
	m_transformed_normal = transpose(m_inverse);
}


const mat4& Transform::getTransform() const
{
	return m_transform;
}

Object* Transform::getObject()
{
	return m_object;
}

void Transform::applyTransform(vec3 *point)
{
	*point = vec3(m_transform * vec4((vec3)(*point), 1));
}

void Transform::applyInverseTransform(vec3 *point)
{
	*point = vec3(m_inverse *vec4((vec3)(*point), 1));
}


/**
 * Translate
 */
Translate::Translate(Object* obj, vec3 translate) :
	Transform(obj)
{
	mat4 t(1.f);
	t = glm::translate(t, translate);
	setTransform(t);
}

Translate::Translate(Object* obj, float x, float y, float z) :
	Transform(obj)
{
	mat4 t(1.f);
	t = translate(t, vec3(x, y, z));
	setTransform(t);
}

/**
 * Rotate
 */
Rotate::Rotate(Object* obj, vec3 axis, float degrees) :
	Transform(obj)
{
	mat4 r(1.f);
	r = rotate(r, degrees, axis);
	setTransform(r);
}

Rotate::Rotate(Object* obj, float x, float y, float z) :
	Transform(obj)
{
	mat4 r(1.f);
	r = rotate(r, x, vec3(1.f, 0.f, 0.f));
	r = rotate(r, y, vec3(0.f, 1.f, 0.f));
	r = rotate(r, z, vec3(0.f, 0.f, 1.f));
	setTransform(r);
}

/**
 * Scale
 */
Scale::Scale(Object* obj, float s) :
	Transform(obj)
{
	mat4 scale(1.f);
	scale = glm::scale(scale, vec3(s, s, s));
	setTransform(scale);
}

Scale::Scale(Object* obj, float x, float y, float z) :
	Transform(obj)
{
	mat4 scale(1.f);
	scale = glm::scale(scale, vec3(x, y, z));
	setTransform(scale);
}

Scale::Scale(Object* obj, vec3 scale) :
	Transform(obj)
{
	mat4 s(1.f);
	s = glm::scale(s, scale);
	setTransform(s);
}
