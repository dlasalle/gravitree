/**
* @file Vector3D.hpp
* @brief The Vector3D class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-19
*/



#ifndef GRAVITREE_VECTOR3D_HPP
#define GRAVITREE_VECTOR3D_HPP


#include <cmath>
#include <ostream>

namespace gravitree
{

class Vector3D
{
  public:
    /**
    * @brief A new three dimensional vector.
    *
    * @param x The x dimension.
    * @param y The y dimension.
    * @param y The z dimension.
    */
    Vector3D(
        double const x=0.0,
        double const y=0.0,
        double const z=0.0) noexcept:
      m_x(x),
      m_y(y),
      m_z(z),
      m_length2(x*x + y*y + z*z)
    {
      // do nothing
    }

    /**
    * @brief Get the x component.
    *
    * @return The x component.
    */
    inline double x() const noexcept
    {
      return m_x;
    }

    /**
    * @brief Get the y component.
    *
    * @return The y component.
    */
    inline double y() const noexcept
    {
      return m_y;
    }

    /**
    * @brief Get the z component.
    *
    * @return The z component.
    */
    inline double z() const noexcept
    {
      return m_z;
    }

    /**
    * @brief Get this vector in polar coordates, with x = longitude, y =
    * latitude, z = altitude (from origin).
    *
    * @return The polar coordinates.
    */
    inline Vector3D toPolarCoordinates() const noexcept
    {
      double const r = magnitude();
      double const phi = atan2(m_y, m_x);
      double const theta = r > 0.0 ? asin(m_z / r) : 0.0;
      return Vector3D(phi, theta, r);
    }

    /**
    * @brief Get the square of the distance between this and another vector.
    *
    * @param other The other vector.
    *
    * @return The square of the distance.
    */
    inline double distance2(
        Vector3D const other) const noexcept
    {
      return (*this - other).magnitude2();
    }

    /**
    * @brief Get the distance between this and another vector.
    *
    * @param other The other vector.
    *
    * @return The distance.
    */
    inline double distance(
        Vector3D const other) const noexcept
    {
      return (*this - other).magnitude();
    }

    /**
    * @brief Perform the dot product between this vector and another.
    *
    * @param other The other vector.
    *
    * @return The result.
    */
    inline double operator*(
        Vector3D const & other) const noexcept
    {
      return m_x*other.m_x + m_y*other.m_y + m_z*other.m_z;
    }

    /**
    * @brief Perform the cross product between two vector.
    *
    * @param other The other vector.
    *
    * @return The cross product.
    */
    inline Vector3D cross(
        Vector3D const & other) const noexcept
    {
      return Vector3D(
          m_y*other.m_z - m_z*other.m_y,
          -(m_x*other.m_z - m_z*other.m_x),
          m_x*other.m_y - m_y*other.m_x);
    }

    /**
    * @brief Scale this vector (v) and get the result: a*v.
    *
    * @param scalar The scalar (a).
    *
    * @return The result (av).
    */
    inline Vector3D operator*(
        double const scalar) const noexcept
    {
      return Vector3D(m_x*scalar, m_y*scalar, m_z*scalar,
          m_length2*scalar*scalar);
    }

    /**
    * @brief Divide this vector (v) and get the result: (v_x/a, v_y/a, v_z/a).
    *
    * @param scalar The divisor (a).
    *
    * @return The result (v/a).
    */
    inline Vector3D operator/(
        double const scalar) const noexcept
    {
      return Vector3D(m_x/scalar, m_y/scalar, m_z/scalar, \
          m_length2/(scalar*scalar));
    }



    /**
    * @brief Add two vector together and return the result.
    *
    * @param other The other vector to add.
    *
    * @return The addition of the two vectors. 
    */
    inline Vector3D operator+(
        Vector3D const & other) const noexcept
    {
      return Vector3D(m_x+other.m_x, m_y+other.m_y, m_z+other.m_z);
    }

    /**
    * @brief Subtract a vector from this one..
    *
    * @param other The other vector to subtract.
    *
    * @return The difference of the two vectors.
    */
    inline Vector3D operator-(
        Vector3D const & other) const noexcept
    {
      return Vector3D(m_x-other.m_x, m_y-other.m_y, m_z-other.m_z);
    }

    /**
    * @brief Get the negative of this vector.
    *
    * @return The negation of this vector.
    */
    inline Vector3D operator-() const noexcept
    {
      return Vector3D(-m_x, -m_y, -m_z);
    }

    /**
    * @brief Get the square of the magnitude of this vector.
    *
    * @return The square of the magnitude.
    */
    inline double magnitude2() const noexcept
    {
      return m_length2;
    }

    /**
    * @brief Return the magnitude of this vector.
    *
    * @return The magnitude.
    */
    inline double magnitude() const noexcept
    {
      return std::sqrt(m_length2); 
    }

