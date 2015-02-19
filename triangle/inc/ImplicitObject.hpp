/**
 * ImplicitObject
 *
 * File: 	ImplicitObject.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 18 2015
 */

#ifndef IMPLICITOBJ_H
#define IMPLICITOBJ_H

#include "Color.hpp"

#include <glm/glm.hpp>

#include <list>

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
		inline const vec3 normal() const;

		void operator *= (const mat4& m);
		void operator *= (const float s);
		friend Point operator * (const mat4& m, const Point& p);
		friend Point operator * (mat4& m, const Point& p);


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

	/**
	 * \class Model
	 *
	 * A model contains 1 or many implicit models.
	 * These are more complex shapes than the implicit model.
	 *
	 */
	class Model
	{
	public:
		Model();
		~Model();
		Object* getRoot();

	protected:
		void setRoot(Object* r);
		void addObject(Object* o);
	private:
		std::list<Object*> m_objects;
		Object* m_root;
	};
};
#endif // IMPLICITOBJ_H
