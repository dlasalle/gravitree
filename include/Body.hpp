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
#include <string>

namespace gravitree
{

class Body
{
  public:
    /**
    * @brief Create a physics body.
    *
    * @param name The name of the body.
    * @param mass The mass of the body.
    */
    Body(
        std::string name,
        kilo_type mass);

    /**
    * @brief Virtual destructor.
    */
    virtual ~Body();

    /**
    * @brief Get the name of this body.
    *
    * @return The name of this body.
    */
    std::string name() const noexcept;

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

  private:
    std::string m_name;
    kilo_type m_mass;
    Rotation m_angularVelocity;

};

}

#endif
