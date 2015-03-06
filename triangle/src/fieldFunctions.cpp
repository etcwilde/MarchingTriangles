/**
 * fieldFunctions
 *
 * File: 	fieldFunctions.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 19 2015
 */

#include "fieldFunctions.hpp"

using namespace Implicit;


float metaballFunction(float r, float R)
{
	if (R < r) return 0;
	if(r >= 3.f/R && r <= R) return 0.75f * ((1 - (r/R)) * (1 - (r/R)));
	else return 0.5f * (1 - (3 * r * r / R * R));
}

float geoffFunction(float r, float R)
{
	register const float rs = (r * r) / (R * R);
	register const float rq = rs * rs;
	register const float rse = rq * rs;
	return 1 - (4/9)*rse + (17/9) * rq - (22/9)*rs;
}



