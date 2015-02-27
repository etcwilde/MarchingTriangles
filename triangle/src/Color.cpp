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

float ColorRGB::hue()
{
	float Red = R / 255;
	float Green = G / 255;
	float Blue = B / 255;
	float Hue = 0;

	float min = std::min(std::min(Red, Green), Blue);
	float max = std::max(std::max(Red, Green), Blue);

	if (max == Red) Hue = (Green - Blue) / (max - min);
	else if (max == Green) Hue = 2.f + (Blue - Red) / (max - min);
	else Hue = 4.f + (Red - Green) / (max - min);

	Hue *= 60;

	while (Hue < 0) Hue += 360;
	return Hue;
}
