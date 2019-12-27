//
// Created by Alex on 23.12.2019.
//

#ifndef AIRPLANEDATABASE_COMMANDDISPATCHER_HPP
#define AIRPLANEDATABASE_COMMANDDISPATCHER_HPP

#include "./../Models/Plane.hpp"
#include "./../Services/DatabaseService.hpp"
#include "./../Models/AVLTree.hpp"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class CommandDispatcher{

    static CommandDispatcher* instance;

    CommandDispatcher();



public:

    static CommandDispatcher* getInstance();

    void createPlane(string command);

    void deletePlane(string command);

    void updatePlane(string command);

    void showOffsetLimit(string command);

    void optimize();

    void search(string command);

    ~CommandDispatcher();
};

CommandDispatcher* CommandDispatcher::instance = 0;

CommandDispatcher::CommandDispatcher(){}

CommandDispatcher* CommandDispatcher::getInstance(){

    if (instance == 0){
        instance = new CommandDispatcher();
    }
    return instance;
}

CommandDispatcher::~CommandDispatcher(){

}

void CommandDispatcher::createPlane(std::string command) {
    DatabaseService* ds = (DatabaseService::getInstance());
    Plane* plane = new Plane(command, true);
    ds->createPlane(plane);
}

void CommandDispatcher::deletePlane(string command) {
    DatabaseService* ds = (DatabaseService::getInstance());
    size_t pos = 0;
    string token;
    string delimiter = " ";
    vector<string> tokens;
    while ((pos = command.find(delimiter)) != std::string::npos) {
        token = command.substr(0, pos);
        tokens.push_back(token);
        command.erase(0, pos + delimiter.length());
    }
    tokens.push_back(command);
    long long id = stoll(tokens[1]);
    ds->deletePlane(id);
}

void CommandDispatcher::updatePlane(string command) {
    DatabaseService* ds = (DatabaseService::getInstance());
    size_t pos = 0;
    string token;
    string delimiter = " ";
    vector<string> tokens;
    while ((pos = command.find(delimiter)) != std::string::npos) {
        token = command.substr(0, pos);
        tokens.push_back(token);
        command.erase(0, pos + delimiter.length());
    }
    tokens.push_back(command);
    tokens.erase(tokens.begin());
    ds->updatePlane(tokens);
}

void CommandDispatcher::showOffsetLimit(string command) {
    DatabaseService* ds = (DatabaseService::getInstance());
    long long offset, limit;
    size_t pos = 0;
    string token;
    string delimiter = " ";
    vector<string> tokens;
    while ((pos = command.find(delimiter)) != std::string::npos) {
        token = command.substr(0, pos);
        tokens.push_back(token);
        command.erase(0, pos + delimiter.length());
    }
    tokens.push_back(command);
    offset = stoll(tokens[1]);
    limit = stoll(tokens[2]);
    ds->showOffsetLimit(offset, limit);
}

void CommandDispatcher::optimize() {
    DatabaseService* ds = (DatabaseService::getInstance());
    ds->createTree();
}

void CommandDispatcher::search(string command) {
    long long id = stoll(command.substr(command.find(" "), command.length() -1));
    DatabaseService* ds = (DatabaseService::getInstance());
    Plane* plane = ds->search(id);
    if(plane)
        cout << plane->toString();
    else
        cerr << "Plane with id '" << id << "' was not found!";
}

#endif //AIRPLANEDATABASE_COMMANDDISPATCHER_HPP
