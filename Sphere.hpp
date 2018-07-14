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
        bool trace(float &t_near, const Ray &ray);
        Vect3F setSNorm(const Ray &ray, const float &t_near) const {
            Vect3F p = setPtoS(ray, t_near) - getPosition();
            return p;
        }
        float getLenseEffect(const float &face_level) {
            return (1 * 0.2) + pow(1 - face_level, 6) * (1 - 0.2);
        }
        Ray getReflectRay(const Ray &ray);
    };
}

#endif /* SPHERE_HPP */

