/**
* @file KeplerOrbit.hpp
* @brief The KeplerOrbit class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-22
*/



#ifndef GRAVITREE_KEPLERORBIT_HPP
#define GRAVITREE_KEPLERORBIT_HPP

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
    * @param parentMass The mass of the parent body. 
    */
    KeplerOrbit(
        meter_type semimajorAxis,
        double eccentricity,
        radian_type inclination,
        radian_type longitudeOfAscendingNode,
        radian_type argumentOfPeriapsis,
        kilo_type parentMass);

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
    * @return The longitude in radians (\f$ \Omega \f$).
    */
    radian_type longitudeOfAscendingNode() const;

    /**
    * @brief Get the argument of periapsis.
    *
    * @return The argument of periapsis in radians.
    */
    radian_type argumentOfPeriapsis() const;

    /**
    * @brief Get the mass of the parent body which is being orbited..
    *
    * @return The mass in kg (M).
    */
    kilo_type parentMass() const;

    /**
    * @brief Get the period of the orbit.
    *
    * @return The period in seconds.
    */
    second_type period() const;

    /**
    * @brief Get the gravitational parameter.
    *
    * \f[
    *    \mu = GM
    * \f]
    *
    * @return The parameter.
    */
    double mu() const;

    /**
    * @brief Get the angular momentum of the orbit.
    *
    * \f[
    *    h = \sqrt{\mu a (1 - e^2)}
    * \f]
    *
    * @return The angular momentum (h).
    */
    double angularMomentum() const;

    /**
    * @brief Get the semi-latus rectum of the orbit.
    *
    * \f[
    *    p = a(1-e^2)
    * \f]
    *
    * @return The semi-latus rectum (p).
    */
    double semilatusRectum() const;

    /**
    * @brief Get the distance of the apoapsis from the focal point (the
    * furthest distance during orbit).
    *
    * When the eccentricity (\f$e\f$) of the orbit is less than one:
    *
    * \f[
    *    apoapsis = \frac{p}{1 - e}
    * \f]
    *
    * and when the eccentricity is equal to or greater than one:
    *
    * \f[
    *    apoapsis = \infty
    * \f]
    * because parabolic and hyperbolic orbits have no apaopsis.
    *
    * @return The distance in meters.
    */
    meter_type apoapsis() const;

    /**
    * @brief Get the distance of the apoapsis from the focal point (the closest
    * distance during orbit).
    *
    * \f[
    *    apoapsis = \frac{p}{1 + e}
    * \f]
    *
    * @return The distance in meters.
    */
    meter_type periapsis() const;

    /**
    * @brief Check if this is a closed orbit (elliptic and circular), otherwise
    * it is open (parabolic and hyperbolic).
    *
    * @return True if the orbit is closed.
    */
    bool isClosed() const;

  private:
    meter_type m_semimajorAxis;
    double m_eccentricity;
    radian_type m_inclination;
    radian_type m_longitudeOfAscendingNode;
    radian_type m_argumentOfPeriapsis;
    kilo_type m_parentMass;

    // derived parameters
    second_type m_period;
    double m_mu;
};

}

#endif
