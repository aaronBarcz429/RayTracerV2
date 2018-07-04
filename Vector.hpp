/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector.hpp
 * Author: Aaron
 *
 * Created on June 19, 2018, 8:07 PM
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

namespace raytracer
{
    template<typename T>
    class Vector
    {
        private:
            T x_cord, y_cord, z_cord;
        public:
            /**
             * 
             */
            Vector():
                    x_cord(0.0), y_cord(0.0), z_cord(0.0){}
            /**
             * Copy constructor 
             * @param n
             */
            Vector(const T &n):
                    x_cord(n), y_cord(n), z_cord(n){}
            /**
             * Copy constructor to set all three vector elements
             * @param s
             * @param t
             * @param u
             */
            Vector(const T &s, const T &t, const T &u):
                    x_cord(s), y_cord(t), z_cord(u){}
            T getX() const { return x_cord; }
            T getY() const { return y_cord; }
            T getZ() const { return z_cord; }
            
            /**
             * Add vector by a scalar
             * @param n
             * @return Vector<T> 
             */
            Vector<T> operator + (const T &n) const
            {
                return Vector<T>(x_cord+n, y_cord+n, z_cord+n);
            }
            
            /**
             * Add vector by another vector
             * @param n
             * @return Vector<T> 
             */
            Vector<T> operator + (const Vector<T> &n) const
            {
                return Vector<T>(x_cord+n.x_cord, y_cord+n.y_cord, z_cord+n.z_cord);
            }
            
            /**
             * Subtract vector by a scalar
             * @param n
             * @return Vector<T> 
             */
            Vector<T> operator - (const T &n) const
            {
                return Vector<T>(x_cord-n, y_cord-n, z_cord-n);
            }
            
            /**
             * Subtract vector by another vector
             * @param n
             * @return 
             */
            Vector<T> operator - (const Vector<T> &n) const
            {
                return Vector<T>(x_cord-n.x_cord, y_cord-n.y_cord, z_cord-n.z_cord);
            }
            
            /**
             * Multiply by a scalar
             * @param n
             * @return Vector<T>
             */
            Vector<T> operator * (const T &n) const
            {
                return Vector<T>(x_cord*n, y_cord*n, z_cord*n);
            }
            
            /**
             * Multiply by another vector
             * @param n
             * @return Vector<T>
             */
            Vector<T> operator * (const Vector<T> &n) const
            {
                return Vector<T>(x_cord*n.x_cord, y_cord*n.y_cord, z_cord*n.z_cord);
            }
            
            /**
             * Divide by a scalar.
             * Error will be raised if numerator is negative
             * @param n
             * @return Vector<T>
             */
            Vector<T> operator / (const T &n) const
            {
                if(n > 0.0)
                {
                    return Vector<T>(x_cord/n, y_cord/n, z_cord/n);
                }
                else
                {
                    std::cerr << "Error: divide by zero." << std::endl;
                    exit(1000);
                }
                
            }
            
            /**
             * Divide by a vector.
             * Error will be raised if numerator is negative per each element
             * @param n
             * @return Vector<T>
             */
            Vector<T> operator / (const Vector<T> &n) const
            {
                if(n.x_cord > 0.0 && n.y_cord > 0.0 && n.z_cord > 0.0)
                {
                    return Vector<T>(x_cord/n.x_cord, y_cord/n.y_cord, z_cord/n.z_cord);
                }
                else
                {
                    std::cerr << "Error: divide by zero." << std::endl;
                    exit(1000);
                }
                
            }
            
            /**
             * Add-assign by scalar
             * @param n
             * @return Vector<T>
             */
            Vector<T> operator += (const T &n)
            {
                return Vector<T>(x_cord += n, y_cord += n, z_cord += n);
            }
            
            /**
             * Add-assign by vector
             * @param n
             * @return Vector<T>
             */
            Vector<T> operator += (const Vector<T> &n)
            {
                return Vector<T>(x_cord += n.x_cord, y_cord += n.y_cord, z_cord += n.z_cord);
            }
            
            /**
             * print
             * @param v
             * @return
             */
            friend std::ostream & operator << (std::ostream &os, const Vector<T> &v)
            {
                os << v.x_cord << " " << v.y_cord << " " << v.z_cord;
                return os;
            }
            
            /**
             * Dot product of two vectors
             * @param v
             * @return T
             */
            T dotProduct(const Vector<T> &v) const
            {
                return (x_cord*v.x_cord + y_cord*v.y_cord + z_cord*v.z_cord);
            }
            
            /**
             * Calculates normal vector from two vectors
             * @param v
             * @return Vector<T>
             */
            Vector<T> crossProduct(const Vector<T> &v) const
            {
                return Vector<T>((y_cord*v.z_cord) - (z_cord*v.y_cord),
                                 (z_cord*v.x_cord) - (x_cord*v.z_cord),
                                 (x_cord*v.y_cord) - (y_cord*v.x_cord));
            }
            
            /**
             * Find magnitude of a vector
             * @return T
             */
            T magnitude(void) const
            {
                return sqrt(x_cord*x_cord + y_cord*y_cord + z_cord*z_cord);
            }
            
            /**
             * Make vector unit length
             * @return Vector<T>
             */
            Vector<T> &normalize(void)
            {
                    T magInv = 1/magnitude();
                    x_cord*=magInv, y_cord*=magInv, z_cord*=magInv;
                    return *this;
            }
            
            /**
             * Sum all elements in a vector together
             * @return T
             */
            T sum() const
            {
                    return x_cord+y_cord+z_cord;
            }
			
    };
    typedef Vector<float> Vect3F;
}


#endif /* VECTOR_HPP */

