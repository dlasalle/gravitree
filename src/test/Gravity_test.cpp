/**
* @file Gravity_test.cpp
* @brief Unit tests for the Gravity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-21
*/


#include "Gravity.hpp"
#include "UnitTest.hpp"

namespace gravitree
{


UNITTEST(Gravity, acceleration)
{
  // earths equitorial gravity
  testNearEqual(Gravity::acceleration(5.9722e24, 6.3781e6), 9.79812, 1e-6, 1e-9);
}

UNITTEST(Gravity, force)
{
  // earths equitorial gravity
  testNearEqual(Gravity::force(5.9722e24, 7.342e22, 3.84399e11), 1.9805e14, 1e-6, 1e-9);
}

}
