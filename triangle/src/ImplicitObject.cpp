#include "ImplicitObject.hpp"

using namespace Implicit;

Object::Object():
	m_iso(0.5f),
	m_center()
{ }

Object::Object(float iso) :
	m_iso(iso),
	m_center()
{ }

Object::Object(glm::vec3 center, float iso) :
	m_iso(iso),
	m_center(center)
{ }

void Object::SetIso(float iso)
{
	m_iso = iso;
}

glm::vec3 Object::Project(glm::vec3 p)
{
	return project(p);
}

glm::vec3 Object::GetStartVertex()
{
	return Project(m_center);
}

float Object::findRoot(glm::vec3 point, glm::vec3 direction)
{
	direction = glm::normalize(direction);
	float ret_val;
	register float xi;
	register float xi1 = 0;
	register float xi2 = 1;
#ifdef DEBUG
	unsigned int iteration = 0;
#endif
	for (unsigned int i = 0; i < FIND_ROOT_ITERS; ++i)
	{
		register float fxi1 = Evaluate(point + (direction * xi1));
		register float fxi2 = Evaluate(point + (direction * xi2));
		xi = xi1 - fxi1 * ((xi1 - xi2)/(fxi1 - fxi2));
		if (fxi1 == fxi2)
		{
			ret_val = xi1;
#ifdef DEBUG
			iteration = i;
#endif
			break;
		}
		xi2 = xi1; xi1 = xi;
	}
#ifdef DEBUG
	std::cout << "Iterations: " << iteration << '\n';
#endif
	return ret_val;
}

void Object::getTangentSpace(const glm::vec3& N, glm::vec3& T, glm::vec3& B)
	const
{
	if (N.x > 0.5f || N.y > 0.5f) T = glm::vec3(N.y, -N.x, 0.f);
	else T = glm::vec3(-N.z, 0.f, N.x);
	B = glm::cross(N, T);
	T = glm::normalize(T);
	B = glm::normalize(B);
}

glm::vec3 Object::project(glm::vec3 pt)
{
	// the point + some distance along the gradient
	// Gives us the point on the surface
	return pt + (Normal(pt) * findRoot(pt, Normal(pt)));
}

