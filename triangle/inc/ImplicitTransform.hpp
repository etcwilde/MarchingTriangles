#ifndef IMPLICIT_TRANSFORM_H
#define IMPLICIT_TRANSFORM_H

#include "ImplicitObject.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Implicit
{
	class Transform : public Object
	{
	public:
		Transform(Object* obj, glm::mat4 transform);

		float getFieldValue(glm::vec3 pt);
		PointFlavour getFlavour(glm::vec3 pt);
		bool contains(glm::vec3 pt, float errorMargin);
		std::list<glm::vec3> getPointsInObject();

	protected:
		Transform(Object* obj);
		void setTransform(glm::mat4 transform);
		glm::mat4 getTransform();
		Object* getObject();

		void applyTransform(glm::vec3 *pt);
		void applyInverseTransform(glm::vec3 *pt);

		Object* m_object;
		glm::mat4 m_transform;
		glm::mat4 m_invTransform;
		glm::mat4 m_normalTransform;
	};

	class Translate : public Transform
	{
	public:
		Translate(Object* obj, glm::vec3 translate);
		Translate(Object* obj, float x, float y, float z);
	};

	class Rotate : public Transform
	{
	public:
		Rotate(Object* obj, float x, float y, float z);
		Rotate(Object* obj, glm::vec3 axis, float degree);
	};

	class Scale : public Transform
	{
	public:
		Scale(Object* obj, float scale);
		Scale(Object* obj, float x, float y, float z);
		Scale(Object* obj, glm::vec3 scale);
	};
};

#endif
