/**
* @file SolarSystem_test.cpp
* @brief Unit tests for the SolarSystem class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-01
*/


#include "SolarSystem.hpp"
#include "UnitTest.hpp"


namespace gravitree
{

UNITTEST(SolarSystem, GetSystemRelativeToSun)
{
  Body sun(0, 1.9885e30);

  SolarSystem system(sun);

  Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      0);

  Body moon(31, 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      3);

  Body mars(4, 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      0);

  std::vector<std::pair<Body const *, Vector3D>> list = \
      system.getRelativeTo(0);

  testEqual(list.size(), 4U);

  for (const std::pair<Body const *, Vector3D>& pair : list) {
    if (pair.first->id() == 0) {
      testEqual(pair.first->mass(), 1.9885e30);
      testEqual(pair.second.x(), 0.0);
      testEqual(pair.second.y(), 0.0);
      testEqual(pair.second.z(), 0.0);
    } else if (pair.first->id() == 3) {
      testEqual(pair.first->mass(), 5.97237e24);
      testNearEqual(pair.second.x(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->id() == 31) {
      testEqual(pair.first->mass(), 7.342e22);
      testNearEqual(pair.second.x(), -3.626e8, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->id() == 4) {
      testEqual(pair.first->mass(), 6.4171e23);
      testNearEqual(pair.second.x(), 2.067e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else {
      testFail() << "Unknown object: " << pair.first->id();
    }
  }
}

UNITTEST(SolarSystem, GetSystemRelativeToEarth)
{
  Body sun(0, 1.9885e30);

  SolarSystem system(sun);

  Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      0);

  Body moon(31, 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      3);

  Body mars(4, 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      0);

  Body phobos(41, 1.0659e16);
  system.addBody(
      phobos,
      Vector3D(9.51758e6, 0, 0),
      Vector3D(0, -2.138e3, 0),
      4);


  std::vector<std::pair<Body const *, Vector3D>> list = \
      system.getRelativeTo(3);

  testEqual(list.size(), 5U);

  for (const std::pair<Body const *, Vector3D>& pair : list) {
    if (pair.first->id() == 0) {
      testEqual(pair.first->mass(), 1.9885e30);
      testNearEqual(pair.second.x(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->id() == 3) {
      testEqual(pair.first->mass(), 5.97237e24);
      testEqual(pair.second.x(), 0.0);
      testEqual(pair.second.y(), 0.0);
      testEqual(pair.second.z(), 0.0);
    } else if (pair.first->id() == 31) {
      testEqual(pair.first->mass(), 7.342e22);
      testNearEqual(pair.second.x(), -3.626e8, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->id() == 4) {
      testEqual(pair.first->mass(), 6.4171e23);
      testNearEqual(pair.second.x(), 2.067e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->id() == 41) {
      testEqual(pair.first->mass(), 1.0659e16);
      testNearEqual(pair.second.x(), 2.0670951758e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else {
      testFail() << "Unknown object: " << pair.first->id();
    }
  }
}

UNITTEST(SolarSystem, GetSystemRelativeToMoon)
{
  Body sun(0, 1.9885e30);

  SolarSystem system(sun);

  Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      0);

  Body moon(31, 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      3);

  Body mars(4, 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      0);

  std::vector<std::pair<Body const *, Vector3D>> list = \
      system.getRelativeTo(31);

  testEqual(list.size(), 4U);

  for (const std::pair<Body const *, Vector3D>& pair : list) {
    if (pair.first->id() == 0) {
      testEqual(pair.first->mass(), 1.9885e30);
      testNearEqual(pair.second.x(), 3.626e8, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->id() == 3) {
      testEqual(pair.first->mass(), 5.97237e24);
      testNearEqual(pair.second.x(), 3.626e8, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->id() == 31) {
      testEqual(pair.first->mass(), 7.342e22);
      testEqual(pair.second.x(), 0.0);
      testEqual(pair.second.y(), 0.0);
      testEqual(pair.second.z(), 0.0);
    } else if (pair.first->id() == 4) {
      testEqual(pair.first->mass(), 6.4171e23);
      testNearEqual(pair.second.x(), 2.070626e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else {
      testFail() << "Unknown object: " << pair.first->id();
    }
  }
}

UNITTEST(SolarSystem, GetBody)
{
  Body sun(0, 1.9885e30);

  SolarSystem system(sun);

  Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      0);

  Body moon(31, 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      3);

  Body mars(4, 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      0);

  testEqual(system.getBody(0)->id(), 0UL);
  testEqual(system.getBody(0)->mass(), 1.9885e30);

  testEqual(system.getBody(3)->id(), 3UL);
  testEqual(system.getBody(3)->mass(), 5.97237e24);

  testEqual(system.getBody(31)->id(), 31UL);
  testEqual(system.getBody(31)->mass(), 7.342e22);

  testEqual(system.getBody(4)->id(), 4UL);
  testEqual(system.getBody(4)->mass(), 6.4171e23);
}

UNITTEST(SolarSystem, GetPositionEarthRelativeToSun)
{
  Body sun(0, 1.9885e30);

  SolarSystem system(sun);

  Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      0);

  Body moon(31, 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      3);

  Body mars(4, 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      0);

  Vector3D pos = system.getBodyPositionRelativeTo(3, 0);

  testNearEqual(pos.x(), 0.0, 1.0e-9, 1.0);
  testNearEqual(pos.y(), 1.47095e11, 1.0e-9, 1.0);
  testNearEqual(pos.z(), 0.0, 1.0e-9, 1.0);
}

UNITTEST(SolarSystem, GetPositionSunRelativeToEarth)
{
  Body sun(0, 1.9885e30);

  SolarSystem system(sun);

  Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      0);

  Body moon(31, 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      3);

  Body mars(4, 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      0);

  Vector3D pos = system.getBodyPositionRelativeTo(0, 3);

  testNearEqual(pos.x(), 0.0, 1.0e-9, 1.0);
  testNearEqual(pos.y(), -1.47095e11, 1.0e-9, 1.0);
  testNearEqual(pos.z(), 0.0, 1.0e-9, 1.0);
}

UNITTEST(SolarSystem, GetPositionMarsRelativeToEarth)
{
  Body sun(0, 1.9885e30);

  SolarSystem system(sun);

  Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      0);

  Body mars(4, 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      0);

  Vector3D pos = system.getBodyPositionRelativeTo(4, 3);

  testNearEqual(pos.x(), 2.067e11, 1.0e-9, 1.0);
  testNearEqual(pos.y(), -1.47095e11, 1.0e-9, 1.0);
  testNearEqual(pos.z(), 0.0, 1.0e-9, 1.0);
}

UNITTEST(SolarSystem, GetPositionMoonRelativeToEarth)
{
  Body sun(0, 1.9885e30);

  SolarSystem system(sun);

  Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      0);

  Body moon(31, 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      3);

  Vector3D pos = system.getBodyPositionRelativeTo(31, 3);

  testNearEqual(pos.x(), -3.626e8, 1.0e-9, 1.0);
  testNearEqual(pos.y(), 0.0, 1.0e-9, 1.0);
  testNearEqual(pos.z(), 0.0, 1.0e-9, 1.0);
}

UNITTEST(SolarSystem, GetPositionEarthRelativeToMoon)
{
  Body sun(0, 1.9885e30);

  SolarSystem system(sun);

  Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      0);

  Body moon(31, 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      3);

  Vector3D pos = system.getBodyPositionRelativeTo(3, 31);

  testNearEqual(pos.x(), 3.626e8, 1.0e-9, 1.0);
  testNearEqual(pos.y(), 0.0, 1.0e-9, 1.0);
  testNearEqual(pos.z(), 0.0, 1.0e-9, 1.0);
}

}
