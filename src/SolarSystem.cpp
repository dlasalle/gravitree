/**
* @file SolarSystem.cpp
* @brief Imlementation of the SolarSystem class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-01
*/

#include "SolarSystem.hpp"

#include <cassert>

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
  node_struct * const parentNode = m_bodies.at(parent).get();

  std::unique_ptr<node_struct> ptr(new node_struct{body, state, parentNode, {}});

  parentNode->children.emplace_back(ptr.get());

  m_bodies.emplace(body.name(), std::move(ptr));
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

Body SolarSystem::getBody(
    std::string const name) const
{
  return m_bodies.at(name)->body;
}

std::vector<std::pair<Body const *, Vector3D>>
    SolarSystem::getSystemRelativeTo(
        std::string const name) const
{
  // start with children nodes
  std::vector<std::pair<Body const *, Vector3D>> list;
  list.reserve(m_bodies.size());

  node_struct const * node = m_bodies.at(name).get();
  Vector3D origin = node->state.position();

  getTreeRelativeTo(Vector3D(0,0,0), node, &list);

  // scan up the tree adding nodes, when siblings are encountered add their
  // trees
  node_struct const * parent = node->parent;
  while (parent != nullptr) {
    list.emplace_back(&parent->body, -origin);

    for (node_struct const * const sibling : parent->children) {
      if (sibling != node) {
        getTreeRelativeTo(sibling->state.position() - origin, sibling, &list);
      }
    }

    // move up the tree
    node = parent;
    parent = node->parent;
    origin += node->state.position();
  }

  return list;
}

/******************************************************************************
* PRIVATE METHODS *************************************************************
******************************************************************************/

void SolarSystem::getTreeRelativeTo(
      Vector3D const origin,
      node_struct const * const node,
      std::vector<std::pair<Body const *, Vector3D>> * const list) const
{
  assert(origin.isValid());

  list->emplace_back(&node->body, origin);

  for (node_struct const * const child : node->children) {
    assert(child != nullptr); 
    getTreeRelativeTo(child->state.position() + origin, child, list); 
  }
}

}
