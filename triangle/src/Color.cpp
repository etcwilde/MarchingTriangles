/**
 * Color
 *
 * File: 	Color.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 15 2015
 */

#include "Color.hpp"

ColorRGB::ColorRGB() :
	R(0),
	G(0),
	B(0)
{}

// Cap between 255 and 0
ColorRGB::ColorRGB(float r, float g, float b)
{
	R = r > 255.f ? 255.f : (r < 0.f ? 0.f : r);
	G = g > 255.f ? 255.f : (g < 0.f ? 0.f : g);
	B = b > 255.f ? 255.f : (b < 0.f ? 0.f : b);
}


inline float ColorRGB::r() const { return R; }

inline float ColorRGB::g() const { return G; }

inline float ColorRGB::b() const { return B; }

const float* ColorRGB::data() const {return m_vals;}

void ColorRGB::operator +=(const ColorRGB& color)
{
	R = std::min((R + color.r()) / 2, 255.f);
	G = std::min((G + color.g()) / 2, 255.f);
	B = std::min((B + color.b()) / 2, 255.f);
}

void ColorRGB::operator -= (const ColorRGB& color)
{
	R = std::max((R - color.r()) * 2, 0.f);
	G = std::max((G - color.g()) * 2, 0.f);
	B = std::max((B - color.b()) * 2, 0.f);
}

ColorRGB ColorRGB::operator + (const ColorRGB& color) const
{
	return ColorRGB(
			std::min((R + color.r())/2, 255.f),
			std::min((G + color.g())/2, 255.f),
		       	std::min((B + color.b())/2, 255.f));
}

ColorRGB ColorRGB::operator -(const ColorRGB& color) const
{
	return ColorRGB (
			std::max((R - color.r()) * 2, 0.f),
			std::max((G - color.g()) * 2, 0.f),
			std::max((B - color.b()) * 2, 0.f));
}
