/**
 * @file Shape.hpp
 * @brief The Shape abstract class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-03-19
 */



#ifndef GRAVITREE_SHAPE_HPP
#define GRAVITREE_SHAPE_HPP


namespace gravitree
{

class Shape
{
  public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Shape()
    {
      // do nothing
    }

    /**
     * @brief Get the coefficient of the moment of inertia about an axis.
     *
     * @return The coefficient.
     */
    virtual double momentCoefficient(
        Vector3D const axis) const noexcept = 0;
};

}

#endif

