/**
* @file LeapFrogIntegrator.hpp
* @brief The LeapFrogIntegrator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-03-30
*/


#ifndef ORBITREE_LEAPFROGINTEGRATOR_HPP
#define ORBITREE_LEAPFROGINTEGRATOR_HPP

#include "KineticStateDelta.hpp"
#include "Vector3D.hpp"
#include "Types.hpp"

namespace gravitree
{

class LeapFrogIntegrator
{
  public:
    template <typename F>
    inline static KineticStateDelta integrate(
        Vector3D const position,
        Vector3D const velocity,
        F const gravity,
        second_type const step) noexcept
    {
      // kick drift form of leap-frog integrator
      Vector3D const slope = gravity(position);
      Vector3D const halfVelDelta = slope*step*0.5;
      Vector3D const posDelta = (velocity+halfVelDelta)*step;
      Vector3D const slopeNext = gravity(position+posDelta);
      Vector3D const velDelta = halfVelDelta + slopeNext*step*0.5;

      return KineticStateDelta(posDelta, velDelta);
    }
};

}

#endif

