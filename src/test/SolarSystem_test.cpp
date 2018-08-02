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

  Body mars("mars", 6.4171e23);
  system.addBody(
      mars,
      Vector3D(2.067e11, 0, 0),
      Vector3D(0, -2.650e4, 0),
      "sun");

  std::vector<std::pair<Body const *, Vector3D>> list = \
      system.getSystemRelativeTo("sun");

  testEqual(list.size(), 3U);

  for (const std::pair<Body const *, Vector3D>& pair : list) {
    if (pair.first->name() == "sun") {
      testEqual(pair.first->mass(), 1.9885e30);
      testEqual(pair.second.x(), 0.0);
      testEqual(pair.second.y(), 0.0);
      testEqual(pair.second.z(), 0.0);
    } else if (pair.first->name() == "earth") {
      testEqual(pair.first->mass(), 5.97237e24);
      testEqual(pair.second.x(), 0.0);
      testEqual(pair.second.y(), 1.47095e11);
      testEqual(pair.second.z(), 0.0);
    } else if (pair.first->name() == "mars") {
      testEqual(pair.first->mass(), 6.4171e23);
      testEqual(pair.second.x(), 2.067e11);
      testEqual(pair.second.y(), 0.0);
      testEqual(pair.second.z(), 0.0);
    } else {
      testFail() << "Unknown object: " << pair.first->name();
    }
  }
}



}

