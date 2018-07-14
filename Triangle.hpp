/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Triangle.hpp
 * Author: Aaron
 *
 * Created on June 30, 2018, 11:06 AM
 */

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"
#include "Material.hpp"

namespace raytracer {

    class Triangle : public Shape {
    private:
        Vect3F A, B, C, surface_normal;
    public:

        Triangle() {
        }
        
        Triangle(const Vect3F &a,
                const Vect3F &b,
                const Vect3F &c,
                const Material &mat) :
        A(a), B(b), C(c), surface_normal(Vect3F()) {
            Shape::material = mat;
        }

        Triangle(const Vect3F &a,
                const Vect3F &b,
                const Vect3F &c,
                const Vect3F &sn,
                const Material &mat) :
        A(a), B(b), C(c), surface_normal(sn) {
            Shape::position = surface_normal;
            Shape::material = mat;
        }
        
        bool intersect(const Ray &ray, float &t0, float &t1);
        
        bool trace(float &t_near, const Ray &ray);
        
        Vect3F getSNorm(const Ray &ray, const float &t_near) const {
             return surface_normal;
        }
        
        Ray getReflectionRay(const Ray &ray){
            
        }
        Ray getRefractionRay(const Ray &ray){
            
        }        
        float getLenseEffect(const float &face_level){
            return 1;
        }

        Vect3F getSideA() const {
            return A;
        }

        Vect3F getSideB() const {
            return B;
        }

        Vect3F getSideC() const {
            return C;
        }
        
        Vect3F getSurfaceNormal() const {
            return surface_normal;
        }
        
        void printTriangle() const {
            std::cout << "A: " << A << std::endl;
            std::cout << "B: " << B << std::endl;
            std::cout << "C: " << C << std::endl;
            std::cout << "Nor: " << Shape::position << std::endl;
        }
    };
}
#endif /* TRIANGLE_HPP */