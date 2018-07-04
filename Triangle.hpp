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
        Vect3F A, B, C, surfaceNorm;
    public:

        Triangle() {
        }

        Triangle(const Vect3F &a,
                const Vect3F &b,
                const Vect3F &c,
                const Vect3F &sn,
                const Material &mat) :
        A(a), B(b), C(c), surfaceNorm(sn) {
            Shape::material = mat;
        }
        bool intersect(const Ray &ray, float &t0, float &t1);

        Vect3F getSideA() const {
            return A;
        }

        Vect3F getSideB() const {
            return B;
        }

        Vect3F getSideC() const {
            return C;
        }
    };
}
#endif /* TRIANGLE_HPP */