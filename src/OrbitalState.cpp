/**
 * @file OrbitalState.cpp
 * @brief Implementation of the OrbitalState class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-07-31
 */

#include "OrbitalState.hpp"
#include "Constants.hpp"
#include "Gravity.hpp"

#include "Output.hpp"
#include <iostream>

#include <cassert>

namespace gravitree
{

/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

radian_type calcEccentricAnomally(
    KeplerOrbit const orbit,
    radian_type const trueAnomally)
{
  double const e2 = orbit.eccentricity() * orbit.eccentricity();
  double const num = std::sqrt(1.0-e2) * std::sin(trueAnomally);
  double const den = orbit.eccentricity() + std::cos(trueAnomally);
  return std::atan2(num, den);
}

radian_type calcMeanAnomally(
    KeplerOrbit const orbit,
    radian_type const eccentricAnomally)
{
  return eccentricAnomally - orbit.eccentricity()*std::sin(eccentricAnomally);
}

double newtonsMethod(
    radian_type const meanAnomally,
    double const eccentricity,
    size_t const maxIterations,
    double const tolerance)
{
  double eccentricAnomally = meanAnomally;
  double residual = eccentricity*std::sin(eccentricAnomally);
  for (size_t i = 0; i < maxIterations; ++i) {
    eccentricAnomally -= \
        (residual / (1.0 - eccentricity * std::cos(eccentricAnomally)));
    residual = eccentricAnomally - \
        eccentricity * std::sin(eccentricAnomally) - meanAnomally;
    if (residual < tolerance) {
      break;
    }
  }

  return eccentricAnomally;
}

}


/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

OrbitalState OrbitalState::fromVectors(
    Vector3D const position,
    Vector3D const velocity,
    kilo_type const parentMass)
{
  Vector3D const hVec = position.cross(velocity);
  double const h = hVec.magnitude();

  double const r = position.magnitude();
  double const v = velocity.magnitude();

  double const mu = parentMass * Gravity::G;

  double const E = v*v*0.5 - (mu / r);

  double const semimajorAxis = - 0.5 * mu / E;
  double const eccentricity = std::sqrt(1.0-(h*h)/(semimajorAxis*mu));

  double const cos_i = hVec.z() / h;
  double const inclination = std::acos(cos_i);

  double const sin_i = std::sin(inclination);

  double const longitudeOfAscendingNode = std::atan2(hVec.x(), -hVec.y());
  double const cos_W = std::cos(longitudeOfAscendingNode);
  double const sin_W = std::sin(longitudeOfAscendingNode);

  double const w_v = std::atan2( \
      position.z() / sin_i, \
      position.x() * cos_W + position.y() * sin_W);

  double const p = semimajorAxis * (1.0 - eccentricity*eccentricity);

  double const trueAnomally = std::atan2( \
      std::sqrt(p/mu) * (position*position), p-r);

  double const argumentOfPeriapsis = w_v - trueAnomally;

  KeplerOrbit orbit(semimajorAxis, eccentricity, inclination,
      longitudeOfAscendingNode, argumentOfPeriapsis, parentMass);

  return OrbitalState(orbit, trueAnomally);
}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

OrbitalState::OrbitalState(
    KeplerOrbit const orbit,
    radian_type const trueAnomally) :
  m_orbit(orbit),
  m_trueAnomally(trueAnomally),
  m_eccentricAnomally(0),
  m_meanAnomally(0),
  m_time(0)
{
  m_eccentricAnomally = calcEccentricAnomally(orbit, trueAnomally);
  m_meanAnomally = calcMeanAnomally(orbit, m_eccentricAnomally);

  // time since epoch 
  m_time = (m_meanAnomally*orbit.period()) / (2.0 * Constants::PI);
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void OrbitalState::setTime(
    second_type const time) noexcept
{
  m_time = time;

  double const sweepRate = 2.0 * Constants::PI / m_orbit.period(); 
  m_meanAnomally = sweepRate * time;

  m_eccentricAnomally = newtonsMethod(m_meanAnomally, \
      m_orbit.eccentricity(), 512, 1e-8);

  double const e2 = m_eccentricAnomally*0.5;

  m_trueAnomally = 2.0 * std::atan2(
      std::sqrt(1.0+m_orbit.eccentricity())*std::sin(e2),
      std::sqrt(1.0-m_orbit.eccentricity())*std::cos(e2));
}

Vector3D OrbitalState::velocity() const noexcept
{
  double const cos_W = std::cos(m_orbit.longitudeOfAscendingNode());
  double const sin_W = std::sin(m_orbit.longitudeOfAscendingNode());

  double const sin_v = std::sin(m_trueAnomally);
  double const cos_wv = std::cos( \
      m_orbit.argumentOfPeriapsis() + m_trueAnomally);
  double const sin_wv = std::sin( \
      m_orbit.argumentOfPeriapsis() + m_trueAnomally);

  double const cos_i = std::cos(m_orbit.inclination());
  double const sin_i = std::sin(m_orbit.inclination());

  double const r = distance();
  double const p = m_orbit.semilatusRectum(); 

  double const h = m_orbit.angularMomentum(); 
  double const h_r = h / r;
  double const he_rp = (m_orbit.eccentricity() / p) * h_r;

  Vector3D const pos = position();
  Vector3D const vel =  Vector3D(
      (pos.x() * he_rp * sin_v) - (h_r*(cos_W*sin_wv+sin_W*cos_wv*cos_i)),
      (pos.y() * he_rp * sin_v) - (h_r*(sin_W*sin_wv+cos_W*cos_wv*cos_i)),
      (pos.z() * he_rp * sin_v) + (h_r*(sin_i * cos_wv)));

  return vel;
}

Vector3D OrbitalState::position() const noexcept
{
  double const cos_W = std::cos(m_orbit.longitudeOfAscendingNode());
  double const sin_W = std::sin(m_orbit.longitudeOfAscendingNode());

  double const r = distance();

  double const cos_wv = std::cos( \
      m_orbit.argumentOfPeriapsis() + m_trueAnomally);
  double const sin_wv = std::sin( \
      m_orbit.argumentOfPeriapsis() + m_trueAnomally);

  double const cos_i = std::cos(m_orbit.inclination());
  double const sin_i = std::sin(m_orbit.inclination());

  return Vector3D(
      r * (cos_W * cos_wv - sin_W * sin_wv * cos_i),
      r * (sin_W * cos_wv + cos_W * sin_wv * cos_i),
      r * (sin_i * sin_wv));
}

meter_type OrbitalState::distance() const noexcept
{
  double const a = m_orbit.semimajorAxis();
  double const e = m_orbit.eccentricity();
  double const cos_E = std::cos(m_eccentricAnomally);

  return a * (1.0 - e * cos_E);
}

radian_type OrbitalState::trueAnomally() const noexcept
{
  return m_trueAnomally;
}

radian_type OrbitalState::meanAnomally() const noexcept
{
  return m_meanAnomally;
}

radian_type OrbitalState::eccentricAnomally() const noexcept
{
  return m_eccentricAnomally;
}

second_type OrbitalState::time() const noexcept
{
  return m_time;
}

KeplerOrbit OrbitalState::orbit() const noexcept
{
  return m_orbit;
}

}

