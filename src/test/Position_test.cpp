/**
* @file Position_test.cpp
* @brief Unit tests for the Position class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-20
*/


#include "Position.hpp"
#include "UnitTest.hpp"


namespace gravitree
{


UNITTEST(Position, toVector)
{
  Vector3D v(1.0, 2.0, 3.0);
  Position p(v);
  Vector3D u = p.toVector();

  testEqual(u.x(), v.x());
  testEqual(u.y(), v.y());
  testEqual(u.z(), v.z());
}

UNITTEST(Position, sum)
{
  Position p(1.0e10, 1.0e10, 0.0);
  Vector3D v(1e9, 0, 0);

  p += v;

  testEqual(p.x(), 1.1e10);
  testEqual(p.y(), 1.0e10);
  testEqual(p.z(), 0.0);
}

UNITTEST(Position, difference)
{
  Position p1(1.0e10, 1.0e10, 0.0);
  Position p2(1.0e10, -1.0e10, 100.0);

  Vector3D distance = p1 - p2;

  testNearEqual(distance.x(), 0.0, 1.0e-9, 1.0e-7);
  testNearEqual(distance.y(), 2.0e10, 1.0e-9, 1.0e-7);
  testNearEqual(distance.z(), -100.0, 1.0e-9, 1.0e-7);
}

}
