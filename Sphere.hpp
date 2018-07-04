/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sphere.hpp
 * Author: Aaron
 *
 * Created on June 24, 2018, 1:06 PM
 */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Vector.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Shape.hpp"

namespace raytracer
{
    class Sphere : public Shape
    {
    private:
        float radius, radius_squared;
    public:
        Sphere(){};
        Sphere(const Vect3F &pos, const Material &mat, const float &rad);
        bool intersect(const Ray &ray, float &t0, float &tl);
    };
}

#endif /* SPHERE_HPP */