    /**
    * @brief Perform the dot product between this vector and another storing
    * the result in this vector.
    *
    * @param other The other vector.
    *
    * @return This vector.
    */
    inline Vector3D& operator*=(
        Vector3D const & other) noexcept
    {
      m_x *= other.m_x; 
      m_y *= other.m_y;
      m_z *= other.m_z;
      updateLength();

      return *this;
    }

    /**
    * @brief Scale this vector by some value storing the result in this vector.
    *
    * @param scalar The scalar to scale by.
    *
    * @return This vector.
    */
    inline Vector3D& operator*=(
        double const scalar) noexcept
    {
      m_x *= scalar; 
      m_y *= scalar;
      m_z *= scalar;
      m_length2 *= scalar*scalar;

      return *this;
    }

    /**
    * @brief Add another vector to this one storing the result in this vector.
    *
    * @param other The other vector.
    *
    * @return This vector.
    */
    inline Vector3D& operator+=(
        Vector3D const & other) noexcept
    {
      m_x += other.m_x; 
      m_y += other.m_y;
      m_z += other.m_z;
      updateLength();

      return *this;
    }

    /**
    * @brief Subtract another vector from this one storing the result in this
    * vector.
    *
    * @param other The other vector.
    *
    * @return This vector.
    */
    inline Vector3D& operator-=(
        Vector3D const & other) noexcept
    {
      m_x -= other.m_x; 
      m_y -= other.m_y;
      m_z -= other.m_z;
      updateLength();

      return *this;
    }

    /**
    * @brief Check if this vector is equal to another.
    *
    * @param other The vector to test for equality.
    *
    * @return True if the vectors are equal.
    */
    inline bool operator==(
        Vector3D const& other) const noexcept
    {
      return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
    }

    /**
    * @brief Check if this vector is not equal to another.
    *
    * @param other The vector to test against.
    *
    * @return True if the vectors are not equal.
    */
    inline bool operator!=(
        Vector3D const& other) const noexcept
    {
      return !this->operator==(other);
    }

    /**
    * @brief Check if this vector is less than another.
    *
    * @param other The vector to test against.
    *
    * @return True if this vector is less than the other.
    */
    inline bool operator<(
        Vector3D const& other) const noexcept
    {
      return m_z < other.m_z || (m_z == other.m_z && ( \
          m_y < other.m_y || (m_y == other.m_y && \
              m_x < other.m_x)));
    }

    /**
    * @brief Check if this vector is greater than another.
    *
    * @param other The vector to test against.
    *
    * @return True if this vector is greater than the other.
    */
    inline bool operator>(
        Vector3D const& other) const noexcept
    {
      return m_z > other.m_z || (m_z == other.m_z && ( \
          m_y > other.m_y || (m_y == other.m_y && \
              m_x > other.m_x)));
    }

    /**
    * @brief Check if this vector is less or equal than another.
    *
    * @param other The vector to test against.
    *
    * @return True if this vector is less or equal than the other.
    */
    inline bool operator<=(
        Vector3D const& other) const noexcept
    {
      return !(*this > other);
    }

    /**
    * @brief Check if this vector is greater or equal than another.
    *
    * @param other The vector to test against.
    *
    * @return True if this vector is greater or equal than the other.
    */
    inline bool operator>=(
        Vector3D const& other) const noexcept
    {
      return !(*this < other);
    }

    /**
    * @brief Get a normalized version of this vector. If this vector has zero
    * magnitude, the normalized version will also be a vector of magnitude
    * zero.
    *
    * @return The normalized version.
    */
    inline Vector3D normalized() const noexcept
    {
      double const mag = magnitude();
      double const invMag = mag != 0 ? 1.0 / mag : 0.0;
      return (*this)*invMag;
    }

    /**
    * @brief Check if all values in this vector are valid (i.e., neither NaN or
    * Inf).
    *
    * @return True if all the values are valid.
    */
    inline bool isValid() const noexcept
    {
      return std::isfinite(m_x) && std::isfinite(m_y) && std::isfinite(m_z);
    }

  private:
    union {
      struct {
        double m_x;
        double m_y;
        double m_z;
        double m_length2;
      };

      double m_v[4];
    };

    /**
    * @brief Update the length of this vector.
    */
    inline void updateLength() noexcept
    {
      m_length2 = m_x*m_x + m_y*m_y + m_z*m_z;
    }

    /**
    * @brief A new three dimensional vector.
    *
    * @param x The x dimension.
    * @param y The y dimension.
    * @param z The z dimension.
    * @param m2 The square of the magnitude of the vector.
    */
    Vector3D(
        double const x,
        double const y,
        double const z,
        double const m2) noexcept:
      m_x(x),
      m_y(y),
      m_z(z),
      m_length2(m2)
    {
      // do nothing
    }
};

}

#endif
