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
}

void SolarSystem::addBody(
    Body const body,
    Vector3D const position,
    Vector3D const velocity,
    std::string const parent)
{
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
}

std::vector<std::pair<Body*, Vector3D>> SolarSystem::getSystemRelativeTo(
    std::string const name) const
{
  return std::vector<std::pair<Body*, Vector3D>>();
}





}
