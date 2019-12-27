//
// Created by Alex on 22.12.2019.
//

#ifndef AIRPLANEDATABASE_DATABASESERVICE_HPP
#define AIRPLANEDATABASE_DATABASESERVICE_HPP

#include "./../Models/Plane.hpp"
#include "./../Models/AVLTree.hpp"
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

    bool optimized;

    BST* tree;

public:

    static DatabaseService* getInstance();

    void createPlane(Plane*);

    void deletePlane(long long);

    void updatePlane(vector<string>);

    void showOffsetLimit(long long, long long);

    void createTree();

    Plane* search(long long);

    ~DatabaseService();
};

DatabaseService* DatabaseService::instance = 0;

DatabaseService::DatabaseService()  : optimized(false), tree(nullptr) {}

DatabaseService* DatabaseService::getInstance(){

    if (instance == 0){
        instance = new DatabaseService();
    }
    return instance;
}

DatabaseService::~DatabaseService(){
    delete tree;
    file.close();
}

bool DatabaseService::exists(long long id) {
    file.open("Planes.db", std::fstream::in);
    string line;
    while (!safeGetline(file, line).eof()){
        if (line.find(to_string(id)) == 0){
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}


void DatabaseService::createPlane(Plane *plane) {
    if(exists(plane->getId())){
        cerr << "A record with ID '" << plane->getId() <<"' already exists!" << endl;
        delete plane;
        return;
    }
    file.open("Planes.db", std::fstream::out | std::fstream::app);
    string planeToStr = plane->toString();
    file << planeToStr << "\r\n";
    file.close();
    delete plane;
    optimized = false;
}

void DatabaseService::deletePlane(long long id) {
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
        cerr << "Invalid ID '" << id <<"' ! No record was deleted!" << endl;
    }

    string path = "Planes.db";
    const char * p = path.c_str(); // required conversion for remove and rename functions
    remove(p);
    rename("Temp.db", p);
    optimized = false;
}

void DatabaseService::updatePlane(vector<string> tokens) {
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
            }else if(tokens[1].compare("Type") == 0){
                oFile << tokens[0] << " " <<  tokens[2] << " " << lineTokens[2] << " " << lineTokens[3] << "\r\n";
            }else if(tokens[1].compare("Name") == 0){
                oFile << tokens[0] << " " <<  lineTokens[1] << " " << tokens[2] << " " << lineTokens[3] << "\r\n";
            }else if(tokens[1].compare("Flights") == 0){
                oFile << tokens[0] << " " <<  lineTokens[1] << " " << tokens[2] << " " << tokens[2] << "\r\n";
            }else{
                cerr << "Invalid attribute: " << tokens[1] << " !" << endl;
            }
        }
    }


    oFile.close();
    file.close();

    if(!exists){
        cerr << "Invalid ID '" << tokens[0] << "' ! No record was updated!" << endl;
    }else {

    }

    string path = "Planes.db";
    const char * p = path.c_str(); // required conversion for remove and rename functions
    remove(p);
    rename("Temp.db", p);
    optimized = false;
}

void DatabaseService::showOffsetLimit(long long offset, long long limit) {
    file.open("Planes.db", std::fstream::in);
    string line;
    int counter = 0;
    //TODO: Validate offset, limit >= 0
    while (!safeGetline(file, line).eof() && limit >0) {
        if(counter >= offset){
            cout << line << endl;
            limit--;
        }
        counter++;
    }
    file.close();
}

void DatabaseService::createTree() {
    BST* t = new BST();
    file.open("Planes.db", std::fstream::in);
    string line;
    while (!safeGetline(file, line).eof()){
        Plane *p = new Plane(line, false);
        t->insert(p);
    }
    this->tree = t;
    optimized = true;
}

Plane* DatabaseService::search(long long id) {
    if(optimized){
        return tree->find(id);
    }else{
        if(!exists(id)){
            return nullptr;
        }
        file.open("Planes.db", std::fstream::in);
        string line;
        string planeStr = "";
        while (!safeGetline(file, line).eof()) {
            if (line.find(to_string(id)) == 0){
                planeStr = line;
                break;
            }
        }

        file.close();
        Plane* plane = new Plane(planeStr, false);
        return plane;
    }
}

#endif //AIRPLANEDATABASE_DATABASESERVICE_HPP
