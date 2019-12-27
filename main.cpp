#include <iostream>
#include "Utils/REPL.hpp"
int main() {

    //Plane* p = PlaneFactory::createPlane(1,"asd", Plane::Cargo, 2);

    REPL repl;
    repl.run();
    return 0;
}