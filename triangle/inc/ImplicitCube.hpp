#ifndef IMPLICIT_CUBE_H
#define IMPLICIT_CUBE_H

#include "ImplicitObject.hpp"
#include "Color.hpp"

#include <complex>

#include <glm/glm.hpp>

using namespace glm;

namespace Implicit
{
	class Cube : public ImplicitModel
	{
	public:
		Cube(float (*fieldFunc)(float), float radius, float sides);
		Cube(float (*fieldFunc)(float), ColorRGB color, float r, float sides);
		Cube(float (*fieldFunc)(float), float coeff, ColorRGB color,
				float r, float sides);
		Cube(float (*fieldFunc)(float), float radius, float x, float y, float z);
		Cube(float (*fieldFunc)(float), ColorRGB color, float radius, float x, float y, float z);


		float getFieldValue(vec3 pt);
		float getDistanceSq(vec3 pt);

		bool contains(vec3 pt, float tolerance);
		bool touches (vec3 pt, float tolerance);

		Point getPoint(vec3 pt);

		vec3 getNearestPoint(vec3 pt);

	protected:
		ColorRGB m_color;
		float m_radius;
		float m_radiusSq;
		float m_x;
		float m_y;
		float m_z;
	};
};

#endif

