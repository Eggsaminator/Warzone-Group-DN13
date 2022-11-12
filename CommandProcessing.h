#pragma once
#include <map>
#include <queue>
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
    static CommandProcessor* instance(Engine* engine);
    void chooseInputMethod();
    Command* getCommand();
    Command* getCommand(string promptMessage);
protected:
    CommandProcessor(Engine* engine);
    ~CommandProcessor();
    virtual Command* readCommand();
    void saveCommand(Command* command);
    bool inputIsValid(string command, string argument);
    bool validate(State* state, Command* command);
    bool isValid(State* state, Command* command);
    bool isValidInputMethod(string command, string argument);
    Engine* m_engine;
    static map<string, vector<string>> s_commandValidStates;
    vector<Command*> m_commandList;
private:
    static CommandProcessor* s_instance;
};

class Command {
public:
    Command(string command);
    Command(string command, string argument);
    ~Command();
    void execute(Engine* engine);
    string getName();
    string getArgument();
    string getEffect();
    void saveEffect(string effect);
private:
    string m_command;
    string m_argument;
    string m_effect;
};

class FileCommandProcessorAdapter : public CommandProcessor {
public:
    static FileCommandProcessorAdapter* instance(Engine* engine);
    void setFile(string path);
    void processFile();
private:
    FileCommandProcessorAdapter(Engine* engine);
    ~FileCommandProcessorAdapter();
    Command* readCommand();
    queue<string>* readFile(string path);
    static FileCommandProcessorAdapter* s_instance;
    string m_filePath;
    queue<string>* m_fileContents;
};

void testCommandProcessor();