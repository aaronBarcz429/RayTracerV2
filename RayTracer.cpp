#include "Raytracer.hpp"

namespace raytracer {

    /**
     * Use to create a lense effect
     * @param const float a
     * @param const float b
     * @param const float mix
     * @return float
     */
    float RayTracer::blend(const float &a, const float &b, const float &mix) {
        return b * mix + a * (1 - mix);
    }

    Vect3F RayTracer::refractRay(const Vect3F& W, const Vect3F& pt,
            const Vect3F& N, const float& eta1, const float& eta2, const Shape& shape) {
        float etar = eta1 / eta2;
        float a = etar * -1;
        float wn = W.dotProduct(N);
        float radsq = 1 - (etar * etar) * (1 - wn * wn);
        Vect3F T(0.0);
        if (radsq > 0) {
            float b = (etar * wn) - sqrt(radsq);
            T = (W * a) + (N * b);
        }
        return T;
    }

    Ray RayTracer::refractExit(const Vect3F& W, const Vect3F& pt, const float& eta_in, const Shape& shape) {
        Ray refR;
        Vect3F T1 = refractRay(W, pt, (pt - shape.getPosition()).normalize(), 1.0, eta_in, shape);
        float t1_sum = T1.sum();
        if (t1_sum != 0.0) {
            Vect3F exit = pt + T1 * 2 * (shape.getPosition() - pt).dotProduct(T1);
            Vect3F Nin = shape.getPosition() - exit;
            Vect3F T2 = refractRay(T1 * -1, exit, Nin, eta_in, 1.0, shape);
            refR = Ray(exit, T2);
        }
        return refR;
    }

    /**
     * Draws the object(s) in the world.
     * @param const Ray ray
     * @param const int level
     * @return Vect3F
     */
    Vect3F RayTracer::draw(const Ray& ray, const int& level) {
        Vect3F ori = ray.getOrigin();
        Vect3F dir = ray.getDirection();
        float t_near = INFINITY;
        Vect3F pixel_value;
        const Shape *shape = NULL;
        if (!shapes.empty()) {
            for (unsigned i = 0; i < shapes.size(); i++) {
                float t0 = INFINITY;
                float t1 = INFINITY;
                if (shapes[i]->intersect(ray, t0, t1)) {
                    if (t0 < 0) {
                        t0 = t1;
                    }
                    if (t0 < t_near) {
                        t_near = t0;
                        shape = shapes[i];
                    }
                }
            }
        }
        if (!shape) {
            return Vect3F(0.0);
        }
        Vect3F ptos = ori + (dir * t_near);
        Vect3F snorm = (ptos - shape->getPosition()).normalize();
        float bias = 1.0e-4;
        for (unsigned int i = 0; i < lights.size(); i++) {
            Vect3F ptl = (lights[i].getPosition() - ptos).normalize();
            Vect3F eml = lights[i].getColor();
            if (snorm.dotProduct(ptl) > 0) {
                pixel_value += eml * shape->getMaterial().getDiffusion() * std::max(float(0), snorm.dotProduct(ptl));
                pixel_value += eml * shape->getMaterial().getSpecular()
                        * std::max(float(0), (float) pow(snorm.dotProduct(ptl), shape->getMaterial().getLevel()));
            }
        }
        if (level > 0) {
            float face_level = dir.dotProduct(snorm);
            float lense_effect = blend(pow(1 - face_level, 6), 1, 0.2);
            Vect3F reflect_direction(dir - snorm * 2 * face_level);
            reflect_direction.normalize();
            Ray reflect_ray(((ptos + snorm) * bias), reflect_direction);
            Vect3F reflection(draw(reflect_ray, level - 1));
            Ray refract_ray = refractExit(dir * -1, ptos, shape->getMaterial().getRefractionIndex(), *shape);
            Vect3F refraction(0.0);
            if (refract_ray.getDirection().sum() && shape->getMaterial().getOpacity().sum()) {
                refraction = draw(refract_ray, level - 1);
            }
            pixel_value += (reflection * lense_effect * shape->getMaterial().getReflection()
                    + refraction * lense_effect * shape->getMaterial().getOpacity())
                    * shape->getMaterial().getDiffusion();
        }
        return pixel_value;
    }

    /**
     * Converts string into an array using a char delimiter
     * @param const std::string str
     * @param const char delimiter
     * @return std::string
     */
    std::vector<std::string> RayTracer::split(const std::string &str, const char &delimiter) {
        std::vector<std::string> result;
        std::string data;
        std::stringstream ss(str);
        while (getline(ss, data, delimiter)) {
            result.push_back(data);
        }
        return result;
    }

    bool RayTracer::raytracerTest() {
        RayTracer ray_tracer = RayTracer(2000, 3000);
        ray_tracer.readSceneFile("SceneTwo.txt");
        ray_tracer.renderScene();
        return true;
    }

    Vect3F RayTracer::parseCameraVector(const std::vector<std::string> &line_split) {
        float x = 0.0,
                y = 0.0,
                z = 0.0;
        x = std::stof(line_split[1]);
        y = std::stof(line_split[2]);
        z = std::stof(line_split[3]);
        return Vect3F(x, y, z);
    }

    void RayTracer::parseCameraPlane(const std::vector<std::string> &line_split) {
        camera.setRight(std::stof(line_split[1]));
        camera.setLeft(std::stof(line_split[2]));
        camera.setTop(std::stof(line_split[3]));
        camera.setBottom(std::stof(line_split[4]));
    }

    void RayTracer::parseLights(const std::vector<std::string> &line_split) {
        Light light(Vect3F(std::stof(line_split[1]),
                std::stof(line_split[2]),
                std::stof(line_split[3])),
                Vect3F(std::stof(line_split[4]),
                std::stof(line_split[5]),
                std::stof(line_split[6])));
        lights.push_back(light);
    }

