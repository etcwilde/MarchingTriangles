/*
 * vecHelp
 *
 * File: 	vecHelp.cpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 06 2015
 */

#include "vecHelp.hpp"
ostream& operator<<(ostream& os, glm::vec3 v)
{
	os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}
