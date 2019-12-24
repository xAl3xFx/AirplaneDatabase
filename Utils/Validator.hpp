//
// Created by Alex on 23.12.2019.
//

#ifndef AIRPLANEDATABASE_VALIDATOR_HPP
#define AIRPLANEDATABASE_VALIDATOR_HPP

#include <string>
using namespace std;

class Validator{
private:
    static Validator* instance;
public:
    static Validator* getInstance();

    string validateCommand() const;

    Validator();
};

Validator* Validator::instance = 0;

Validator::Validator(){}

Validator* Validator::getInstance(){
    if (instance == 0){
        instance = new Validator();
    }
    return instance;
}

string Validator::validateCommand() const {
    string command;
    cout << "Enter a command: ";
    getline(cin, command);
    cout << endl;
    std::string delimiter = " ";
    std::string token = command.substr(0, command.find(delimiter)); // token is "scott"
    if(token.compare("create") == 0 || token.compare("exit") == 0 || token.compare("delete") == 0 || token.compare("update") == 0){
        return command;
    }

    cerr << "Invalid command !" << endl;
    return Validator::validateCommand();

}

#endif //AIRPLANEDATABASE_VALIDATOR_HPP