    Material RayTracer::parseMaterial(const std::vector<std::string> &line_split) {
        Material material(
                Vect3F(std::stof(line_split[1]),
                std::stof(line_split[2]),
                std::stof(line_split[3])),
                Vect3F(std::stof(line_split[4]),
                std::stof(line_split[5]),
                std::stof(line_split[6])),
                Vect3F(std::stof(line_split[7]),
                std::stof(line_split[8]),
                std::stof(line_split[9])),
                Vect3F(std::stof(line_split[10]),
                std::stof(line_split[11]),
                std::stof(line_split[12])),
                Vect3F(std::stof(line_split[13]),
                std::stof(line_split[14]),
                std::stof(line_split[15])),
                std::stof(line_split[16]),
                std::stof(line_split[17]));
        return material;
    }

    void RayTracer::parseShapes(const std::vector<std::string> &line_split, const Material &material) {
        if (line_split[0] == "sphere") {
            Sphere * sphere = new Sphere(
                    Vect3F(std::stof(line_split[1]),
                    std::stof(line_split[2]),
                    std::stof(line_split[3])),
                    material,
                    std::stof(line_split[4]));
            shapes.push_back(sphere);
        }
        if (line_split[0] == "triangle") {
            Triangle * triangle = new Triangle(
                    Vect3F(std::stof(line_split[1]),
                    std::stof(line_split[2]),
                    std::stof(line_split[3])),
                    Vect3F(std::stof(line_split[4]),
                    std::stof(line_split[5]),
                    std::stof(line_split[6])),
                    Vect3F(std::stof(line_split[7]),
                    std::stof(line_split[8]),
                    std::stof(line_split[9])),
                    Vect3F(std::stof(line_split[10]),
                    std::stof(line_split[11]),
                    std::stof(line_split[12])),
                    material);
            shapes.push_back(triangle);
        }
    }

    bool RayTracer::readSceneFile(const std::string &file_name) {
        std::string line;
        std::ifstream in_file;
        std::vector<std::string> line_split;
        int line_count = 0;
        in_file.open(file_name, std::ios::binary | std::ios::in);
        if (!in_file) {
            std::cerr << "Error: file " << file_name << " does not exist." << std::endl;
            return false;
        }
        while (getline(in_file, line)) {
            line_split = split(line, ' ');
            std::string variable = line_split[0];
            line_count++;
            if (variable.compare("eye") == 0 && line_count == 1) {
                camera.setEye(parseCameraVector(line_split));
                continue;
            } else if (variable.compare("look") == 0 && line_count == 2) {
                camera.setLookAt(parseCameraVector(line_split));
                continue;
            } else if (variable.compare("up") == 0 && line_count == 3) {
                camera.setUp(parseCameraVector(line_split));
                continue;
            } else if (variable.compare("fl") == 0 && line_count == 4) {
                camera.setFocalLength(std::stof(line_split[1]));
                continue;
            } else if (variable.compare("plane") == 0 && line_count == 5) {
                parseCameraPlane(line_split);
                continue;
            } else if (variable.compare("light") == 0) {
                parseLights(line_split);
                continue;
            } else if (variable.compare("material") == 0) {
                material = parseMaterial(line_split);
                continue;
            } else if (variable.compare("sphere") == 0 || variable.compare("triangle") == 0) {
                parseShapes(line_split, material);
                continue;
            } else {
                std::cerr << "File Format Error: variable " << variable <<
                        " is not valid or is in the wrong place.";
                return false;
            }
        }
        std::cout << "Finished Reading file..." << std::endl;
        std::cout << "Number of shapes: " << shapes.size() << std::endl;
        in_file.close();
        return true;
    }

    bool RayTracer::readObjectFile(const std::string& file_name) {
        return true;
    }

    bool RayTracer::writeToPNG() {
        return true;
    }

    bool RayTracer::writeToPPM(const Vect3F *image) {
        std::ofstream outFile;
        outFile.open("output.ppm", std::ios::binary | std::ios::out);
        outFile << "P6\n" << width << " " << height << "\n255\n";
        for (unsigned int i = 0; i < width * height; ++i) {
            outFile << (unsigned char) (std::min(float(1), image[i].getX()) * 255) <<
                    (unsigned char) (std::min(float(1), image[i].getY()) * 255) <<
                    (unsigned char) (std::min(float(1), image[i].getZ()) * 255);
        }
        outFile.close();
        return true;
    }

    bool RayTracer::renderScene() {
        Vect3F W = camera.getW();
        Vect3F U = camera.getU();
        Vect3F V = camera.getV();
        Vect3F E = camera.getEye();
        float fl = camera.getFocalLength();
        float r = camera.getRight(),
                l = camera.getLeft(),
                t = camera.getTop(),
                b = camera.getBottom();
        float px = 0.0f, py = 0.0f;
        Vect3F ori, dir;
        Vect3F *image = new Vect3F[width * height], *pixel = image;
        float aspectRatio = (float) width / (float) height;
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < width; j++, pixel++) {
                px = (float) j / ((float)width - 1.0f)*(r - l) + l;
                py = (float) i / ((float)height - 1.0f)*(t - b) + b;
                px *= aspectRatio;
                ori = E + (W * -fl) + (U * px) + (V * py);
                dir = (ori - E).normalize();
                Ray ray(ori, dir);
                *pixel = draw(ray, 5);
            }
            std::cout << "Percent Completed: " << (i / (float) height) * 100 << "\r";
        }
        writeToPPM(image);
        delete [] image;
        return true;
    }
}

