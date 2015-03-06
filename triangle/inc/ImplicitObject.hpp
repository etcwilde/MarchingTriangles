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
		virtual float getFieldValue(glm::vec3 point) const = 0;

		/**
		 * Get Distance
		 *
		 * Get the distance from a skeleton point to some point in
		 * space.
		 *
		 * \param point The point to get the distance to.
		 * \return Distance
		 */
		virtual float getDistance(glm::vec3 point) const =0;
		
		/**
		 * Get Start Point
		 *
		 * Gets a point on the surface.
		 * \return Point on surface
		 */
		virtual glm::vec3 getStartPoint() const =0;
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

	private:
	};
};

#endif //IMPLICIT_OBJECT_HPP
