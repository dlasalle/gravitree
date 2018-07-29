/**
 * @file Body.cpp
 * @brief Implementation of the Body class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-03-19
 */


#include "Body.hpp"

namespace gravitree
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

Body::Body(
    kilo_type const mass) :
  m_mass(mass),
  m_angularVelocity(),
  m_linearVelocity(),
  m_position()
{
  // do nothing
}


Body::~Body()
{
    // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

kilo_type Body::mass() const noexcept
{
  return m_mass;
}

Rotation Body::angularVelocity() const noexcept
{
  return m_angularVelocity;
}

void Body::setAngularVelocity(
    Rotation const velocity) noexcept
{
  m_angularVelocity = velocity;
}

Vector3D Body::linearVelocity() const noexcept
{
  return m_linearVelocity;
}

void Body::setLinearVelocity(
    Vector3D const velocity) noexcept
{
  m_linearVelocity = velocity;
}

void Body::move(
    Vector3D const delta) noexcept
{
  m_position += delta;
}

void Body::accelerateLinear(
    Vector3D const delta) noexcept
{
  m_linearVelocity += delta;
}

Position Body::position() const noexcept
{
  return m_position;
}


}
