#include "fieldFunctions.hpp"


float Implicit::metaballFunction(float dist)
{
	// a == 1, max dist is b
        // max number is a + a, max distance is b
        static const float a = 0.5f, b = 10.f;
        if (b < dist) return 0;
        if(dist >= 3.f/b && dist <= b) return 0.75f * ((1 - (dist/b)) * (1 - (dist/b)));
        else return a * (1 - (3 * dist * dist / b * b));
}

float Implicit::wyvillFunction(float r)
{
	return 0;
}
