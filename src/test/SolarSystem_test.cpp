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
  Body sun("sun", 1.9885e30);

  SolarSystem system(sun);

  Body earth("earth", 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      "sun");

  Body moon("moon", 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      "earth");

  Body mars("mars", 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      "sun");

  std::vector<std::pair<Body const *, Vector3D>> list = \
      system.getRelativeTo("sun");

  testEqual(list.size(), 4U);

  for (const std::pair<Body const *, Vector3D>& pair : list) {
    if (pair.first->name() == "sun") {
      testEqual(pair.first->mass(), 1.9885e30);
      testEqual(pair.second.x(), 0.0);
      testEqual(pair.second.y(), 0.0);
      testEqual(pair.second.z(), 0.0);
    } else if (pair.first->name() == "earth") {
      testEqual(pair.first->mass(), 5.97237e24);
      testNearEqual(pair.second.x(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->name() == "moon") {
      testEqual(pair.first->mass(), 7.342e22);
      testNearEqual(pair.second.x(), -3.626e8, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->name() == "mars") {
      testEqual(pair.first->mass(), 6.4171e23);
      testNearEqual(pair.second.x(), 2.067e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else {
      testFail() << "Unknown object: " << pair.first->name();
    }
  }
}

UNITTEST(SolarSystem, GetSystemRelativeToEarth)
{
  Body sun("sun", 1.9885e30);

  SolarSystem system(sun);

  Body earth("earth", 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      "sun");

  Body moon("moon", 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      "earth");

  Body mars("mars", 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      "sun");

  Body phobos("phobos", 1.0659e16);
  system.addBody(
      phobos,
      Vector3D(9.51758e6, 0, 0),
      Vector3D(0, -2.138e3, 0),
      "mars");


  std::vector<std::pair<Body const *, Vector3D>> list = \
      system.getRelativeTo("earth");

  testEqual(list.size(), 5U);

  for (const std::pair<Body const *, Vector3D>& pair : list) {
    if (pair.first->name() == "sun") {
      testEqual(pair.first->mass(), 1.9885e30);
      testNearEqual(pair.second.x(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->name() == "earth") {
      testEqual(pair.first->mass(), 5.97237e24);
      testEqual(pair.second.x(), 0.0);
      testEqual(pair.second.y(), 0.0);
      testEqual(pair.second.z(), 0.0);
    } else if (pair.first->name() == "moon") {
      testEqual(pair.first->mass(), 7.342e22);
      testNearEqual(pair.second.x(), -3.626e8, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->name() == "mars") {
      testEqual(pair.first->mass(), 6.4171e23);
      testNearEqual(pair.second.x(), 2.067e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->name() == "phobos") {
      testEqual(pair.first->mass(), 1.0659e16);
      testNearEqual(pair.second.x(), 2.0670951758e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else {
      testFail() << "Unknown object: " << pair.first->name();
    }
  }
}

UNITTEST(SolarSystem, GetSystemRelativeToMoon)
{
  Body sun("sun", 1.9885e30);

  SolarSystem system(sun);

  Body earth("earth", 5.97237e24);
  system.addBody(
      earth,
      Vector3D(0, 1.47095e11, 0),
      Vector3D(3.029e4, 0, 0),
      "sun");

  Body moon("moon", 7.342e22);
  system.addBody(
      moon,
      Vector3D(-3.626e8, 0, 0),
      Vector3D(0, -1.022e3, 0),
      "earth");

  Body mars("mars", 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      "sun");

  std::vector<std::pair<Body const *, Vector3D>> list = \
      system.getRelativeTo("moon");

  testEqual(list.size(), 4U);

  for (const std::pair<Body const *, Vector3D>& pair : list) {
    if (pair.first->name() == "sun") {
      testEqual(pair.first->mass(), 1.9885e30);
      testNearEqual(pair.second.x(), 3.626e8, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->name() == "earth") {
      testEqual(pair.first->mass(), 5.97237e24);
      testNearEqual(pair.second.x(), 3.626e8, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), 0.0, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else if (pair.first->name() == "moon") {
      testEqual(pair.first->mass(), 7.342e22);
      testEqual(pair.second.x(), 0.0);
      testEqual(pair.second.y(), 0.0);
      testEqual(pair.second.z(), 0.0);
    } else if (pair.first->name() == "mars") {
      testEqual(pair.first->mass(), 6.4171e23);
      testNearEqual(pair.second.x(), 2.070626e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.y(), -1.47095e11, 1.0e-3, 1.0);
      testNearEqual(pair.second.z(), 0.0, 1.0e-3, 1.0);
    } else {
      testFail() << "Unknown object: " << pair.first->name();
    }
  }
}

}



