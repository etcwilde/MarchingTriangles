#ifndef IMPLICIT_WARP_H
#define IMPLICIT_WARP_H
#include "ImplicitObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>

#include <cmath>

namespace Implicit
{
	class Warp : public Object
	{
	public:
		Warp(Object* obj, glm::vec3 offest, glm::vec3 direction);
		float getFieldValue(glm::vec3 pt);
		PointFlavour getFlavour(glm::vec3 pt);
		bool contains(glm::vec3 pt, float errorMargin);
		std::list<glm::vec3> getPointsInObject();

		glm::vec3 warpPoint(glm::vec3 pt);
		virtual glm::vec3 warpFunction(glm::vec3 pt)=0;
	protected:
		Object* m_object;
		glm::mat4 m_transform;
		glm::mat4 m_inverseTransform;
	};

	class Twist : public Warp
	{
	public:
		Twist(Object* obj);
		Twist(Object* obj, float coeff);
		Twist(Object* obj, glm::vec3 offset, glm::vec3 direction, float coeff);

		glm::vec3 warpFunction(glm::vec3 pt);
	protected:
		float m_coeff;
	};

	class Taper : public Warp
	{
	public:
		Taper(Object* obj);
		Taper(Object* obj, float max, float min);
		Taper(Object* obj, glm::vec3 offset, glm::vec3 direction,
				float max, float min);

		glm::vec3 warpFunction(glm::vec3 pt);
	protected:
		float m_min;
		float m_max;
	};

	class Bend : public Warp
	{
	public:
		Bend(Object* obj);
		Bend(Object* obj, float rate);
		Bend(Object* obj, glm::vec3 offset, glm::vec3 direction,
				float rate);

		glm::vec3 warpFunction(glm::vec3 pt);

	protected:
		float m_rate;
	};

};

#endif
