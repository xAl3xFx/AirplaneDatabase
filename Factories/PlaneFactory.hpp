//
// Created by Alex on 22.12.2019.
//

#ifndef AIRPLANEDATABASE_PLANEFACTORY_HPP
#define AIRPLANEDATABASE_PLANEFACTORY_HPP

#include "./../Models/Plane.hpp"

class PlaneFactory{
public:
    static Plane* createPlane(long long _id, std::string _plane, Plane::Type _type, unsigned long long _flights);
};

Plane* PlaneFactory::createPlane(long long _id, std::string _plane, Plane::Type _type, unsigned long long _flights) {
    return new Plane(_id, _plane, _type, _flights);
}

#endif //AIRPLANEDATABASE_PLANEFACTORY_HPP
