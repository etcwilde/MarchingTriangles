#ifndef IMPLICITOBJ_H
#define IMPLICITOBJ_H

#include "Color.hpp"

#include <glm/glm.hpp>

using namespace glm;

namespace Implicit
{

	class Point
	{
	public:
		Point();
		Point(ColorRGB color, vec3 normal);

		inline const ColorRGB& color() const;
		inline vec3 normal();

		void operator *= (const mat4& m);
		void operator *= (const float s);

	protected:
		ColorRGB m_color;
		vec3 m_normal;

	private:

	};

	class Object
	{
	public:
		virtual ~Object() {}
		virtual float getFieldValue(vec3 point) = 0;
		virtual Point getPoint(vec3 point) = 0;
		virtual bool contains(vec3 point, float tolerance) = 0;

	protected:
	private:
	};

	class ImplicitModel : public Object
	{
	public:
		ImplicitModel(float (*fieldFunc)(float));
		ImplicitModel(float (*fieldFunc)(float), float coeff);

		void setFieldFunc(float(*fieldFunc)(float));
		void setFieldCoeff(float coeff);

		virtual float getFieldValue(vec3 point);
		virtual float getDistanceSq(vec3 point) =0;

	protected:
		float (*m_fieldFunc)(float);
		float m_coeff;
	private:
	};
};
#endif // IMPLICITOBJ_H
