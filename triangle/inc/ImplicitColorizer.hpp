#ifndef IMPLICIT_COLORIZER_H
#define IMPLICIT_COLORIZER_H
#include "Color.hpp"
#include "ImplicitObject.hpp"
#include "Perlin.hpp"

namespace Implicit
{
	class Colorizer : public Object
	{
	public:
		Colorizer(Object* obj);
		float getFieldValue(glm::vec3 pt);
		PointFlavour getFlavour(glm::vec3 pt);
		bool contains(glm::vec3, float errorMargin);
		std::list<glm::vec3> getPointsInObject();

		void setObject(Object* obj);

		virtual ColorRGB transformColor(glm::vec3 pt, ColorRGB color)=0;

	protected:
		Object* m_obj;
	};

	class SolidColorizer : public Colorizer
	{
	public:
		SolidColorizer(Object* obj, ColorRGB color) :
			Colorizer(obj),
			m_color(color)
		{}

		virtual ColorRGB transformColor(glm::vec3 point, ColorRGB color)
		{
			// Solid colour
			return m_color;
		}
	protected:
		ColorRGB m_color;
	};

	/*class HueShiftColorizer : public Colorizer
	{
	public:
		HueShiftColorizer(Object* obj, float shift) :
			Colorizer(obj),
			m_shift(shift)
		{}

		virtual ColorRGB transformColor(glm::vec3 point, ColorRGB color)
		{
			float hue = color.hue() + m_shift;
			hue = (hue < 0.f) ? hue + 1.f : ((hue > 1.f) ? hue - 1.f : hue);
			return ColorRGB(
		}

	protected:
		float m_shift;

	}; */

	class NoiseShadeColorizer : public SolidColorizer
	{
	public:
		NoiseShadeColorizer(Object* obj, NoiseGenerator* generator, ColorRGB color) :
			SolidColorizer(obj, color),
			m_generator(generator)
		{}

		ColorRGB transformColor(glm::vec3 point, ColorRGB color)
		{
			float noise = m_generator -> generateNoise(
					point.x, point.y, point.z);
			noise = (1.f + noise) / 2.f;
			return ColorRGB(m_color.r() * noise,
					m_color.g() * noise,
					m_color.b() * noise);
		}

	protected:
		NoiseGenerator * m_generator;
	};

	class NoiseColorizer : public Colorizer
	{
	public:
		NoiseColorizer(Object* obj, NoiseGenerator* generator, ColorRGB high, ColorRGB low) :
			Colorizer(obj),
			m_generator(generator),
			m_highColor(high),
			m_lowColor(low)
		{}

		ColorRGB transformColor(glm::vec3 point, ColorRGB color)
		{
			float noise = m_generator->generateNoise(
					point.x, point.y, point.z);
			float high = (1.f + noise)/1.6f;
			float low = 1.f - high;
			return ColorRGB(m_highColor.r()* high +
					m_lowColor.r() * low,
					m_highColor.g() * high +
					m_lowColor.g() * low,
					m_highColor.b() * high +
					m_lowColor.b() * low);
		}

	protected:
		NoiseGenerator* m_generator;
		ColorRGB m_highColor;
		ColorRGB m_lowColor;

	};

};

#endif
