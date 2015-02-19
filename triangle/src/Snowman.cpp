/**
 * Snowman
 *
 * File: 	Snowman.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 18 2015
 */

#include "Snowman.hpp"
using namespace Implicit;

Snowman::Snowman() :
	Model()
{
	Object* body_sphere = new Sphere(geoffFunction, ColorRGB(1, 1, 1), 1.f);
	Object* button_sphere = new Sphere(wyvillFunction, ColorRGB(1, 0, 0),
			0.1f);
	addObject(body_sphere);
	addObject(button_sphere);
}
