//
// Created by Alex on 22.12.2019.
//

#ifndef AIRPLANEDATABASE_PLANE_HPP
#define AIRPLANEDATABASE_PLANE_HPP

#include <string>
#include <vector>

using namespace std;

class Plane {
public:
    enum Type
    {
        Jet,
        Cargo,
        Airliner
    };

    Plane(long long _id, std::string _plane, Type _type, unsigned long long _flights) : id(_id), plane(_plane), type(_type), flights(_flights) {}
    Plane();
    Plane(string, bool);
    string toString() const;
    long long getId() const;

private:
    long long id;
    std::string plane;
    Plane::Type type;
    unsigned long long flights;


};

Plane::Plane(string str, bool withCommand) {
    size_t pos = 0;
    string token;
    string delimiter = " ";
    vector<string> tokens;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    tokens.push_back(str);
    if(withCommand){
        id = stoll(tokens[1]);
        plane = tokens[2];
        if(tokens[3].compare("Jet") == 0){
            type = Jet;
        }else if(tokens[3].compare("Cargo") == 0){
            type = Cargo;
        }else if(tokens[3].compare("Airliner") == 0){
            type = Airliner;
        }
        flights = stoull(tokens[4]);
    }else{
        id = stoll(tokens[0]);
        plane = tokens[1];
        if(tokens[2].compare("Jet") == 0){
            type = Jet;
        }else if(tokens[2].compare("Cargo") == 0){
            type = Cargo;
        }else if(tokens[2].compare("Airliner") == 0){
            type = Airliner;
        }
        flights = stoull(tokens[3]);
    }

}

string Plane::toString() const{
    string result;
    result.append(std::to_string(this->id));
    result.append(" ");
    result.append(this->plane);
    result.append(" ");
    if(this->type == Plane::Jet){
        result.append("Jet");
    }else if(this->type == Plane::Cargo){
        result.append("Cargo");
    }else{
        result.append("Airliner");
    }
    result.append(" ");
    result.append(std::to_string(this->flights));
    return result;
}

long long Plane::getId() const {
    return this->id;
}


#endif //AIRPLANEDATABASE_PLANE_HPP
