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
        return 
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
        Vect3F P = pt - shape.getPosition();
        Vect3F T1 = refractRay(W, pt, P.normalize(), 1.0, eta_in, shape);
        float t1_sum = T1.sum();
        if (t1_sum != 0.0) {
            Vect3F F = shape.getPosition() - pt;
            Vect3F exit = pt + T1 * 2 * F.dotProduct(T1);
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
        Vect3F dir = ray.getDirection();
        float t_near = INFINITY;
        Vect3F pixel_value;
        const Shape *shape = NULL;
        if (!shapes.empty()) {
            for (unsigned i = 0; i < shapes.size(); i++) {
                if(shapes[i]->trace(t_near, ray)){
                    shape = shapes[i];
                    //std::cout << "Shape number: " << (i+1) << std::endl;
                }
            }
        }
        if (!shape) {
            return Vect3F(0.0);
        }
        Vect3F ptos = shape->setPtoS(ray, t_near);
        Vect3F snorm = shape->setSNorm(ray, t_near);
        snorm.normalize();
        for (unsigned int i = 0; i < lights.size(); i++) {
            Vect3F ptl = lights[i].getPosition() - ptos;
            ptl = ptl.normalize();
            Vect3F eml = lights[i].getColor();
            if (snorm.dotProduct(ptl) > 0) {
                pixel_value += eml * shape->getMaterial().getDiffusion() * std::max(float(0), snorm.dotProduct(ptl));
                pixel_value += eml * shape->getMaterial().getSpecular()
                        * std::max(float(0), (float) pow(snorm.dotProduct(ptl), shape->getMaterial().getLevel()));
            }
        }
        if (level > 0) {
            Ray reflect_ray = shape->getReflectRay(ray);
            Vect3F reflection(draw(reflect_ray, level - 1));
            Ray refract_ray = refractExit(dir * -1, ptos, shape->getMaterial().getRefractionIndex(), *shape);
            Vect3F refraction(0.0);
            if (refract_ray.getDirection().sum() && shape->getMaterial().getOpacity().sum()) {
                refraction = draw(refract_ray, level - 1);
            }
            pixel_value += (reflection * shape->getLenseEffect() * shape->getMaterial().getReflection()
                    + refraction * shape->getLenseEffect() * shape->getMaterial().getOpacity())
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
        RayTracer ray_tracer = RayTracer(1000, 2000);
        ray_tracer.readSceneFile("SceneTorus.txt");
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
        std::string progress_line = "start reading scene";
        std::string line;
        std::ifstream in_file;
        std::vector<std::string> line_split;
        int line_count = 0;
        in_file.open(file_name, std::ios::binary | std::ios::in);
        if (!in_file) {
            std::cerr << "Error: file " << file_name << " does not exist." << std::endl;
            return false;
        }
        std::cout << progress_line;
        while (getline(in_file, line)) {
            line_split = split(line, ' ');
            std::string variable = line_split[0];
            line_count++;
            // Ignore comments
            if(variable[0] == '#'){
                if(line_count > 5){
                    continue;
                }else{
                    line_count -= 1;
                    continue;
                }
            }
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
            } else if (variable.compare("object") == 0){
                readObjectFile(line_split[1]);
                continue;
            } else {
                std::cerr << "File Format Error: variable " << variable <<
                        " is not valid or is in the wrong place.";
                return false;
            }
            progress_line += ".";
            std::cout << progress_line;
        }
        std::cout << progress_line << "...";
        std::cout << "done" << std::endl;
        std::cout << "number of shapes: " << shapes.size() << std::endl;
        in_file.close();
        return true;
    }

    bool RayTracer::readObjectFile(const std::string& file_name) {
        std::string line;
        std::ifstream in_file;
        std::vector<std::string> line_split;
        std::vector<Vect3F> verticies;
        std::vector<Vect3F> normals;
        in_file.open(file_name, std::ios::binary | std::ios::in);
        if (!in_file) {
            std::cerr << "Error: file " << file_name << " does not exist." << std::endl;
            return false;
        }
        while(getline(in_file, line)){
            line_split = split(line, ' ');
            std::string variable = line_split[0];
            // Ignore comments
            if(variable[0] == '#'){
                continue;
            }
            if(variable.compare("v") == 0){
                Vect3F vertex = Vect3F(
                        std::stof(line_split[1]),
                        std::stof(line_split[2]),
                        std::stof(line_split[3]));
                verticies.push_back(vertex);
                continue;
            } else if (variable.compare("vn") == 0){
                Vect3F normal = Vect3F(
                        std::stof(line_split[1]),
                        std::stof(line_split[2]),
                        std::stof(line_split[3]));
                normals.push_back(normal);
            } else if (variable.compare("f") == 0){
                std::string str = line_split[1];
                std::string vertex_str = str.substr(0, str.find("//"));
                int x_index = std::stoi(vertex_str);
                std::string normal_str = str.substr(str.find("//")+2, str.size());
                int normal_index = std::stoi(normal_str);
                str = line_split[2];
                vertex_str = str.substr(0, str.find("//"));
                int y_index = std::stoi(vertex_str);
                str = line_split[3];
                vertex_str = str.substr(0, str.find("//"));
                int z_index = std::stoi(vertex_str);
                Triangle * triangle = new Triangle(
                        verticies[x_index-1],
                        verticies[y_index-1],
                        verticies[z_index-1],
                        normals[normal_index-1],material);
                shapes.push_back(triangle);
            }
        }
        in_file.close();
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
            if(i % 1000 == 0){
                std::cout << "creating file: " << (i / (float) (width * height)) * 100 << "\r";
            }            
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
                dir = ori - E;
                dir = dir.normalize();
                Ray ray(ori, dir);
                *pixel = draw(ray, 5);                
            }
            std::cout << "rendering: " << (i / (float) height) * 100 << "\r";
        }
        std::cout << std::endl << "done" << std::endl;
        writeToPPM(image);
        delete [] image;
        return true;
    }
}

