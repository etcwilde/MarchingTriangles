/*
 * vecHelp
 *
 * File: 	vecHelp.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 06 2015
 */

#ifndef VECHELP_HPP
#define VECHELP_HPP

// To help with vectors

#include <glm/vec3.hpp>
#include <ostream>
using std::ostream;

ostream& operator<<(ostream& os, glm::vec3 v);


#endif // VECHELP_HPP
