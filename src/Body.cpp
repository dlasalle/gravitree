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
    std::string const name,
    kilo_type const mass) :
  m_name(name),
  m_mass(mass),
  m_angularVelocity()
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

std::string Body::name() const noexcept
{
  return m_name;
}

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

}
