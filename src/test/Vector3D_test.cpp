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
#include "Output.hpp"


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

UNITTEST(Vector3D, dotSelf)
{
  Vector3D const v(1.0, 2.0, 3.0);
  double const mag2 = v*v;
  testEqual(v.magnitude2(), mag2);
}


UNITTEST(Vector3D, dotOther)
{
  Vector3D const v(1.0, 2.0, 3.0);
  Vector3D const u(3.0, 2.0, 1.0);
  double const dot = v*u;

  testEqual(10.0, dot);
}

UNITTEST(Vector3D, crossSelf)
{
  Vector3D const v(1.0, 2.0, 3.0);
  Vector3D const cross = v.cross(v);

  Vector3D const u(0.0, 0.0, 0.0);

  testEqual(u, cross);
}


UNITTEST(Vector3D, crossRight)
{
  Vector3D const v(2.0, 0.0, 0.0);
  Vector3D const u(0.0, 1.5, 0.0);
  Vector3D const cross = v.cross(u);

  Vector3D const w(0.0, 0.0, 3.0);

  testEqual(w, cross);
}

UNITTEST(Vector3D, crossOther)
{
  Vector3D const v(3.0, -3.0, 1.0);
  Vector3D const u(4.0, 9.0, 2.0);
  Vector3D const cross = v.cross(u);

  Vector3D const w(-15.0, -2.0, 39.0);

  testEqual(w, cross);
}

UNITTEST(Vector3D, crossOtherOpposite)
{
  Vector3D const v(3.0, -3.0, 1.0);
  Vector3D const u(4.0, 9.0, 2.0);
  Vector3D const cross = u.cross(v);

  Vector3D const w(15.0, 2.0, -39.0);

  testEqual(w, cross);
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
