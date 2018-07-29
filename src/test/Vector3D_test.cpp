/**
* @file VectorMath_test.cpp
* @brief Unit tests for the Vector3D class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-20
*/



#include "Vector3D.hpp"
#include "UnitTest.hpp"


namespace gravitree
{


UNITTEST(Vector3D, components)
{
  Vector3D v(1.0, 2.0, 3.0);

  testEqual(v.x(), 1.0);
  testEqual(v.y(), 2.0);
  testEqual(v.z(), 3.0);
}


UNITTEST(Vector3D, toPolarCoordinates)
{
  Vector3D v(5.0, 0.0, 0.0);

  Vector3D s = v.toPolarCoordinates();

  testEqual(s.x(), 0.0);
  testEqual(s.y(), 0.0);
  testEqual(s.z(), 5.0);
}

UNITTEST(Vector3D, distance)
{
  Vector3D v(5.0, 0.0, 0.0);
  Vector3D u(0.0, 5.0, 0.0);

  double const dist = v.distance(u);

  testEqual(dist, u.distance(v));
  testEqual(dist, std::sqrt(5.0*5.0 + 5.0*5.0));
}

UNITTEST(Vector3D, add)
{
  Vector3D v(5.0, 0.0, 0.0);
  Vector3D u(0.0, 5.0, 0.0);

  Vector3D w = v + u;

  testEqual(w.x(), 5.0);
  testEqual(w.y(), 5.0);
  testEqual(w.z(), 0.0);
}

UNITTEST(Vector3D, subtract)
{
  Vector3D v(5.0, 0.0, 0.0);
  Vector3D u(0.0, 5.0, 0.0);

  Vector3D w = v - u;

  testEqual(w.x(), 5.0);
  testEqual(w.y(), -5.0);
  testEqual(w.z(), 0.0);
}

UNITTEST(Vector3D, magnitude)
{
  Vector3D v(0.0, 0.0, 5.0);

  testEqual(v.magnitude(), 5.0);
}

UNITTEST(Vector3D, scale)
{
  Vector3D v(1.0, 2.0, 3.0);

  v *= 2.0;

  testEqual(v.x(), 1.0*2.0);
  testEqual(v.y(), 2.0*2.0);
  testEqual(v.z(), 3.0*2.0);
}

}
