//
// Created by Alex on 22.12.2019.
//

#ifndef AIRPLANEDATABASE_DATABASESERVICE_HPP
#define AIRPLANEDATABASE_DATABASESERVICE_HPP

#include "./../Models/Plane.hpp"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Function needed to correctly read lines.
std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();
    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
            case '\n':
                return is;
            case '\r':
                if(sb->sgetc() == '\n')
                    sb->sbumpc();
                return is;
            case std::streambuf::traits_type::eof():
                if(t.empty())
                    is.setstate(std::ios::eofbit);
                return is;
            default:
                t += (char)c;
        }
    }
}


class DatabaseService{
    fstream file;

    static DatabaseService* instance;

    DatabaseService();

    bool exists(long long id);

    //void printAnimalsList();

public:

    static DatabaseService* getInstance();

    void createPlane(Plane*);

    void deletePlane(long long id);

    void updatePlane(vector<string>);

    ~DatabaseService();
};

DatabaseService* DatabaseService::instance = 0;

DatabaseService::DatabaseService(){}

DatabaseService* DatabaseService::getInstance(){

    if (instance == 0){
        instance = new DatabaseService();
    }
    return instance;
}

DatabaseService::~DatabaseService(){
    file.close();
}

bool DatabaseService::exists(long long id) {
    file.open("Planes.db", std::fstream::in);
    string line;
    while (!safeGetline(file, line).eof())
        if (line.find(to_string(id)) == 0)
            return true;
    return false;
}


void DatabaseService::createPlane(Plane *plane) {
    //TODO: Check if 'id' of the plane exists and validate.
    if(exists(plane->getId())){
        //TODO: handle plane id already exists
    }
    file.open("Planes.db", std::fstream::out | std::fstream::app);
    string planeToStr = plane->toString();
    file << planeToStr << "\r\n";
    file.close();
    delete plane;
}

void DatabaseService::deletePlane(long long id) {
    //TODO: Check if 'id' exists and validate.
    //Not using exists() for optimization purposes.
    bool exists = false;
    file.open("Planes.db", std::fstream::in);
    fstream oFile("Temp.db", std::fstream::out | std::fstream::app);

    string line;

    while (!safeGetline(file, line).eof()) {
        if (line.find(to_string(id)) != 0){
            oFile << line << "\r\n";
        }else{
            exists = true;
        }
    }


    oFile.close();
    file.close();

    if(!exists){
        //TODO: Handle id doesn't exist.
    }

    string path = "Planes.db";
    const char * p = path.c_str(); // required conversion for remove and rename functions
    remove(p);
    rename("Temp.db", p);
}

void DatabaseService::updatePlane(vector<string> tokens) {
    /// 0 - ID
    /// 1 - Attribute
    /// 2 - New value
    //TODO: Check if 'id' exists and validate.
    //Not using exists() for optimization purposes.
    bool exists = false;
    file.open("Planes.db", std::fstream::in);
    fstream oFile("Temp.db", std::fstream::out | std::fstream::app);

    string line;

    while (!safeGetline(file, line).eof()) {
        if (line.find(tokens[0]) != 0){
            oFile << line << "\r\n";
        }else{
            exists = true;
            size_t pos = 0;
            string token;
            string delimiter = " ";
            vector<string> lineTokens;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                lineTokens.push_back(token);
                line.erase(0, pos + delimiter.length());
            }
            ///Line tokens:
            /// 0 - Id
            /// 1 - Type
            /// 2 - Name
            /// 3 - Flights
            lineTokens.push_back(line);
            if(tokens[1].compare("Id") == 0){
                oFile << tokens[2] << " " <<  lineTokens[1] << " " << lineTokens[2] << " " << lineTokens[3] << "\r\n";
            }else{
                //TODO: handle invalid attribute
            }
        }
    }


    oFile.close();
    file.close();

    if(!exists){
        //TODO: Handle id doesn't exist.
    }

    string path = "Planes.db";
    const char * p = path.c_str(); // required conversion for remove and rename functions
    remove(p);
    rename("Temp.db", p);


}


#endif //AIRPLANEDATABASE_DATABASESERVICE_HPP
