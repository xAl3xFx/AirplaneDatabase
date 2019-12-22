#include <iostream>
#include "Models/Plane.hpp"
#include "Factories/PlaneFactory.hpp"
#include <fstream>
#include <string>

int main() {

//    Plane p(1,"asd", Plane::Cargo, 2);]
    Plane* p = PlaneFactory::createPlane(1,"asd", Plane::Cargo, 2);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}