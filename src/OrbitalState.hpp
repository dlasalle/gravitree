/**
* @file OrbitalState.hpp
* @brief The OrbitalState class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-04-03
*/



#ifndef ORBITREE_ORBITALSTATE_HPP
#define ORBITREE_ORBITALSTATE_HPP

#include "KeplerOrbit.hpp"

namespace gravitree
{

class OrbitalState
{
  public:
    /**
    * @brief Create a new orbital state.
    *
    * @param orbit The current orbit.
    * @param trueAnomally The current true anomally.
    */
    OrbitalState(
        KeplerOrbit orbit,
        radian_type trueAnomally);

    /**
    * @brief Destructor.
    */
    ~OrbitalState();

    /**
    * @brief Get the components of the velocity of this object.
    *
    * @return The velocity components.
    */
    Vector3D velocity() const noexcept;

    /**
    * @brief Get the angle between the tangent of the velocity and the focal
    * point of the orbit.
    *
    * @return The tangent angle.
    */
    radian_type tangent() const noexcept;

    /**
    * @brief The distance of the orbit from the focal point in meters.
    *
    * @return The altitude.
    */
    meter_type altitude() const noexcept;

  private:
    KeplerOrbit m_orbit;
    radian_type m_trueAnomally;
};

}

#endif
