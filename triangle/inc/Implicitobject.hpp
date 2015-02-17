#ifndef IMPLICITOBJ_H
#define IMPLICITOBJ_H

#include "Color.hpp"

#include <glm/glm.hpp>

using namespace glm;

/**
 * \namespace  Implicit
 * \brief The implicit system namespace.
 *
 * Everything pertaining to the implicit system falls under the implicit
 * namespace.
 * This includes the implicit objects themselves.
 */
namespace Implicit
{
	/**
	 * \class Point
	 * \brief Data for a given sampled point
	 *
	 * Contains the normal and color data for a given spot
	 */
	class Point
	{
	public:
		Point();
		Point(ColorRGB color, vec3 normal);

		inline const ColorRGB& color() const;
		inline vec3 normal();

		void operator *= (const mat4& m);
		void operator *= (const float s);

	protected:
		ColorRGB m_color;
		vec3 m_normal;

	private:

	};

	/**
	 * \class Object
	 * \brief Abstract Basic requirements for an implicit object
	 *
	 * All implicit objects must at least have a field function, a way to
	 * retrieve the color and normal data, and a way to determine whether a
	 * point is within the object.
	 */
	class Object
	{
	public:
		virtual ~Object() {}

		/**
		 * Returns the value of the field function at a given point
		 */
		virtual float getFieldValue(vec3 point) = 0;

		/**
		 * Returns the color and normal information at a given point
		 */
		virtual Point getPoint(vec3 point) = 0;

		/**
		 * Returns true if a point is within the implicit surface
		 */
		virtual bool contains(vec3 point, float tolerance) = 0;

	protected:
	private:
	};

	/**
	 * \class ImplicitModel
	 * \brief Abstract for implicit models
	 *
	 * Contains the basic shapes, spheres, cubes, etc..
	 * and gives a base for other more complex models.
	 */
	class ImplicitModel : public Object
	{
	public:
		ImplicitModel(float (*fieldFunc)(float));
		ImplicitModel(float (*fieldFunc)(float), float coeff);

		void setFieldFunc(float(*fieldFunc)(float));
		void setFieldCoeff(float coeff);

		virtual float getFieldValue(vec3 point);
		virtual float getDistanceSq(vec3 point) =0;

	protected:
		float (*m_fieldFunc)(float);
		float m_coeff;
	private:
	};
};
#endif // IMPLICITOBJ_H
