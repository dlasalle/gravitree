/**
* @file KeplerOrbit.hpp
* @brief The KeplerOrbit class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-22
*/



#ifndef ORBITREE_KEPLERORBIT_HPP
#define ORBITREE_KEPLERORBIT_HPP

#include "Types.hpp"


namespace gravitree
{

class KeplerOrbit
{
  public:
    /**
    * @brief Create a new keplerian orbit.
    *
    * @param semimajorAxis The semi-major axis (a).
    * @param eccentricity The eccentricity (e).
    * @param inclination The inclination (i).
    * @param longitudeOfAscendingNode The position of the ascending node
    * (omega).
    * @param argumentOfPeriapsis The argument of periapsis (w).
    * @param period The period of the orbit.
    */
    KeplerOrbit(
        meter_type semimajorAxis,
        double eccentricity,
        radian_type inclination,
        radian_type longitudeOfAscendingNode,
        radian_type argumentOfPeriapsis,
        second_type period);

    /**
    * @brief Get the length of the semimajor axis.
    *
    * @return The length of the semi major axis in meters.
    */
    meter_type semimajorAxis() const;

    /**
    * @brief Get the eccentricity of the orbit.
    *
    * @return The eccentricity.
    */
    double eccentricity() const;

    /**
    * @brief Get the inclination of the orbit.
    *
    * @return The inclination in radians.
    */
    radian_type inclination() const;

    /**
    * @brief Get the longitude of the ascending node as measured from the
    * reference direction.
    *
    * @return The longitude in radians.
    */
    radian_type longitudeOfAscendingNode() const;

    /**
    * @brief Get the argument of periapsis.
    *
    * @return The argument of periapsis in radians.
    */
    radian_type argumentOfPeriapsis() const;

    /**
    * @brief Get the period of the orbit.
    *
    * @return The period in seconds.
    */
    second_type period() const;

    /**
    * @brief Get the distance of the apoapsis from the focal point.
    *
    * @return The distance in meters.
    */
    meter_type apoapsis() const;

    /**
    * @brief Get the distance of the apoapsis from the focal point.
    *
    * @return The distance in meters.
    */
    meter_type periapsis() const;

    /**
    * @brief Get the angle between the tangent of the velocity and the focal
    * point of the orbit.
    *
    * @param trueAnomally The true anomally.
    *
    * @return The tangent angle.
    */
    radian_type tangent(
        radian_type trueAnomally) const;

    /**
    * @brief Get the distance from the focal point at the given position.
    *
    * @param trueAnomally The true anomally of the position in radians.
    *
    * @return The distance in meters.
    */
    meter_type altitude(
        radian_type trueAnomally) const;

    /**
    * @brief Get the velocity of the orbit at a given position.
    *
    * @param trueAnomally The true anomally of the position.
    *
    * @return The velocity in meters per second.
    */
    mps_type velocity(
        radian_type trueAnomally) const;

  private:
    meter_type m_semimajorAxis;
    double m_eccentricity;
    radian_type m_inclination;
    radian_type m_longitudeOfAscendingNode;
    radian_type m_argumentOfPeriapsis;
    second_type m_period;
};

}

#endif
