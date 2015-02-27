#ifndef IMPLICIT_PLANE_H
#define IMPLICIT_PLANE_H

#include "ImplicitPrimitive.hpp"

#include "Color.hpp"

#include <glm/glm.hpp>

#include <list>
#include <cmath>

namespace Implicit
{
	class Plane : public Primitive
	{
	public:
		Plane(float (*fieldFunc)(float), float radius);
		Plane(float (*fieldFunc)(float), ColorRGB color, float radius);
		Plane(float (*fieldFunc)(float), float coeff, ColorRGB color,
				float radius);

		float getFieldValue(glm::vec3 pt);
		float getDistanceSq(glm::vec3 pt);
		float getDistance(glm::vec3 pt);
		bool contains(glm::vec3 pt, float errorMargin);
		std::list<glm::vec3> getPointsInObject();
		PointFlavour getFlavour(glm::vec3 pt);

	protected:
		ColorRGB m_color;
		float m_radius;
		float m_radiusSq;
	};
};

#endif
