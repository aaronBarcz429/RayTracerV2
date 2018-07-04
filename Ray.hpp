/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ray.hpp
 * Author: Aaron
 *
 * Created on June 24, 2018, 6:45 AM
 */

#ifndef RAY_HPP
#define RAY_HPP

#include "Vector.hpp"

namespace raytracer
{
    class Ray
    {
    private:
        Vect3F origin, direction;
    public:
        Ray(){}
        Ray(const Vect3F &ori, const Vect3F &dir):
        origin(ori), direction(dir){}
        Vect3F getOrigin() const {return origin;}
        Vect3F getDirection() const {return direction;}
    };
}

#endif /* RAY_HPP */

