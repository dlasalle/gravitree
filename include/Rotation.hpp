/**
 * @file Rotation.hpp
 * @brief The Rotation class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-03-19
 */



#ifndef GRAVITREE_ROTATION_HPP
#define GRAVITREE_ROTATION_HPP

#include "Vector3D.hpp"
#include "Types.hpp"

namespace gravitree
{

class Rotation
{
  public:
    /**
     * @brief Create a new rotation of magnitude zero.
     */
    Rotation() noexcept :
      m_vec(1.0, 0.0, 0.0),
      m_rot(0.0)
    {
      // do nothing
    }

    /**
     * @brief Create a new rotation vector.
     *
     * @param vec The vector around which to rotate.
     * @param rot The rotation (in radians).
     */
    Rotation(
        Vector3D const vec,
        radian_type const rot) noexcept :
      m_vec(vec),
      m_rot(rot)
    {
      // do nothing
    }

    /**
    * @brief Get the vector this rotation is around.
    *
    * @return The vector.
    */
    Vector3D axis() const noexcept
    {
      return m_vec;
    }

    /**
    * @brief Get the angle of this rotation.
    *
    * @return The angle.
    */
    radian_type angle() const noexcept
    {
      return m_rot;
    }

    /**
    * @brief Equals operator.
    *
    * @param other The other rotation.
    *
    * @return True if the axis and angle are equal.
    */
    bool operator==(
        Rotation const & other) const noexcept
    {
      return m_vec == other.m_vec && m_rot == other.m_rot;
    }

  private:
    Vector3D m_vec;
    radian_type m_rot;
};

}

#endif
