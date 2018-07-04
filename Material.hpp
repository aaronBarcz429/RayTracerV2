/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Material.hpp
 * Author: Aaron
 *
 * Created on June 24, 2018, 12:22 PM
 */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Vector.hpp"

namespace raytracer
{
    class Material
    {
    private:
        Vect3F ambient,
               diffusion,
               specular,
               refraction, 
               opacity;
        float level, refractionIndex;
    public:
        Material():
        level(0.0), refractionIndex(0.0){}
        Material(const Vect3F &ambient,
        const Vect3F &diffusion,
        const Vect3F &specular,
        const Vect3F &refraction,
        const Vect3F &opacity,
        const float &level,
        const float &refractionIndex):
        ambient(ambient), diffusion(diffusion),
        specular(specular), refraction(refraction),
        opacity(opacity), level(level), 
        refractionIndex(refractionIndex){}
        
        Vect3F getAmbient() const {return ambient;}
        Vect3F getDiffusion() const {return diffusion;}
        Vect3F getSpecular() const {return specular;}
        Vect3F getRefraction() const {return refraction;}
        Vect3F getOpacity() const {return opacity;}
        float getLevel() const {return level;}
        float getRefractionIndex() const {return refractionIndex;}
    };
}

#endif /* MATERIAL_HPP */

