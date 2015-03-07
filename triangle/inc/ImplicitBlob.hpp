#ifndef IMPLICIT_BLOB_HPP
#define IMPLICIT_BLOB_HPP

/**
 * This is a simple version of implicits
 */


#include <glm/glm.hpp>

#include "fieldFunctions.hpp"
#include "ImplicitObject.hpp"

#ifdef DEBUG
#include <iostream>
#endif

/**
 * \namespace Implicit
 *
 * Implicits are objects with field functions where surface is defined at a
 * given iso value.
 */
namespace Implicit
{
	class Blob : public Object
	{

	typedef float(*FieldFunction)(float, float);
	public:
		Blob(FieldFunction, float iso);
		Blob(FieldFunction, float iso, float max_distance);
		Blob(FieldFunction, float iso, glm::vec3 center);
		Blob(FieldFunction, float iso, glm::vec3 center, float max_distance);

		float getFieldValue(glm::vec3 pt);

		float getDistance(glm::vec3 pt) const;
		glm::vec3 getStartPoint();

		/**
		 * Maximum distance from the point where anything is defined
		 */
		float getMaxDist() const;

		glm::vec3 getCenter() const;

		virtual float evaluate(float r);
	protected:

	private:
		FieldFunction m_fieldFunc;
		float m_iso;
		glm::vec3 m_center;
		float m_max_distance;
	};
};

#endif //IMPLICIT_BLOB_HPP
