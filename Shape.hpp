/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Shape.hpp
 * Author: Aaron
 *
 * Created on June 30, 2018, 11:02 AM
 */

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Vector.hpp"
#include "Material.hpp"
#include "Ray.hpp"

namespace raytracer
{
    class Shape
    {
    protected:
        Vect3F position;
        Material material;
    public:
        Shape(){}
        virtual ~Shape(){}
        virtual bool intersect(const Ray &ray, float &t0, float &t1) = 0;
        Vect3F getPosition() const { return position; }
        Material getMaterial() const { return material; }
        void setMatieral(const Material &mat) { material = mat; }
    };
}

#endif /* SHAPE_HPP */

