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

  m_bodies.emplace(m_root->body.id(), std::move(rootPtr));
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
    Body::id_type const parent)
{
  node_struct * const parentNode = m_bodies.at(parent).get();

  OrbitalState const state = OrbitalState::fromVectors( \
      position, velocity, parentNode->body.mass());

  addBody(body, state, parent);
}

void SolarSystem::addBody(
    Body const body,
    OrbitalState const state,
    Body::id_type const parent)
{
  node_struct * const parentNode = m_bodies.at(parent).get();

  std::unique_ptr<node_struct> ptr(new node_struct{body, state, parentNode, {}});

  parentNode->children.emplace_back(ptr.get());

  m_bodies.emplace(body.id(), std::move(ptr));
}

void SolarSystem::removeBody(
    Body::id_type const id)
{
  node_struct * const node = m_bodies.at(id).get();
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

  m_bodies.erase(id); 
}

Body const * SolarSystem::getBody(
    Body::id_type const id) const
{
  return &m_bodies.at(id)->body;
}

Body * SolarSystem::getBody(
    Body::id_type const id)
{
  return &m_bodies.at(id)->body;
}

std::vector<std::pair<Body const *, Vector3D>>
    SolarSystem::getRelativeTo(
        Body::id_type const id) const
{
  // start with children nodes
  std::vector<std::pair<Body const *, Vector3D>> list;
  list.reserve(m_bodies.size());

  node_struct const * node = m_bodies.at(id).get();
  Vector3D origin = node->state.position();

  getTreeRelativeTo(-origin, node, &list);

  // scan up the tree adding nodes, when siblings are encountered add their
  // trees
  node_struct const * parent = node->parent;
  while (parent != nullptr) {
    list.emplace_back(&parent->body, -origin);

    for (node_struct const * const sibling : parent->children) {
      if (sibling != node) {
        getTreeRelativeTo(-origin, sibling, &list);
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

  Vector3D const offset = node->state.position() + origin;
  list->emplace_back(&node->body, offset);

  for (node_struct const * const child : node->children) {
    assert(child != nullptr); 
    getTreeRelativeTo(offset, child, list); 
  }
}

}
