//
// Created by Alex on 22.12.2019.
//

#ifndef AIRPLANEDATABASE_PLANE_HPP
#define AIRPLANEDATABASE_PLANE_HPP

class Plane {
public:
    enum Type
    {
        Jet,
        Cargo,
        Airliner
    };

    Plane(long long _id, std::string _plane, Type _type, unsigned long long _flights) : id(_id), plane(_plane), type(_type), flights(_flights) {}

private:
    long long id;
    std::string plane;
    Plane::Type type;
    unsigned long long flights;

};

#endif //AIRPLANEDATABASE_PLANE_HPP
