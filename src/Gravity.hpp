/**
* @file Gravity.hpp
* @brief The Gravity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-21
*/



#ifndef ORBITREE_GRAVITY_HPP
#define ORBITREE_GRAVITY_HPP


#include "Body.hpp"


namespace gravitree
{

class Gravity
{
  public:
    /**
    * @brief The gravitational constant (in meters^3 / kg s^2).
    */
    static constexpr double const G = 6.67408e-11;

    /**
    * @brief Calculate the acceleration of body of negligable mass towards a
    * body of large mass.
    *
    * @param mass The mass of the large body.
    * @param distance The distance of the small body from the large body.
    *
    * @return The acceleration (meters / second^2).
    */
    inline static mps2_type acceleration(
        kilo_type const mass,
        meter_type const distance) noexcept
    {
      return force(1.0, mass, distance);
    }

    /**
    * @brief Calculate the acceleration magnitude and direction of a neglibale
    * mass towards a large mass.
    *
    * @param mass The large mass.
    * @param offset The offset of the large mass.
    *
    * @return The acceleration in each dimension.
    */
    inline static Vector3D acceleration(
        kilo_type const mass,
        Vector3D const offset)
    {
      return force(1.0, mass, offset);
    }

    /**
    * @brief Get the force between two bodies.
    *
    * @param mass1 The mass of the first body.
    * @param mass2 The mass of the second body.
    * @param distance The distance between the center of mass of the two
    * bodies.
    *
    * @return The force of attraction between the two bodies.
    */
    inline static newton_type force(
        kilo_type mass1,
        kilo_type mass2,
        meter_type distance) noexcept
    {
      return (G*mass1*mass2) / (distance*distance);
    }

    /**
    * @brief Calculate the directional force between two bodies.
    *
    * @param mass1 The first mass.
    * @param mass2 The second mass.
    * @param offset The offset of the two masses.
    *
    * @return The force.
    */
    inline static Vector3D force(
        kilo_type const mass1,
        kilo_type const mass2,
        Vector3D const offset) noexcept
    {
      return -offset.normalized() * ((G*mass1*mass2) / offset.magnitude2());
    }
};

}

#endif
