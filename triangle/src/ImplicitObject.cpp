#include "ImplicitObject.hpp"

using namespace Implicit;

void Object::get_tangent_space(const glm::vec3& N, glm::vec3& T, glm::vec3& B) const
{
	if (N.x > 0.5f || N.y > 0.5f) T = glm::vec3(N.y, -N.x, 0.f);
	else T = glm::vec3(-N.z, 0.f, N.x);
	B = glm::cross(N, T);
	T = glm::normalize(T);
	B = glm::normalize(B);
}
