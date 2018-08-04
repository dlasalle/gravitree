/**
* @file KineticStateDelta.hpp
* @brief The KineticStateDelta class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-30
*/



#ifndef GRAVITREE_KINETICSTATEDELTA_HPP
#define GRAVITREE_KINETICSTATEDELTA_HPP

#include "Vector3D.hpp"

namespace gravitree
{

class KineticStateDelta
{
  public:
    /**
    * @brief Create a new KineticStateDelta.
    *
    * @param posDelta The change in position.
    * @param velDelta The change in linear velocity.
    */
    KineticStateDelta(
        Vector3D const posDelta,
        Vector3D const velDelta) :
      m_posDelta(posDelta),
      m_velDelta(velDelta)
    {
      // do nothing
    }

    /**
    * @brief Create a new KineticStateDelta.
    */
    KineticStateDelta() :
      m_posDelta(0, 0, 0),
      m_velDelta(0, 0, 0)
    {
      // do nothing
    }

    /**
    * @brief Create a copy of a KineticStateDelta.
    *
    * @param other
    */
    KineticStateDelta(
        KineticStateDelta const & other) :
      m_posDelta(other.m_posDelta),
      m_velDelta(other.m_velDelta)
    {
      // do nothing
    }

    /**
    * @brief Assignment operator.
    *
    * @param other The KineticStateDelta to assign from.
    *
    * @return The assigned state.
    */
    KineticStateDelta& operator=(
        KineticStateDelta const & other) noexcept
    {
      m_posDelta = other.m_posDelta;
      m_velDelta = other.m_velDelta;
      return *this;
    }

    /**
    * @brief Get the change in position.
    *
    * @return The change.
    */
    inline Vector3D position() const noexcept
    {
      return m_posDelta;
    }

    /**
    * @brief Get the change in velocity.
    *
    * @return The change.
    */
    inline Vector3D velocity() const noexcept
    {
      return m_velDelta;
    }

  private:
    Vector3D m_posDelta;
    Vector3D m_velDelta;
};

}

#endif
