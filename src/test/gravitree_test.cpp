/**
* @file gravitree_test.cpp
* @brief Unit tests for the gravitree.hpp header.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-04
*/

#include "gravitree.hpp"
#include "UnitTest.hpp"

UNITTEST(gravitree, usage)
{
  // all of the classes are tested in their respective unit tests, so this
  // test is to ensure everything complies fine and using the 'gravitree.hpp'
  // include works
  gt::Body sun(1337, 1.9885e30);

  gt::SolarSystem system(sun);

  gt::Body earth(3, 5.97237e24);
  system.addBody(
      earth,
      gt::Vector3D(0, 1.47095e11, 0),
      gt::Vector3D(3.029e4, 0, 0),
      1337);

  gt::Body moon(432, 7.342e22);
  system.addBody(
      moon,
      gt::Vector3D(-3.626e8, 0, 0),
      gt::Vector3D(0, -1.022e3, 0),
      3);

  gt::Body mars(8731, 6.4171e23);
  system.addBody(
      mars,
      gt::Vector3D(2.067e11, 0, 0),
      gt::Vector3D(0, -2.650e4, 0),
      1337);

  std::vector<std::pair<gt::Body const *, gt::Vector3D>> list = \
      system.getRelativeTo(1337);

  testEqual(list.size(), 4U);
}
