/**
* @file OrbitalState.hpp
* @brief The OrbitalState class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-04-03
*/



#ifndef GRAVITREE_ORBITALSTATE_HPP
#define GRAVITREE_ORBITALSTATE_HPP

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
    * @brief Set the time passed since the epoch.
    *
    * @param time The time in seconds.
    */
    void setTime(
        second_type time) noexcept;

    /**
    * @brief Get the components of the velocity of this object relative to the
    * body it orbits.
    *
    * @return The velocity components.
    */
    Vector3D velocity() const noexcept;

    /**
    * @brief Get the position of this object relative to the body it orbits.
    *
    * @return The position.
    */
    Vector3D position() const noexcept;

    /**
    * @brief The distance of the this object from the body it orbits.
    *
    * @return The distance in meters.
    */
    meter_type distance() const noexcept;

    /**
    * @brief The current true anomally.
    *
    * @return The true anomally.
    */
    radian_type trueAnomally() const noexcept;

    /**
    * @brief The current mean anomally.
    *
    * @return The mean anomally.
    */
    radian_type meanAnomally() const noexcept;

    /**
    * @brief The current eccentric anomally.
    *
    * @return The current eccentric anomally.
    */
    radian_type eccentricAnomally() const noexcept;

    /**
    * @brief The time passed since the epoch (in seconds).
    *
    * @return The number of seconds.
    */
    second_type time() const noexcept;

  private:
    KeplerOrbit m_orbit;
    radian_type m_trueAnomally;
    radian_type m_eccentricAnomally;
    radian_type m_meanAnomally;
    second_type m_time;
};

}

#endif
