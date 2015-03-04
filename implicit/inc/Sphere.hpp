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
		float getFieldFunc(float r);


	private:
		float (*m_fieldFunc)(float);
		float m_radius;
	};
};

#endif
