/**
* @file Output.cpp
* @brief Implementation of the output operators.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-29
*/


#include "Output.hpp"

namespace gravitree
{

std::ostream& operator<<(
    std::ostream& os,
    Vector3D const vec)
{
  os << "Vector3D{" << vec.x() << " " << vec.y() << " " << vec.z() << "}";
  return os;
}

std::ostream& operator<<(
    std::ostream& os,
    Rotation const rot)
{
  os << "Rotation{" << rot.axis() << "," << rot.angle() << "}";
  return os;
}

}
