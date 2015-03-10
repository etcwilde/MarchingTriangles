#ifndef IMPLICIT_PRIMITIVE_HPP
#define IMPLICIT_PRIMITIVE_HPP

#include "ImplicitObject.hpp"

#include <glm/glm.hpp>

#ifdef DEBUG
#include <iostream>
#endif

namespace Implicit
{

	typedef float(*FieldFunction)(float, float);

	class Primitive : public Object
	{
	public:
		/**
		 * \brief Create new primitive
		 *
		 * Creates a default primitive with a field function
		 * The default iso value is 0.5
		 * The default radius is 1
		 *
		 * \param f The FieldFunction for the Primitive
		 */
		Primitive(FieldFunction f);

		/**
		 * \brief Create new Primitive
		 *
		 * Creates a Primitive with a defined iso value
		 * The default radius is 1
		 * \param f The FieldFunction for the primitive
		 * \param iso The iso value where the function is defined
		 */
		Primitive(FieldFunction f, float iso);

		/**
		 * \brief Create new Primitive
		 *
		 * Creates a new Primitive with a defined FieldFunction, iso
		 * value and radius.
		 *
		 * \param f The FieldFunction for the Primitive
		 * \param iso The iso value where the surface is defined
		 * \param radius The radius of the object
		 */
		Primitive(FieldFunction f, float iso, float radius);

		/**
		 * \brief Create new Primitive
		 *
		 * Creates a new Primitive with a defined FieldFunction, iso
		 * value and radius.
		 *
		 * \param f The FieldFunction for the Primitive
		 * \param center The center position of the primitive
		 * \param iso The iso value where the surface is defined
		 * \param radius The radius of the object
		 */
		Primitive(FieldFunction f, glm::vec3 center, float iso,
				float radius);

		/**
		 * \brief Changes the radius of the object
		 *
		 * \param radius The maximum distance where the field function
		 * is not 0
		 */
		void SetRadius(float radius);

		/**
		 * \brief Evaluates the field function at a distance
		 *
		 * Will return a value between 0 and 1
		 * \return The result of the field function at distance r
		 */
		virtual float FieldValue(float r);

		/**
		 * \brief Evaluate the surface at a distance
		 *
		 * Where this evaluates to 0, the surface is defined
		 *
		 * \param r The distance to evaluate the function
		 */
		virtual float Evaluate(float r);

		/**
		 * \brief Evaluate the surface at a given point
		 *
		 * Where this evaluates to 0, the surface is defined
		 *
		 * \param point The point to evaluate
		 */
		virtual float Evaluate(glm::vec3 point);

		/**
		 * \brief Evaluate the field function at a given point
		 *
		 * \param point The point to evaluate
		 */
		virtual float FieldValue(glm::vec3 point);

		glm::vec3 StartPoint();
	protected:

		/**
		 * \brief Get distance to point
		 *
		 * \param pt The point to get the distance of
		 * \return The distance from the center to the point
		 */
		float getDistance(glm::vec3 pt);

		/**
		 * \brief Field falloff function of the primitive blob
		 */
		FieldFunction m_fieldFunction;
		/**
		 * \brief Maximum radius of the primitive
		 */
		float m_radius;
	private:

	};
};

#endif // IMPLICIT_PRIMITIVE_HPP