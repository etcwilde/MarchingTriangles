#ifndef IMPLICIT_SPHERE_H
#define IMPLICIT_SPHERE_H

#include "ImplicitPrimitive.hpp"

#include "Color.hpp"

#include <cmath>

#include <iostream>

namespace Implicit
{
	class Sphere : public Primitive
	{
	public:
		Sphere(float (*fieldFunc)(float), float radius);
		Sphere(float (*fieldFunc)(float), ColorRGB color, float radius);
		Sphere(float (*fieldFunc)(float), float coeff, ColorRGB color,
				float radius);

		float getFieldValue(glm::vec3 pt);
		float getDistanceSq(glm::vec3 pt);
		float getDistance(glm::vec3 pt);
		bool contains(glm::vec3 pt, float errorMargin);
		std::list<glm::vec3> getPointsInObject();
		PointFlavour getFlavour(glm::vec3 pt);


		virtual glm::vec3 gradient(glm::vec3 point);

	protected:
		ColorRGB m_color;
		float m_radius;
		float m_radiusSq;
	private:
	};
};

#endif
