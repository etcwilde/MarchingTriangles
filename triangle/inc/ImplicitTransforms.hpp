#ifndef IMPLICIT_TRANSFORM_H
#define IMPLICIT_TRANSFORM_H

#include "ImplicitObject.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;


namespace Implicit
{
	/**
	 * \class Transform
	 * A transformation of an implicit object
	 */
	class Transform : public Object
	{
	public:
		Transform(Object* obj, mat4 transform);

		float getFieldValue(vec3 point);
		Point getPoint(vec3 point);
		bool contains(vec3 point, float tolerance);

	protected:
		Transform(Object* obj);
		void setTransform(const mat4& transform);
		const mat4& getTransform() const;
		Object* getObject();

		void applyTransform(vec3* pt);
		void applyInverseTransform(vec3* pt);
	private:
		Object* m_object;
		mat4 m_transform;
		mat4 m_inverse;
		mat4 m_transformed_normal;
	};

	class Translate : public Transform
	{
		Translate(Object* obj, vec3 translate);
		Translate(Object* obj, float x, float y, float z);
	};

	class Rotate : public Transform
	{
		Rotate(Object* obj, vec3 axis, float degrees);
		Rotate(Object* obj, float x, float y, float z);
	};

	class Scale : public Transform
	{
		Scale(Object* obj, float s);
		Scale(Object* obj, float x, float y, float z);
		Scale(Object* obj, vec3 scale);
	};

};
#endif // IMPLICIT_TRANSFORM_H
