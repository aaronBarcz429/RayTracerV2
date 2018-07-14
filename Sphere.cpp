/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sphere.hpp"

namespace raytracer{
    
    Sphere::Sphere(const Vect3F &pos, const Material &mat, const float &rad)
    {
        Shape::position = pos;
        Shape::material = mat;
        radius = rad;
        radius_squared = rad * rad;
    }
    
    bool Sphere::intersect(const Ray &ray, float &t0, float &t1)
    {
        Vect3F L = ray.getOrigin(), D = ray.getDirection();
	Vect3F tv = getPosition() - L;
	float v = tv.dotProduct(D);
	if(v < 0){
            return false;
        }            
	float dsq = tv.dotProduct(tv) - (v*v);
	if(dsq > radius_squared){
            return false;
        }
	float b = sqrt(radius_squared - dsq);
	t0 = v - b;
	t1 = v + b;
        return true;
    }
    
    bool Sphere::trace(float &t_near, const Ray &ray) {
        float t0 = INFINITY;
        float t1 = INFINITY;
        if (intersect(ray, t0, t1)) {
            if (t0 < 0) {
                t0 = t1;
            }
            if (t0 < t_near) {
                t_near = t0;
                return true;
            }
        }
        return false;
    }
}