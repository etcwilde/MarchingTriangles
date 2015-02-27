/**
 * fieldFunctions
 *
 * File: 	fieldFunctions.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 17 2015
 */

#ifndef FIELDFUNCTIONS_H
#define FIELDFUNCTIONS_H
#include <cmath>

float solidFunction(float dist);

float linearFunction(float dist);

float parabolicFunction(float dist);

float geoffFunction(float dist);

float blinnFunction(float dist);

float metaballFunction(float dist);

float wyvillFunction(float dist);


#endif // FIELDFUNCTIONS_H
