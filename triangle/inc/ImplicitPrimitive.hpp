#ifndef IMPLICIT_PRIMITIVE_H
#define IMPLICIT_PRIMITIVE_H

#include "ImplicitObject.hpp"
#include "Color.hpp"

#include <glm/glm.hpp>

namespace Implicit
{
	class Primitive : public Object
	{
	public:
		Primitive(float (*fieldFunc)(float));
		Primitive(float (*fieldFunc)(float), float coeff);

		void setFieldFunc(float (*fieldFunc)(float));
		void setFieldCoefficient(float coeff);

		virtual float getFieldValue(glm::vec3 point);
		virtual float getDistanceSq(glm::vec3 point)=0;
		virtual float getDistance(glm::vec3 point)=0;

	protected:
		float (*m_fieldFunc)(float);
		float m_fieldCoefficient;
	};
};

#endif
