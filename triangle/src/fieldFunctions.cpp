/*
 * fieldFunctions
 *
 * File: 	fieldFunctions.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 19 2015
 */

#include "fieldFunctions.hpp"

float geoffFunction(float r, float R)
{
	register const float rs = (r * r) / (R * R);
	register const float rq = rs * rs;
	register const float rse = rq * rs;
	return 1 - (4.f/9.f) * rse + (17.f/9.f) * rq - (22.f/9.f) * rs;
}
