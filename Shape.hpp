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

#define BIAS 1.0e-4

namespace raytracer
{
    class Shape
    {
    protected:
        Vect3F position, ptos, snorm;
        Material material;
    public:
        Shape(){}
        virtual ~Shape(){}
        virtual bool intersect(const Ray &ray, float &t0, float &t1) = 0;
        virtual bool trace(float &t_near, const Ray &ray) = 0;
        virtual Vect3F setSNorm(const Ray &ray, const float &t_near) const = 0;
        virtual Ray getReflectRay(const Ray &ray) = 0;
        virtual float getLenseEffect(const float &face_level) = 0;
        Vect3F getPosition() const { return position; }
        Material getMaterial() const { return material; }
        void setMatieral(const Material &mat) { material = mat; }
        Vect3F setPtoS(const Ray &ray, const float &t_near) const {
            ptos = ray.getOrigin() + (ray.getDirection() * t_near);
        }
    };
}

#endif /* SHAPE_HPP */

