#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>

namespace Implicit
{
	class Sphere
	{
	public:
		Sphere(float (*fieldFunc)(float));
		Sphere(float (*fieldFunc)(float), float radius);

		float radius();

		float evaluate(glm::vec3 point);
		float getFieldValue(float r);

		glm::vec3 project(glm::vec3 pt);

		//Should only work on points that have been projected
		float distance(glm::vec3 pt);


	private:
		glm::vec3 gradient(glm::vec3 pt);

		float (*m_fieldFunc)(float);
		float m_radius;
	};
};

#endif
