/**
 * @file OrbitalState_test.cpp
 * @brief Unit tests for the OrbitalState class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-08-01
 */

#include "OrbitalState.hpp"
#include "KeplerOrbit.hpp"
#include "Constants.hpp"

#include "UnitTest.hpp"

namespace gravitree
{

UNITTEST(OrbtialState, trueAnomally)
{
  KeplerOrbit orbit(1e10, 0.5, 0.7, 1.1, 2.1, 1e12);

  OrbitalState state(orbit, 0.3);

  testEqual(state.trueAnomally(), 0.3);
}

UNITTEST(OrbtialState, zeroAnomally)
{
  KeplerOrbit orbit(1e10, 0.5, 0.7, 1.1, 2.1, 1e12);

  OrbitalState state(orbit, 0.0);

  testEqual(state.trueAnomally(), 0.0);
  testEqual(state.meanAnomally(), 0.0);
  testEqual(state.eccentricAnomally(), 0.0);
  testEqual(state.time(), 0.0);
  testEqual(state.distance(), orbit.periapsis());
}

UNITTEST(OrbtialState, piAnomally)
{
  KeplerOrbit orbit(1e10, 0.5, 0.7, 1.1, 2.1, 1e12);

  OrbitalState state(orbit, Constants::PI);

  testEqual(state.trueAnomally(), Constants::PI);
  testEqual(state.meanAnomally(), Constants::PI);
  testEqual(state.eccentricAnomally(), Constants::PI);
  testEqual(state.time(), orbit.period()*0.5);
  testEqual(state.distance(), orbit.apoapsis());
}

#if 0
UNITTEST(OrbtialState, position)
{
}

UNITTEST(OrbtialState, velocity)
{
}

UNITTEST(OrbtialState, distance)
{
}
#endif

}
