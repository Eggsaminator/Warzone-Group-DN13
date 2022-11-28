#pragma once
#include <map>
#include <queue>
#include <string>
#include <vector>
#include "GameEngine.h"
#include "LoggingObesrver.h"

using namespace std;

// Forward declarations

class CommandProcessor;
class Command;
class FileCommandProcessorAdapter;
class Engine;
class State;

//

class CommandProcessor : public ILoggable, public Subject {
public:
    CommandProcessor(Engine* engine);
    ~CommandProcessor();
    void chooseInputMethod();
    Command* getCommand();
    Command* getCommand(string promptMessage);
    Command* getSimpleCommandNoValidation(string promptMessage);
    bool validate(State* state, Command* command);
    void saveCommand(Command* command);
protected:
    virtual Command* readCommand();
    
    string stringToLog();
    bool inputIsValid(string command, string argument);
    bool isValid(State* state, Command* command);
    bool isValidInputMethod(string command, string argument);
    Engine* m_engine;
    static map<string, vector<string>> s_commandValidStates;
    vector<Command*> m_commandList;
private:
    static CommandProcessor* s_instance;
};

class Command : public ILoggable, public Subject  {
public:
    Command(string command);
    Command(string command, string argument);
    ~Command();
    void execute(Engine* engine);
    string getName();
    string getArgument();
    string getEffect();
    void saveEffect(string effect);
    string stringToLog();
private:
    string m_command;
    string m_argument;
    string m_effect;
};

class FileCommandProcessorAdapter : public CommandProcessor {
public:
    FileCommandProcessorAdapter(Engine* engine);
    ~FileCommandProcessorAdapter();
    void setFile(string path);
    void processFile();
private:
    Command* readCommand();
    queue<string>* readFile(string path);
    static FileCommandProcessorAdapter* s_instance;
    string m_filePath;
    queue<string>* m_fileContents;
};

void testCommandProcessor();

extern CommandProcessor* mainCommandProcessor;