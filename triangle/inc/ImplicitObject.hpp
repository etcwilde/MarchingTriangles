#ifndef IMPLICIT_OBJECT_HPP
#define IMPLICIT_OBJECT_HPP

#include <glm/glm.hpp>
#include "floatlibs.hpp"

#ifdef DEBUG
#include <iostream>
#include "vecHelp.hpp"
#endif

#define FIND_ROOT_ITERS 100

namespace Implicit
{
	class Object {
	public:
		/**
		 * \brief Create new default object
		 *
		 * Sets the iso value to the default 0.5
		 * Sets the center to the default (0, 0, 0)
		 */
		Object();

		/**
		 * \brief Create new object with set iso value.
		 *
		 * Sets the desired iso value
		 * The iso value should be between 0 and 1
		 *
		 * Sets the center to the default (0, 0, 0)
		 *
		 * \param iso The iso value where the surface is defined
		 */
		Object(float iso);

		/**
		 * \brief Create a new object at a position
		 *
		 * Create the object at a defined position
		 * Sets the iso value to the default 0.5
		 *
		 * \param center The center position of the object
		 */
		Object(glm::vec3 center);

		/**
		 * \brief Create a new object at a position
		 *
		 * Create the object at a defined position
		 * with a defined iso value
		 *
		 * \param center The center position of the object
		 * \param iso The iso value where the surface is defined
		 */
		Object(glm::vec3 center, float iso);

		/**
		 * \brief Changes the iso value for the object
		 *
		 * Will change the iso value where the surface is defined.
		 * The iso value should be between 0 and 1.
		 */
		void SetIso(float iso);

		/**
		 * \brief evaluate the surface at a given point
		 *
		 * Where this evaluates to 0, the surface is defined
		 *
		 * \param point the point to evaluate
		 */
		virtual float Evaluate(glm::vec3 point)=0;

		/**
		 * \brief Evaluates field function at point
		 *
		 * Will return a value between 0 and 1
		 *
		 * \return The result of the field function at the point
		 */
		virtual float FieldValue(glm::vec3 point)=0;

		/**
		 * \brief Projects a point onto the surface of the object
		 *
		 * Note: The initial point must be within the range of the
		 * falloff field function.
		 */
		glm::vec3 Project(glm::vec3 pt);

		/**
		 * \brief Gets the normal of the surface at a given point.
		 */
		virtual glm::vec3 Normal(glm::vec3 point)=0;

		/**
		 * \brief Get an initial vertex on the surface
		 *
		 * \return The vertex on the surface of the object
		 */
		virtual glm::vec3 GetStartVertex();

	protected:

		/**
		 * \brief Secant method root finder
		 * Uses secant method to perform root finding
		 * Finds the surface of the object
		 *
		 * \param direction The direction to find the value
		 * \return The distance along the direction to move to
		 * intersect the surface
		 */
		float findRoot(glm::vec3 point, glm::vec3 direction);

		/**
		 * \brief Generate Tangent space
		 * Generates the tangent space of a given normal vector
		 *
		 * \param N The normal vector to find tangent space of
		 * \param T Where the tangent will be stored
		 * \param B Where the binormal will be stored
		 */
		void getTangentSpace(const glm::vec3& N, glm::vec3& T,
				glm::vec3& B) const;

		/**
		 * \brief Projects a vertex onto the surface
		 * \param pt The point to be projected
		 */
		glm::vec3 project(glm::vec3 pt);

		/**
		 * \brief Iso value where surface is defined
		 */
		float m_iso;

		/**
		 * \brief center position of the object
		 */
		glm::vec3 m_center;
	private:
	};
};

#endif // IMPLICIT_OBJECT_HPP
