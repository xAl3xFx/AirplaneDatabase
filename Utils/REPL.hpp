//
// Created by Alex on 23.12.2019.
//

#ifndef AIRPLANEDATABASE_REPL_HPP
#define AIRPLANEDATABASE_REPL_HPP

#include "CommandDispatcher.hpp"
#include "Validator.hpp"
#include <string>

using namespace std;

class REPL{
public:
    void run();
};

void REPL::run(){
    cout << "Welcome to the Zoo!" << endl;

    string command = "";
    string commandStr = "";
    CommandDispatcher cd = *(CommandDispatcher::getInstance());
    while(command.compare("exit") != 0){
        cout << endl;
        cout << "Choose one of the following commands:" << endl;
        cout << "'create ID Type Plane Flights' - Create new Plane." << endl;
        cout << "'delete ID' - Deletes Plane with ID." << endl;
        cout << "'update ID [Id, Type, Plane, Flights] new_value' - Updates plane with ID, sets attribute's value to new_value." << endl;
        cout << "'show offset limit - Shows 'limit' full records starting from the first + 'offset' record. " << endl;
        cout << "'exit' - Exit from the database." << endl;
        commandStr = Validator::getInstance()->validateCommand();
        std::string delimiter = " ";
        command = commandStr.substr(0, commandStr.find(delimiter));
        if(command.compare("create") == 0){
            cd.createPlane(commandStr);
        }else if(command.compare("delete") == 0){
            cd.deletePlane(commandStr);
        }else if(command.compare("update") == 0){
            cd.updatePlane(commandStr);
        }else if(command.compare("show") == 0){
            cd.showOffsetLimit(commandStr);
        }
    }
}

#endif //AIRPLANEDATABASE_REPL_HPP
