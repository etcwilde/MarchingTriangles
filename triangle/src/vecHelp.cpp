#include "vecHelp.hpp"
ostream& operator<<(ostream& os, glm::vec3 v)
{
	os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}
