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
	Group* body = addGroup(new RicciBlend(4.f, 2));
	Object* bodySphere = addObject(new Sphere(geoffFunction, ColorRGB(1.f, 1.f, 1.f), 1.f));

	Object* buttonSphere = addObject(new Sphere(wyvillFunction, ColorRGB(1.f, 0.f, 0.f), 0.1f));
	Object* button1 = addObject(new Translate(buttonSphere, 0.0f, 0.15f, -.49f));
	Object* button2 = addObject(new Translate(buttonSphere, 0.0f, -0.15f, -0.49f));
	Object* scale = addObject(new Scale(body, 0.8f));
	Object* translate = addObject(new Translate(scale, 0.0f, 0.6f, 0.0f));

	body->addRecursiveObject(bodySphere);
	body->addRecursiveObject(translate);
	body->addRecursiveObject(button1);

	Group* head = addGroup(new Union());
	Object* eye_sphere = addObject(new Sphere(wyvillFunction, ColorRGB(0.f, 0.f, 0.f), 0.16f));
	Object* left_eye = addObject(new Translate(eye_sphere, -.2f, .12f, -.41f));
	Object* right_eye = addObject(new Translate(eye_sphere, 2.f, .12f, -.41f));

	head->addBaseObject(bodySphere);
	head->addBaseObject(left_eye);
	head->addBaseObject(right_eye);

	body->addBaseObject(head);

	setRoot(body);
}
