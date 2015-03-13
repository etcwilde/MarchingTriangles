/*
 * ImplicitBlend
 *
 * File: 	ImplicitBlend.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 06 2015
 */

#ifndef IMPLICIT_BLEND_HPP
#define IMPLICIT_BLEND_HPP

#include "ImplicitObject.hpp"

#include <list>

#ifdef DEBUG
#include <iostream>
#endif

namespace Implicit
{
	/**
	 * \brief Blends multiple primitive objects into one blobject
	 */
	class Blend : public Object
	{
	public:
		/**
		 * \brief Create a blend object
		 * Uses default iso value of 0.5
		 */
		Blend();

		/**
		 * \brief Create a blend object with defined iso value
		 *
		 * \param iso The value where the surface is defined
		 */
		Blend(float iso);

		/**
		 * \brief Create a blend object with defined iso value
		 *
		 * \param iso The value where the surface is defined
		 * \param center The center of the blend object
		 */
		Blend(float iso, glm::vec3 center);

		/**
		 * \brief Add object to blend
		 *
		 * Adds more objects to be blended
		 *
		 * \param obj The address of the primitive to be added to the
		 * blend object
		 */
		void AddObject(Object* obj);

		virtual float Evaluate(glm::vec3 point);
		virtual float FieldValue(glm::vec3 point);

		virtual glm::vec3 Normal(glm::vec3 point);
	protected:

	private:
		std::list<Object*> m_objects;
	};
};

#endif // IMPLICIT_BLEND_HPP
