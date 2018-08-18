/**
* @file SolarSystem.hpp
* @brief The SolarSystem class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-01
*/


#ifndef GRAVITREE_SRC_SOLARSYSTEM_HPP
#define GRAVITREE_SRC_SOLARSYSTEM_HPP

#include "Body.hpp"
#include "OrbitalState.hpp"
#include "Vector3D.hpp"

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace gravitree
{

class InvalidOperationException : public std::runtime_error
{
  public:
  InvalidOperationException(std::string const operation) :
      std::runtime_error(operation)
  {
    // do nothing
  }
};



class SolarSystem
{
  public:
  /**
  * @brief Create a new solar system.
  *
  * @param root The body which serves as the root of the solar system.
  */
  SolarSystem(
      Body root);

  /**
  * @brief Deleted copy constructor.
  *
  * @param rhs The solar system to copy.
  */
  SolarSystem(
      SolarSystem const& rhs) = delete;

  /**
  * @brief Deleted assignment operator.
  *
  * @param rhs The object to copy.
  *
  * @return This object.
  */
  SolarSystem& operator=(
      SolarSystem const& rhs) = delete;

  /**
  * @brief Advance the solar system by the given number of seconds.
  *
  * @param seconds The seconds passing.
  */
  void tick(
      second_type seconds);

  /**
  * @brief Add a body with the specified position and velocity. It will be
  * added as a child of whichever body its sphere of influence it occupies.
  *
  * @param body The body.
  * @param position The position relative to the parent body.
  * @param velocity The velocity relative to the parent body.
  * @param parent The body being orbited.
  */
  void addBody(
      Body body,
      Vector3D position,
      Vector3D velocity,
      Body::id_type parent);
  
  /**
  * @brief Add a body with the specified orbit.
  *
  * @param body The body.
  * @param state The orbit.
  * @param parent The body being orbited.
  */
  void addBody(
      Body body,
      OrbitalState state,
      Body::id_type parent);
 
  /**
  * @brief Remove a body from the system.
  *
  * @param id The id of the body.
  */
  void removeBody(
      Body::id_type id);

  /**
  * @brief Get the body with the given name.
  *
  * @param id The body's id.
  *
  * @return The body.
  */
  Body getBody(
      Body::id_type id) const;
  
  /**
  * @brief Get the location of every body in the system relative to another. No
  * rotations are applied.
  *
  * @param body The body of the body to use as the origin.
  *
  * @return The pairs of bodies and relative positions.
  */
  std::vector<std::pair<Body const *, Vector3D>> getRelativeTo(
      Body::id_type body) const;

  private:
  struct node_struct
  {
    Body body;
    OrbitalState state;
    node_struct * parent;
    std::vector<node_struct*> children;
  };

  second_type m_time;
  std::map<Body::id_type, std::unique_ptr<node_struct>> m_bodies;
  node_struct * m_root;

  void getTreeRelativeTo(
      Vector3D origin,
      node_struct const * node,
      std::vector<std::pair<Body const *, Vector3D>> * list) const;
};

}

#endif
