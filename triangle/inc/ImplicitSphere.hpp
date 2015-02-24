/**
 * ImplicitSphere
 *
 * File: 	ImplicitSphere.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 16 2015
 */

#ifndef IMPLICIT_SPHERE_H
#define IMPLICIT_SPHERE_H

#include "ImplicitObject.hpp"
#include "Color.hpp"

#include <glm/glm.hpp>

using namespace glm;

namespace Implicit
{
	/**
	 * \class Sphere
	 * \brief implicit sphere
	 *
	 * The implementation of the implicit sphere model
	 */
	class Sphere : public ImplicitModel
	{
	public:
		Sphere(float (*fieldFunc)(float), float radius);
		Sphere(float (*fieldFunc)(float), ColorRGB color, float radius);
		Sphere(float (*fieldFunc)(float), float coeff, ColorRGB color,
				float radius);

		float getFieldValue(vec3 pt);
		float getDistanceSq(vec3 pt);
		// float getDistance(vec3 pt);
		bool contains(vec3 pt, float tolerance);
		bool touches(vec3 pt, float tolerance);

		Point getPoint(vec3 pt);

	protected:
		ColorRGB m_color;
		float m_radius;
		float m_radiusSq;

	private:
	};
};

#endif // IMPLICIT_SPHERE_H
