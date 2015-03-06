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

// Outputs are in [0, 1]

float metaballFunction(float r, float R);

float geoffFunction(float r, float R);

namespace Implicit {};

#endif // FIELDFUNCTIONS_H
