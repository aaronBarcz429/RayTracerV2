#include "Raytracer.hpp"

void runTests()
{
    raytracer::Vect3F zero_vector;
    raytracer::Vect3F single_value_vector(2.1234);
    raytracer::Vect3F diff_value_vector(1.245, 2.1234, 3.1234);
    raytracer::Vect3F vector_alpha(2.125, 1.25, 4.5);
    raytracer::Vect3F vector_bravo(3.75, 2.225, 5.377);
    float scalar = 5.23953;
    std::cout << "Start Test..." << std::endl;
    std::cout << "Zero Vector: " << zero_vector << std::endl;
    std::cout << "Single value vector: " << single_value_vector << std::endl;
    std::cout << "Different value vector: " << diff_value_vector << std::endl;
    std::cout << "Add " << vector_alpha << " and " << vector_bravo << ": " << (vector_alpha + vector_bravo) << std::endl;
    std::cout << "Add " << vector_alpha << " and " << scalar << ": " << (vector_alpha + scalar) << std::endl;
    std::cout << "Subtract " << vector_alpha << " and " << vector_bravo << ": " << (vector_alpha - vector_bravo) << std::endl;
    std::cout << "Subtract " << vector_alpha << " and " << scalar << ": " << (vector_alpha - scalar) << std::endl;
    std::cout << "Multiply " << vector_alpha << " and " << vector_bravo << ": " << (vector_alpha * vector_bravo) << std::endl;
    std::cout << "Multiply " << vector_alpha << " and " << scalar << ": " << (vector_alpha * scalar) << std::endl;
    std::cout << "Divide " << vector_alpha << " and " << vector_bravo << ": " << (vector_alpha / vector_bravo) << std::endl;
    std::cout << "Divide " << vector_alpha << " and " << scalar << ": " << (vector_alpha / scalar) << std::endl;
    std::cout << "Add Assign " << vector_alpha << " and " << vector_bravo << ": " << (vector_alpha += vector_bravo) << std::endl;
    std::cout << "Add Assign " << vector_alpha << " and " << scalar << ": " << (vector_alpha += scalar) << std::endl;
    std::cout << "Dot product " << vector_alpha << " and " << vector_bravo << ": " << (vector_alpha.dotProduct(vector_bravo)) << std::endl;
    std::cout << "Dot product " << vector_bravo << " and " << vector_alpha << ": " << (vector_bravo.dotProduct(vector_alpha)) << std::endl;
    std::cout << "Cross product " << vector_alpha << " and " << vector_bravo << ": " << (vector_alpha.crossProduct(vector_bravo)) << std::endl;
    std::cout << "Cross product " << vector_bravo << " and " << vector_alpha << ": " << (vector_bravo.crossProduct(vector_alpha)) << std::endl;
    std::cout << "Magnitude " << vector_alpha << ": " << vector_alpha.magnitude() << std::endl;
    std::cout << "Magnitude " << vector_bravo << ": " << vector_bravo.magnitude() << std::endl;
    std::cout << "Normalize " << vector_alpha << ": " << vector_alpha.normalize() << std::endl;
    std::cout << "Magnitude " << vector_alpha << ": " << vector_alpha.magnitude() << std::endl;
    std::cout << "Normalize " << vector_bravo << ": " << vector_bravo.normalize() << std::endl;
    std::cout << "Magnitude " << vector_bravo << ": " << vector_bravo.magnitude() << std::endl;
    std::cout << "Raytracer Test: " << (raytracer::RayTracer::raytracerTest()) << std::endl;
}

/*
 * 
 */
int main(int argc, char** argv) {
    raytracer::RayTracer::raytracerTest();
    //runTests();
    return 0;
}

