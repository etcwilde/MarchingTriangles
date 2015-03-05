#include "fieldFunctions.hpp"


float Implicit::metaballFunction(float dist)
{
        // max number is a + a, max distance is b
        static const float a = 1.0f, b = 10.f;
        if (b < dist) return 0;
        if(dist >= 3.f/b && dist <= b) return (3 * a)/2 * ((1 - (dist/b)) * (1 - (dist/b)));
        else return a * (1 - (3 * dist * dist / b * b));
}
