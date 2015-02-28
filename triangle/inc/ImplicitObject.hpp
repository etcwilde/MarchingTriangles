#ifndef IMPLICIT_OBJECT_H
#define IMPLICIT_OBJECT_H

// These two are just place-holders right now
#define NUMERICAL_ITERATIONS 5
#define NUMERICAL_EPSILON 5e-5

#include <glm/glm.hpp>

#include <list>

#include "Color.hpp"

namespace Implicit
{
	class PointFlavour
	{
	public:
		PointFlavour():
			m_color(),
			m_normal()
		{}
		PointFlavour(ColorRGB color, glm::vec3 normal) :
			m_color(color), m_normal(normal)
		{}

		ColorRGB color() { return m_color; }
		glm::vec3 normal() { return m_normal; }

		PointFlavour& operator *= (const glm::mat4& rs)
		{
			m_normal = glm::vec3(rs * glm::vec4(m_normal, 1));
			return *this;
		}

		PointFlavour& operator *= (const float rs)
		{
			m_normal = rs * m_normal;
			return *this;
		}

	private:
		ColorRGB m_color;
		glm::vec3 m_normal;
	};

	class Object
	{
	public:
		virtual ~Object() {}
		virtual float getFieldValue(glm::vec3 point) = 0;
		virtual glm::vec3 gradient(glm::vec3 point);
		virtual float maxCurvature(glm::vec3 point);
		virtual PointFlavour getFlavour(glm::vec3 point) = 0;
		virtual bool contains(glm::vec3 point, float errorMargin) = 0;
		virtual std::list<glm::vec3> getPointsInObject() = 0;
	protected:
		// Secant Method
		virtual float derivative(glm::vec3 pt);
	private:
	};


};



#endif
