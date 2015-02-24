#ifndef IMPLICIT_JACK_H
#define IMPLICIT_JACK_H

#include "ImplicitObject.hpp"
#include "Color.hpp"

#include <glm/glm.hpp>

#include <cmath>
using namespace glm;

namespace Implicit
{

	class Jack : public ImplicitModel
	{
	public:
		Jack(float (*fieldFunc)(float));
		Jack(float (*fieldFunc)(float), float coeff);

		float getFieldValue(vec3 pt);
		float getDistanceSq(vec3 pt);

		bool contains(vec3 pt, float tolerance);
		bool touches(vec3 pt, float tolerance);

		Point getPoint(vec3 pt);

	protected:
		ColorRGB m_color;
	};
};

#endif
