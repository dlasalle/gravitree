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
  Body b("test", 10.0);

  testEqual(b.mass(), 10.0);
}

UNITTEST(Body, name)
{
  Body b("test", 10.0);

  testEqual(b.name(), "test");
}

UNITTEST(Body, angularVelocity)
{
  Body b("test", 10.0);

  testEqual(b.angularVelocity(), Rotation());
}



}

