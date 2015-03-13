/*
 * ImplicitSystem
 *
 * File: 	ImplicitSystem.hpp
 * Author:	Evan Wilde		<etcwilde@uvic.ca>
 * Date:	Mar 12 2015
 */

#ifndef IMPLICIT_SYSTEM_HPP
#define IMPLICIT_SYSTEM_HPP

/**
 * \brief Implicit objects
 *
 * All non-explicitly defined shapes.
 *
 * Implicit objects are geometry defined by math rather than explicit vertex,
 * edge, and face data.
 */
namespace Implicit {};

#include "ImplicitObject.hpp"
#include "ImplicitPrimitive.hpp"
#include "ImplicitBlend.hpp"

#endif //IMPLICIT_SYSTEM_HPP
