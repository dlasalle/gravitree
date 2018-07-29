/**
* @file KeplerOrbit_test.cpp
* @brief Unit tests for the KeplerOrbit class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-26
*/

#include "KeplerOrbit.hpp"
#include "Constants.hpp"
#include "UnitTest.hpp"

namespace gravitree
{

namespace
{

constexpr double deg2rad(
    double const deg)
{
  return deg * Constants::PI / 180.0;
}

}

UNITTEST(KeplerOrbit, gettersTest)
{
  KeplerOrbit orbit(1e10, 0.5, 0.7, 1.1, 2.1, 1e8);

  testEqual(orbit.semimajorAxis(), 1e10);
  testEqual(orbit.eccentricity(), 0.5);
  testEqual(orbit.inclination(), 0.7);
  testEqual(orbit.longitudeOfAscendingNode(), 1.1);
  testEqual(orbit.argumentOfPeriapsis(), 2.1);
  testEqual(orbit.period(), 1e8);
}

UNITTEST(KeplerOrbit, velocityCircularTest)
{
  KeplerOrbit orbit(1e6, 0.0, 0.0, 0.0, 0.0, 1.0e8);
  
  double const length = 2.0 * Constants::PI * 1.0e6;
  double const velocity = length / 1.0e8;

  for (int i = 0; i < 256; ++i) {
    double const trueAnomally = i*Constants::PI/128.0;
    testNearEqual(velocity, orbit.velocity(trueAnomally), 1.0e-6, 0.0); 
  }
}

UNITTEST(KeplerOrbit, velocityEarthTest)
{
  KeplerOrbit orbit(1.496e11, 0.01671022, deg2rad(7.155),
      deg2rad(-11.26064), 0.0,
      31558149.763545603);
  
  // test earth min, max, and average velocities
  mps_type vel = 0.0;
  for (int i = 0; i < 256; ++i) {
    double const curVel = orbit.velocity((i/128.0)*Constants::PI);
    testLess(curVel, 30290);
    testGreater(curVel, 29290);
    vel += curVel;
  }
  vel /= 256;

  testNearEqual(vel, 29780, 1e-3, 1e-2);
}




}

