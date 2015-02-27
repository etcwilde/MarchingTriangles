#ifndef IMPLICIT_TORUS_H
#define IMPLICIT_TORUS_H
#include "ImplicitPrimitive.hpp"
#include "Color.hpp"
namespace Implicit
{
	class Torus : public Primitive
	{
	public:
		Torus(float (*fieldFunc)(float), float innerRadius,
				float outerRadius);
		Torus(float (*fieldFunc)(float), ColorRGB color,
				float innerRadius, float outerRadius);
		Torus(float (*fieldFunc)(float), float coeff, ColorRGB color,
				float innerRadius, float outerRadius);

		glm::vec3 getNearestPoint(glm::vec3 pt);
		float getFieldValue(glm::vec3 pt);
		float getDistanceSq(glm::vec3 pt);
		float getDistance(glm::vec3 pt);
		bool contains(glm::vec3 pt, float errorMargin);
		std::list<glm::vec3> getPointsInObject();
		PointFlavour getFlavour(glm::vec3 pt);
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
