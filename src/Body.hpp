/**
* @file Body.hpp
* @brief The Body class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-19
*/



#ifndef GRAVITREE_BODY_HPP
#define GRAVITREE_BODY_HPP

#include "Position.hpp"
#include "Vector3D.hpp"
#include "Rotation.hpp"
#include "Types.hpp"

#include <memory>

namespace gravitree
{

class Body
{
  public:
    /**
    * @brief Create a physics body.
    *
    * @param mass The mass of the body.
    */
    Body(
        kilo_type mass);

    /**
    * @brief Virtual destructor.
    */
    virtual ~Body();

    /**
    * @brief Get the mass of the object.
    *
    * @return The mass.
    */
    kilo_type mass() const noexcept;

    /**
    * @brief Get the angular velocity of this object.
    *
    * @return The velocity.
    */
    Rotation angularVelocity() const noexcept;

    /**
    * @brief Set the angular velocity.
    *
    * @param velocity The angular velocity.
    */
    void setAngularVelocity(
        Rotation velocity) noexcept;

    /**
    * @brief Get the linear velocity of this object.
    *
    * @return The velocity.
    */
    Vector3D linearVelocity() const noexcept;
    
    /**
    * @brief Set the linear velocity.
    *
    * @param velocity The new linear velocity.
    */
    void setLinearVelocity(
        Vector3D velocity) noexcept;

    /**
    * @brief Move the object by the given delta in meters.
    *
    * @param delta The delta in meters.
    */
    void move(
        Vector3D delta) noexcept;

    /**
    * @brief Accelerate this body linearly
    *
    * @param delta The linear change in velocity.
    */
    void accelerateLinear(
        Vector3D delta) noexcept;

    /**
    * @brief Get the position of the object.
    *
    * @return The position.
    */
    Position position() const noexcept;
 
  private:
    kilo_type m_mass;
    Rotation m_angularVelocity;
    Vector3D m_linearVelocity;
    Position m_position;

};

}

#endif
