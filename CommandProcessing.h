#pragma once
#include <map>
#include <string>
#include <vector>
#include "GameEngine.h"

using namespace std;

// Forward declarations

class CommandProcessor;
class Command;
class FileCommandProcessorAdapter;

//

class CommandProcessor {
public:
    static CommandProcessor* instance();
    Command* getCommand(State* state);
    Command* getCommand(State* state, string promptMessage);
private:
    CommandProcessor();
    ~CommandProcessor();
    Command* readCommand();
    void saveCommand(Command* command);
    bool inputIsValid(string command, string argument);
    void validate(State* state, Command* command);
    bool isValid(State* state, Command* command);
    static CommandProcessor* s_instance;
    static map<string, vector<string>> s_commandValidStates;
    vector<Command*> m_commandList;
};

class Command {
public:
    Command(string command);
    Command(string command, string argument);
    ~Command();
    string getName();
    string getArgument();
    string getEffect();
    void saveEffect(string effect);
private:
    string m_command;
    string m_argument;
    string m_effect;
};

class FileCommandProcessorAdapter {
public:
    FileCommandProcessorAdapter();
    ~FileCommandProcessorAdapter();
    // Should read from a text file, using the Adapter design pattern
private:

};