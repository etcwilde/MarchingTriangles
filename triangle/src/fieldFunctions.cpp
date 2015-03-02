/**
 * fieldFunctions
 *
 * File: 	fieldFunctions.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Feb 19 2015
 */

#include "fieldFunctions.hpp"

float inverseFunction(float dist)
{
	return 1 / (dist * dist);
}

// Upper bound b 100
// a = 3, b = 3 
float metaballFunction(float dist)
{
	// max number is a + a, max distance is b
	static const float a = 3.f, b = 3.f;
	if (b < dist) return 0;
	if(dist >= 3.f/b && dist <= b) return (3 * a)/2 * ((1 - (dist/b)) * (1 - (dist/b)));
	else return a * (1 - (3 * dist * dist / b * b));
}

float geoffFunction(float dist)
{
	if (dist <= 1.f)
	{
		register float d = dist;
		register float s = d*d;
		register float c = s*d;
		return 1.f-(0.444444444f)*c+(1.888888888f)*s-(2.444444444f)*d;
	}
	else return 0.f;
}

float blinnFunction(float dist)
{
	return std::pow(M_E, -3*dist);
}

/*float blinnFunction(float dist)
{
} */

/*float metaballFunction(float dist)
{
	register float d = std::sqrt(dist);
	if (d <= 0.333f) return 1 - 3*dist;
	else if (d < 1.f) return 1.5f * (1-d)*(1-d);
	else return 0.f;
} */

float wyvillFunction(float dist)
{
	if (dist < 1.f) return (1 - dist) * ( 1 - dist) * (1 - dist);
	else return 0.f;
}
