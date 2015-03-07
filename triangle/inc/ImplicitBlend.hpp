#ifndef IMPLICIT_BLEND_HPP
#define IMPLICIT_BLEND_HPP

#include <list>

#include <glm/glm.hpp>

#include "ImplicitObject.hpp"
#include "ImplicitBlob.hpp"

namespace Implicit
{
	class Blend : public Object
	{
	public:
		Blend();
		Blend(float iso);
		void addObject(Object* obj);

		float getFieldValue(glm::vec3 pt);
		virtual glm::vec3 getStartPoint();


		virtual float evaluate(float r);
	protected:

	private:
		//glm::vec3 project_to_surface(glm::vec3 initial_guess) const;

		std::list<Object*> m_objects;
		float m_iso;

	};
};

#endif //IMPLICIT_BLEND_HPP
