#include <iostream>
#include "Utils/REPL.hpp"

int main() {

//    Plane p(1,"asd", Plane::Cargo, 2);]
    //Plane* p = PlaneFactory::createPlane(1,"asd", Plane::Cargo, 2);

    REPL repl;
    repl.run();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}