#ifndef IMPLICIT_LINE_H
#define IMPLICIT_LINE_H

#include "ImplicitPrimitive.hpp"

#include <list>
#include <cmath>

namespace Implicit
{
	class Line : public Primitive
	{
	public:
		Line(float (*fieldFunc)(float), float radius, float length);
		Line(float (*fieldFunc)(float), ColorRGB color, float radius,
				float length);
		Line(float (*fieldFunc)(float), float coeff, ColorRGB color,
				float radius, float length);

		glm::vec3 getNearestPoint(glm::vec3 pt);

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
		float m_length;
		float m_lengthSq;
		glm::vec3 m_endPoint1;
		glm::vec3 m_endPoint2;
	};
};

#endif
