/**
* @file Position.hpp
* @brief The Position class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-20
*/



#ifndef GRAVITREE_POSITION_HPP
#define GRAVITREE_POSITION_HPP

#include "Vector3D.hpp"
#include "Types.hpp"

namespace gravitree
{

class Position
{
  public:
    static constexpr double const COARSE_METERS = 1.0e5;
    static constexpr double const FINE_METERS = 1.0e0;

    /**
    * @brief Create a new position from a rough estimate.
    *
    * @param x The x-component in meters.
    * @param y The y-component in meters.
    * @param z The z-component in meters.
    */
    Position(
        double const x = 0.0,
        double const y = 0.0,
        double const z = 0.0) noexcept :
      m_xCoarse10km(std::floor(x/COARSE_METERS)),
      m_yCoarse10km(std::floor(y/COARSE_METERS)),
      m_zCoarse10km(std::floor(z/COARSE_METERS)),
      m_fine1m(
          x - (m_xCoarse10km*COARSE_METERS),
          y - (m_yCoarse10km*COARSE_METERS),
          z - (m_zCoarse10km*COARSE_METERS))
    {
      // do nothing
    }

    /**
    * @brief Create a new position from a rough estimate.
    *
    * @param base The base estimate.
    */
    Position(
        Vector3D const base) noexcept :
      Position(base.x(), base.y(), base.z())
    {
      // do nothing
    }

    /**
    * @brief Get the x component of this position.
    *
    * @return The x component in meters.
    */
    inline meter_type x() const noexcept
    {
      return static_cast<double>(m_xCoarse10km*COARSE_METERS) + m_fine1m.x();
    }

    /**
    * @brief Get the y component of this position.
    *
    * @return The y component in meters.
    */
    inline meter_type y() const noexcept
    {
      return static_cast<double>(m_yCoarse10km*COARSE_METERS) + m_fine1m.y();
    }

    /**
    * @brief Get the z component of this position.
    *
    * @return The z component in meters.
    */
    inline meter_type z() const noexcept
    {
      return static_cast<double>(m_zCoarse10km*COARSE_METERS) + m_fine1m.z();
    }

    /**
    * @brief Convert this position to a vector.
    *
    * @return The vector form.
    */
    inline Vector3D toVector() const noexcept
    {
      return Vector3D(x(), y(), z());
    }

    /**
    * @brief Get the square of the distance between this position and the
    * other.
    *
    * @param other The other position.
    *
    * @return The distance in meters.
    */
    inline meter_type distance2(
        Position const other) const noexcept
    {
      return toVector().distance2(other.toVector());
    }

    /**
    * @brief Get the distance between this position and the other.
    *
    * @param other The other position.
    *
    * @return The distance in meters.
    */
    inline meter_type distance(
        Position const other) const noexcept
    {
      return std::sqrt(distance2(other));
    }

    /**
    * @brief Get this position in polar coordates, with x = longitude, y =
    * latitude, z = altitude (from origin).
    *
    * @return The polary coordinates.
    */
    inline Vector3D toPolarCoordinates() const noexcept
    {
      return toVector().toPolarCoordinates();
    }

    inline Vector3D operator-(
        Position const other) const noexcept
    {
      Vector3D const fine = m_fine1m - other.m_fine1m;
      Vector3D const coarse = Vector3D(
          m_xCoarse10km - other.m_xCoarse10km,
          m_yCoarse10km - other.m_yCoarse10km,
          m_zCoarse10km - other.m_zCoarse10km) * COARSE_METERS;
      return fine + coarse;
    }

    /**
    * @brief Add another vector this position.
    *
    * @param other The other vector.
    *
    * @return This position updated.
    */
    inline Position& operator+=(
        Vector3D const & other) noexcept
    {
      m_xCoarse10km += static_cast<int64_t>(std::floor(other.x() / COARSE_METERS));
      double const xSum = m_fine1m.x() + std::fmod(other.x(), COARSE_METERS);
      m_xCoarse10km += static_cast<int64_t>(std::floor(xSum / COARSE_METERS));

      m_yCoarse10km += static_cast<int64_t>(std::floor(other.y() / COARSE_METERS));
      double const ySum = m_fine1m.y() + std::fmod(other.x(), COARSE_METERS);
      m_yCoarse10km += static_cast<int64_t>(std::floor(ySum / COARSE_METERS));

      m_zCoarse10km += static_cast<int64_t>(std::floor(other.z() / COARSE_METERS));
      double const zSum = m_fine1m.z() + std::fmod(other.x(), COARSE_METERS);
      m_zCoarse10km += static_cast<int64_t>(std::floor(zSum / COARSE_METERS));

      m_fine1m = Vector3D(
          std::fmod(xSum, COARSE_METERS),
          std::fmod(ySum, COARSE_METERS),
          std::fmod(zSum, COARSE_METERS));

      return *this;
    }


    /**
    * @brief Add another vector this position.
    *
    * @param other The other vector.
    *
    * @return This position updated.
    */
    inline Position& operator-=(
        Vector3D const & other) noexcept
    {
      return (*this) += -other;
    }

  private:
    int64_t m_xCoarse10km;
    int64_t m_yCoarse10km;
    int64_t m_zCoarse10km;

    /**
    * @brief Distance from the 10 kilometer position in meters.
    */
    Vector3D m_fine1m;
};

}

#endif
