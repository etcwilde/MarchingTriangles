/*
 * ImplicitObject
 *
 * File: 	ImplicitObject.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 18 2015
 */

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
	/**
	 * \brief Any implicitly defined shape
	 *
	 * All objects must have a position where surface is defined
	 */
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

		/**
		 * \brief Get Curvature of surface at a point
		 *
		 * Calculates the principle curvatures k1 k2
		 *
		 * Ron Goldman: Curvature formulas for implicit curves and
		 * surfaces
		 *
		 * Also found in Curvature Dependent Polygonization of Implicit
		 * Surfaces Page 3
		 *
		 * \param pt The point to find the curvature at
		 *
		 */
		void Curvature(const glm::vec3& pt, float& k1, float& k2);

	protected:
		/**
		 * \brief gets god deltas for minimizing roundoff error
		 * Used for numerical differentiation
		 * \param dx Where to store delta x
		 * \param dy where to store delta y
		 * \param dz where to store delta z
		 * \param pt Position to get deltas of
		 * \param eps Epsilon, defaults to FLT_EPSILON
		 */
		static inline void getDeltas(float& dx, float& dy, float& dz,
				const glm::vec3& pt, float eps=FLT_EPSILON);

		/**
		 * \brief Calculate Hessian matrix at a given point
		 * \param point The point to get the matrix at
		 * \return The Hessian Function Curvature matrix
		 */
		glm::mat3 hessian(const glm::vec3& point);

		/**
		 * \brief Converts the Hessian to the Curvature of the surface
		 * -- As shown in Curvature dependent polygonizers
		 *
		 * \param H Hessian matrix for the desired point
		 * \return Curvature of the surface
		 */
		glm::mat3 surfaceCurvature(const glm::mat3& H);

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
