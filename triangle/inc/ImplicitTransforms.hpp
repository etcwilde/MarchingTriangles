#ifndef IMPLICIT_TRANSFORM_H
#define IMPLICIT_TRANSFORM_H

#include "ImplicitObject.hpp"

#include <glm/glm.hpp>

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
};
#endif // IMPLICIT_TRANSFORM_H
