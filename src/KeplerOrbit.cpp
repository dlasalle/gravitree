/**
* @file KeplerOrbit.cpp
* @brief Implementation of the KeplerOrbit class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-23
*/

#include "KeplerOrbit.hpp"
#include "Gravity.hpp"
#include "Constants.hpp"
#include <cmath>

namespace gravitree
{

/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

double calcPeriod(
    meter_type const semimajorAxis,
    kilo_type const parentMass)
{
  double const a3 = semimajorAxis*semimajorAxis*semimajorAxis;
  double const mu = Gravity::G * parentMass;
  return 2.0*Constants::PI*std::sqrt(a3/mu);
}

}

/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

KeplerOrbit::KeplerOrbit(
    meter_type const semimajorAxis,
    double const eccentricity,
    radian_type const inclination,
    radian_type const longitudeOfAscendingNode,
    radian_type const argumentOfPeriapsis,
    kilo_type const parentMass) :
  m_semimajorAxis(semimajorAxis),
  m_eccentricity(eccentricity),
  m_inclination(inclination),
  m_longitudeOfAscendingNode(longitudeOfAscendingNode),
  m_argumentOfPeriapsis(argumentOfPeriapsis),
  m_parentMass(parentMass),
  m_period(calcPeriod(semimajorAxis, parentMass)),
  m_mu(parentMass*Gravity::G)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

meter_type KeplerOrbit::semimajorAxis() const
{
  return m_semimajorAxis;
}


double KeplerOrbit::eccentricity() const
{
  return m_eccentricity;
}


radian_type KeplerOrbit::inclination() const
{
  return m_inclination;
}


radian_type KeplerOrbit::longitudeOfAscendingNode() const
{
  return m_longitudeOfAscendingNode;
}

radian_type KeplerOrbit::argumentOfPeriapsis() const
{
  return m_argumentOfPeriapsis;
}

kilo_type KeplerOrbit::parentMass() const
{
  return m_parentMass;
}

second_type KeplerOrbit::period() const
{
  return m_period;
}

double KeplerOrbit::mu() const
{
  return m_mu;
}

double KeplerOrbit::angularMomentum() const
{
  double const e2 = m_eccentricity*m_eccentricity;
  return std::sqrt(m_mu * m_semimajorAxis * (1.0 - e2));
}

meter_type KeplerOrbit::apoapsis() const
{
  if (m_eccentricity >= 1.0) {
    return INFINITY; 
  }

  double const num = m_semimajorAxis * ( 1 - m_eccentricity*m_eccentricity);
  double const den = 1 - m_eccentricity;

  return num / den;
}

meter_type KeplerOrbit::periapsis() const
{
  double const num = m_semimajorAxis * ( 1 - m_eccentricity*m_eccentricity);
  double const den = 1 + m_eccentricity;

  return num / den;
}

}

