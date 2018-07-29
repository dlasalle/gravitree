/**
* @file Body_test.cpp
* @brief Unit tests for the Body class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-26
*/


#include "Body.hpp"
#include "Output.hpp"
#include "UnitTest.hpp"


namespace gravitree
{

UNITTEST(Body, mass)
{
  Body b(10.0);

  testEqual(b.mass(), 10.0);
}

UNITTEST(Body, angularVelocity)
{
  Body b(10.0);

  testEqual(b.angularVelocity(), Rotation());
}

UNITTEST(Body, linearVelocity)
{
  Body b(10.0);

  testEqual(b.linearVelocity(), Vector3D(0.0, 0.0, 0.0));
}

}

