#ifndef IMPLICIT_TORUS_H
#define IMPLICIT_TORUS_H

#include "ImplicitObject.hpp"
#include "Color.hpp"

#include <glm/glm.hpp>

using namespace glm;


namespace Implicit
{
	class Torus : public ImplicitModel
	{
	public:
		Torus(float (*fieldFunc)(float), float innerRadius, float outerRadius);
		Torus(float (*fieldFunc)(float), ColorRGB color,
				float innerRadius, float outerRadius);

		Torus(float (*fieldFunc)(float), float coeff, float innerRadius,
				float outerRadius);

		float getFieldValue(vec3 pt);
		float getDistanceSq(vec3 pt);

		bool contains(vec3 pt, float tolerance);
		bool touches(vec3 pt, float tolerance);

		Point getPoint(vec3 pt);

		vec3 getNearestPoint(vec3 pt);

	protected:
		ColorRGB m_color;
		float m_innerRadius;
		float m_outerRadius;
		float m_width;
		float m_widthSq;
		float m_centerRadius;

	};
};

#endif
