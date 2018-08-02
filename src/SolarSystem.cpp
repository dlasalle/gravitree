/**
* @file SolarSystem.cpp
* @brief Imlementation of the SolarSystem class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-01
*/

#include "SolarSystem.hpp"

namespace gravitree
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

SolarSystem::SolarSystem(
    Body const root) :
  m_time(0.0),
  m_bodies(),
  m_root(nullptr)
{
  std::unique_ptr<node_struct> rootPtr(new node_struct{
      root,
      OrbitalState(KeplerOrbit(0, 0, 0, 0, 0, 0), 0),
      nullptr,
      {}});
  m_root = rootPtr.get();

  m_bodies.emplace(m_root->body.name(), std::move(rootPtr));
}

/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void SolarSystem::tick(
    second_type const seconds)
{
  m_time += seconds;
}

void SolarSystem::addBody(
    Body const body,
    Vector3D const position,
    Vector3D const velocity,
    std::string const parent)
{
  if (m_bodies.count(parent) == 0) {
    throw UnknownBodyException(parent); 
  }
  node_struct * const parentNode = m_bodies.at(parent).get();

  OrbitalState const state = OrbitalState::fromVectors( \
      position, velocity, parentNode->body.mass());

  addBody(body, state, parent);
}

void SolarSystem::addBody(
    Body const body,
    OrbitalState const state,
    std::string const parent)
{
  if (m_bodies.count(parent) == 0) {
    throw UnknownBodyException(parent); 
  }
  node_struct * const parentNode = m_bodies.at(parent).get();

  std::unique_ptr<node_struct> ptr(new node_struct{body, state, parentNode, {}});
  m_bodies.emplace(body.name(), std::move(ptr));

  parentNode->children.emplace_back(ptr.get());
}

void SolarSystem::removeBody(
    std::string const name)
{
  node_struct * const node = m_bodies.at(name).get();
  if (node->parent != nullptr) {
    throw InvalidOperationException("Remove root");
  }

  Vector3D const offsetPos = node->state.position();
  Vector3D const offsetVel = node->state.velocity();

  for (node_struct * const child : node->children) {
    Vector3D const pos = offsetPos + child->state.position();
    Vector3D const vel = offsetVel + child->state.velocity();

    child->state = OrbitalState::fromVectors(pos, vel, \
        node->parent->body.mass());

    node->parent->children.emplace_back(child);
  }

  m_bodies.erase(name); 
}

std::vector<std::pair<Body*, Vector3D>> SolarSystem::getSystemRelativeTo(
    std::string const name) const
{
  return std::vector<std::pair<Body*, Vector3D>>();
}





}
