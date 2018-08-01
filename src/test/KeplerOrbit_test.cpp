/**
* @file KeplerOrbit_test.cpp
* @brief Unit tests for the KeplerOrbit class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-26
*/

#include "KeplerOrbit.hpp"
#include "Gravity.hpp"
#include "Constants.hpp"
#include "UnitTest.hpp"

#include <cmath>

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
  KeplerOrbit orbit(1e10, 0.5, 0.7, 1.1, 2.1, 1e12);

  testEqual(orbit.semimajorAxis(), 1e10);
  testEqual(orbit.eccentricity(), 0.5);
  testEqual(orbit.inclination(), 0.7);
  testEqual(orbit.longitudeOfAscendingNode(), 1.1);
  testEqual(orbit.argumentOfPeriapsis(), 2.1);
  testEqual(orbit.parentMass(), 1e12);
  testEqual(orbit.period(), \
      2.0*Constants::PI*std::sqrt((1e10*1e10*1e10)/(Gravity::G*1e12)));
}

UNITTEST(KeplerOrbit, periapsisTest)
{
  KeplerOrbit orbit(1.496e11, 0.01671022, deg2rad(7.155),
      deg2rad(-11.26064), 0.0, 1.98847e30);
  
  testNearEqual(orbit.periapsis(), 1.47095e11, 1e-3, 1e-2);
}


UNITTEST(KeplerOrbit, apoapsisTest)
{
  KeplerOrbit orbit(1.496e11, 0.01671022, deg2rad(7.155),
      deg2rad(-11.26064), 0.0, 1.98847e30);
  
  testNearEqual(orbit.apoapsis(), 1.521e11, 1e-3, 1e-2);
}

UNITTEST(KeplerOrbit, angularMomentum)
{
  KeplerOrbit orbit(1.496e11, 0.01671022, deg2rad(7.155),
      deg2rad(-11.26064), 0.0, 1.98847e30);

  double const h = std::sqrt(orbit.mu() * orbit.semimajorAxis() * \
      (1.0 - orbit.eccentricity()*orbit.eccentricity()));
  testNearEqual(orbit.angularMomentum(), h, 1e-3, 1e-2);
}


}

