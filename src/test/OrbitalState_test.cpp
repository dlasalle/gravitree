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

constexpr double deg2rad(double const d)
{
  return Constants::PI * d / 180.0;
}

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

UNITTEST(OrbitalState, earthFromElements)
{
  KeplerOrbit orbit(1.496e11, 0.0167, deg2rad(7.155), deg2rad(-11.26064),
      deg2rad(114.20783), 1.9885e30);
  OrbitalState state(orbit, 0);

  testNearEqual(state.orbit().periapsis(), 1.47095e11, 1.0e-3, 1.0);
  testNearEqual(state.orbit().apoapsis(), 1.521e11, 1.0e-3, 1.0);
  testNearEqual(state.orbit().period(), 365.25*24*60*60, 1.0e-3, 1.0e-2);
}

UNITTEST(OrbitalState, fromVectorsPerihelion)
{
  Vector3D pos(0, 1.47095e11, 0);
  Vector3D vel(3.029e4, 0, 0);

  OrbitalState state = OrbitalState::fromVectors(pos, vel, 1.9885e30);

  testNearEqual(state.trueAnomally(), 0.0, 1.0e-3, 1.0e-5);

  testNearEqual(state.orbit().periapsis(), 1.47095e11, 1.0e-3, 1.0);
  testNearEqual(state.orbit().apoapsis(), 1.521e11, 1.0e-3, 1.0);
  testNearEqual(state.orbit().period(), 365.25*24*60*60, 1.0e-3, 1.0e-2);

  testNearEqual(state.orbit().eccentricity(), 0.01671, 1.0e-3, 1.0e-5);

  testNearEqual(state.position().magnitude(), 1.47095e11, 1.0e-3, 1.0);
  testNearEqual(state.velocity().magnitude(), 3.029e4, 1.0e-3, 1.0);
}

UNITTEST(OrbitalState, fromVectorsAphelion)
{
  Vector3D pos(0, 1.1521e11, 0);
  Vector3D vel(2.929e4, 0, 0);

  OrbitalState state = OrbitalState::fromVectors(pos, vel, 1.9885e30);

  testNearEqual(state.trueAnomally(), Constants::PI, 1.0e-3, 1.0e-5);

  testNearEqual(state.orbit().periapsis(), 1.47095e11, 1.0e-3, 1.0);
  testNearEqual(state.orbit().apoapsis(), 1.521e11, 1.0e-3, 1.0);
  testNearEqual(state.orbit().period(), 365.25*24*60*60, 1.0e-3, 1.0e-2);

  testNearEqual(state.orbit().eccentricity(), 0.01671, 1.0e-3, 1.0e-5);

  testNearEqual(state.position().magnitude(), 1.47095e11, 1.0e-3, 1.0);
  testNearEqual(state.velocity().magnitude(), 3.029e4, 1.0e-3, 1.0);
}

UNITTEST(OrbtialState, position)
{
  KeplerOrbit orbit(1.496e11, 0.0167, deg2rad(7.155), deg2rad(-11.26064),
      deg2rad(114.20783), 1.9885e30);
  OrbitalState state(orbit, 0);

  testNearEqual(state.position().magnitude(), state.distance(), 1.0e-3, 1.0);
  testNearEqual(state.position().magnitude(), 1.47095e11, 1.0e-3, 1.0);

  state.setTime(182.625*24*60*60);

  testNearEqual(state.position().magnitude(), 1.521e11, 1.0e-3, 1.0);
}

UNITTEST(OrbtialState, velocity)
{
  KeplerOrbit orbit(1.496e11, 0.0167, deg2rad(7.155), deg2rad(-11.26064),
      deg2rad(114.20783), 1.9885e30);
  OrbitalState state(orbit, 0);

  testNearEqual(state.velocity().magnitude(), 3.029e4, 1.0e-3, 1.0);
}

UNITTEST(OrbtialState, distance)
{
  Vector3D pos(1.5e3, 2.3e2, 7.3e7);
  Vector3D vel(9.5e3, 0.0, 0.0);
  OrbitalState state = OrbitalState::fromVectors(pos, vel, 1.3e14);

  testNearEqual(state.distance(), pos.magnitude(), 1.0e-3, 1.0);
}

}
