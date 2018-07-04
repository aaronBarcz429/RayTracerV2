/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camera.hpp
 * Author: Aaron
 *
 * Created on June 20, 2018, 8:58 PM
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vector.hpp"

namespace raytracer
{
    class Camera
    {
        private:
            Vect3F eye, look_at, up;
            float top, right, bottom, left, focal_length;
        public:
            Camera() :
            top(0.0), right(0.0), bottom(0.0), left(0.0), focal_length(0.0) {
            }
            Camera(const Vect3F &e,
                    const Vect3F &la,
                    const Vect3F &u,
                    const float &fl) :
            eye(e), look_at(la), up(u), top(0.0),
            right(0.0), bottom(0.0), left(0.0), focal_length(fl) {
            }
            
            Vect3F getW() const {
                Vect3F w = eye - look_at;
                w = w.normalize();
                return w;
            }
            
            Vect3F getU() const {
                Vect3F u = up.crossProduct(getW());
                u = u.normalize();
                return u;
            }

            Vect3F getV() const {
                return getW().crossProduct(getU());
            }
            
            Vect3F getEye() const {
                return eye;
            }
            
            void setEye(const Vect3F & e){
                eye = e;
            }
            
            Vect3F getLookAt() const {
                return look_at;
            }
            
            void setLookAt(const Vect3F &la){
                look_at = la;
            }
            
            Vect3F getUp() const {
                return up;
            }
            
            void setUp(const Vect3F &u){
                up = u;
            }

            float getRight() const {
                return right;
            }

            float getLeft() const {
                return left;
            }

            float getTop() const {
                return top;
            }

            float getBottom() const {
                return bottom;
            }

            float getFocalLength() const {
                return focal_length;
            }
            
            void setFocalLength(const float &fl){
                focal_length = fl;
            }

            void setRight(const float &r) {
                right = r;
            }

            void setLeft(const float &l) {
                left = l;
            }

            void setTop(const float &t) {
                top = t;
            }

            void setBottom(const float &b) {
                bottom = b;
            }
    };
}


#endif /* CAMERA_HPP */