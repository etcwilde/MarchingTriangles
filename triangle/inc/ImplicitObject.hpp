#ifndef IMPLICIT_OBJECT_HPP
#define IMPLICIT_OBJECT_HPP

#include <glm/glm.hpp>
#include "vecHelp.hpp"

namespace Implicit
{
	class Object
	{
	public:
		/**
		 * Get Field Value
		 *
		 * Evaluate the filter field falloff function at a vertex.
		 *
		 * \param point The point at which to get the value
		 * \return Field Function evaluated at the point
		 */
		virtual float getFieldValue(glm::vec3 point) = 0;

		/**
		 * Get Start Point
		 *
		 * Gets a point on the surface.
		 * \return Point on surface
		 */
		virtual glm::vec3 getStartPoint()=0;

		/**
		 * Evaluate the field function with respect to the local iso
		 * value
		 */
		virtual float evaluate(float r)= 0;
	protected:


		/**
		 * Get tangent space
		 *
		 * Given a Normal N, defines the Tangent T, and binormal B.
		 *
		 * This method writes to vector T and vector B
		 * \param N Normalized normal
		 * \param T Vector to write tangent to
		 * \param B Vector to write binormal to
		 */
		void get_tangent_space(const glm::vec3& N,
				glm::vec3& T, glm::vec3& B) const;

		/**
		 * Finds the radius at which the iso value is satisfied
		 */
		float findRoot(float r);

		glm::vec3 project_to_surface(glm::vec3 initial_guess);


	private:
	};
};

#endif //IMPLICIT_OBJECT_HPP
