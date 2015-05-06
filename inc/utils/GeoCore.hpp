#ifndef GEOCORE_HPP
#define GEOCORE_HPP
// Useful for geometry utilities
//

#include <cmath>

#include <glm/glm.hpp>

/**
 * \brief Computes the tangent space of a normal N
 *
 * \param N Normal (must be normalized)
 * \param T Tangent
 * \param B Binormal
 */
inline void TangenSpace(const glm::vec3& N, glm::vec3& T, glm::vec3& B)
{
	if (N.x > 0.5f || N.y > 0.5f) T = glm::vec3(N.y, -N.x, 0.f);
	else T = glm::vec3(-N.z, 0.f, N.x);
	B = glm::cross(N, T);
	T = glm::normalize(T);
	B = glm::normalize(B);
}
/**
 * \brief Finds the angle between two vectors A and B at the origin
 *
 * The angle is being measured at the vertex [0, 0, 0]
 * \param A A vertex in 3D space (one of the legs)
 * \param B A vertex in 3D space (one of the legs)
 */
inline float Angle(const glm::vec3& A, const glm::vec3& B)
{
	return std::acos(glm::dot(A, B) / (glm::length(A) * glm::length(B)));
}
/**
 * \brief Finds the angle between two vectors at an arbitrary point
 *
 * The angle is measured at the vertex base
 * \param left A vertex in 3D space (one of the legs)
 * \param right A vertex in 3D space (one of the legs)
 */
inline float Angle(const glm::vec3& base, const glm::vec3& left, const glm::vec3& right)
{
	return Angle(left - base, right - base);
}
/**
 * \brief Finds the radius of curvature
 *
 * Defined in Curvature depended Polygonization
 *
 * Useful for finding the heuristic edge length of the triangle
 */
inline float RadiusOfCurvature(const float& k1, const float& k2)
{
	return 1 / (std::max(std::abs(k1), std::abs(k2)) + FLT_EPSILON);
}



#endif//GEOCORE_HPP
