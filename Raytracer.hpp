/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newfile.hpp
 * Author: Aaron
 *
 * Created on June 24, 2018, 1:38 PM
 */

#ifndef NEWFILE_HPP
#define NEWFILE_HPP

#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Ray.hpp"

namespace raytracer{
    /**
     * Read Scene,
     * Render Scene,
     * Write to PPM or PNG
     */
    class RayTracer
    {
    private:
        unsigned int height, width;
        Camera camera;
        Material material;
        std::vector<Shape*> shapes;
        std::vector<Light> lights;
        std::vector<std::string> split(const std::string &str, const char &delimiter);        
        bool readObjectFile(const std::string &file_name);
        bool writeToPNG();
        bool writeToPPM(const Vect3F * image);
        Vect3F refractRay(Vect3F const &W, Vect3F const &pt, Vect3F const &N,
		float const &eta1, float const &eta2, Shape const &shape);
        Ray refractExit(Vect3F const &W, Vect3F const &pt, float const &eta_in, const Shape &shape);
        Vect3F draw(const Ray &ray, const int &level);
        float blend(const float &a, const float &b, const float &mix);
        Vect3F parseCameraVector(const std::vector<std::string> &line_split);
        std::string parseCameraFocalLength(const std::vector<std::string> &line_split);
        void parseCameraPlane(const std::vector<std::string> &line_split);
        void parseLights(const std::vector<std::string> &line_split);
        Material parseMaterial(const std::vector<std::string> &line_split);
        void parseShapes(const std::vector<std::string> &line_split, const Material &material);
    public:
        RayTracer():
        height(480), width(640){}
        RayTracer(const unsigned int &h, const unsigned int &w):
        height(h), width(w){}
        bool renderScene();        
        static bool raytracerTest();
        bool readSceneFile(const std::string &file_name);
    };
}
#endif /* NEWFILE_HPP */

