/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Triangle.hpp"

namespace raytracer {

    bool Triangle::intersect(const Ray &ray, float &t0, float &t1) {
        Vect3F E1 = B - A;
        Vect3F E2 = C - A;
        Vect3F dir = ray.getDirection();
        Vect3F ori = ray.getOrigin();
        Vect3F pVect = dir.crossProduct(E2);
        float det = E1.dotProduct(pVect);
        float invDet = 1 / det;
        if (det < 0.0000000001f) return false;
        Vect3F tVect = ori - A;
        float u = tVect.dotProduct(pVect) * invDet;
        if (u < 0 || u > 1) return false;
        Vect3F qVect = tVect.crossProduct(E1);
        float v = dir.dotProduct(qVect) * invDet;
        if (v < 0 || u+v > 1) return false;
        t0 = E2.dotProduct(qVect) * invDet;
        return true;
    }
    
    bool Triangle::trace(float& t_near, const Ray& ray)
    {
        if(intersect(ray, t_near, t_near)){
            return true;
        }
        return false;
    }
}