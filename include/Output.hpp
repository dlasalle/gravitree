/**
* @file Output.hpp
* @brief Output operators.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-29
*/

#include "Vector3D.hpp"
#include "Rotation.hpp"
#include <ostream>

namespace gravitree
{

/**
* @brief Output stream operator.
*
* @param os The output stream
* @param vec The vector.
*
* @return The stream.
*/
std::ostream& operator<<(
    std::ostream& os,
    Vector3D const vec);

/**
* @brief Output stream operator.
*
* @param os The output stream
* @param rot The rotation.
*
* @return The stream.
*/
std::ostream& operator<<(
    std::ostream& os,
    Rotation const rot);

}

