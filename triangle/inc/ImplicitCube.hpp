#ifndef IMPLICIT_CUBE
#define IMPLICIT_CUBE
#include "ImplicitPrimitive.hpp"
#include "Color.hpp"

#include <algorithm>
#include <cmath>
#include <list>
#include <complex>

namespace Implicit
{
	class Cube : public Primitive
	{
	public:
		Cube(float (*fieldFunc)(float), float radius, float sides);
		Cube(float (*fieldFunc)(float), ColorRGB color, float radius,
				float sides);
		Cube(float (*fieldFunc)(float), float coeff, ColorRGB color,
				float radius, float sides);
		Cube(float (*fieldFunc)(float), float radius, float x, float y,
				float z);
		Cube(float (*fieldFunc)(float), ColorRGB color, float radius,
				float x, float y, float z);
		Cube(float (*fieldFunc)(float), float coeff, ColorRGB color,
				float radius, float x, float y, float z);

		glm::vec3 getNearestPoint(glm::vec3 pt);

		float getFieldValue(glm::vec3 point);
		float getDistanceSq(glm::vec3 point);
		float getDistance(glm::vec3 point);
		bool contains(glm::vec3 point, float errorMargin);
		std::list<glm::vec3> getPointsInObject();
		PointFlavour getFlavour(glm::vec3 point);

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
