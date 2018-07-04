/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Light.hpp
 * Author: Aaron
 *
 * Created on June 24, 2018, 6:38 AM
 */

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vector.hpp"


namespace raytracer {

    class Light {
    private:
        Vect3F position, color;
    public:

        Light() {
        }

        Light(const Vect3F &pos, const Vect3F &col) :
        position(pos), color(col) {
        }

        Vect3F getPosition() const {
            return position;
        }

        Vect3F getColor() const {
            return color;
        }
    };
}

#endif /* LIGHT_HPP */