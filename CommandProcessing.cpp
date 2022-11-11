#include <iostream>
#include "CommandProcessing.h"


//
CommandProcessor::CommandProcessor() {

}

CommandProcessor::~CommandProcessor() {

}

CommandProcessor* CommandProcessor::instance() {
    if (!s_instance)
        s_instance = new CommandProcessor();
    return s_instance;
}

CommandProcessor* CommandProcessor::s_instance = 0;

map<string, vector<string>> CommandProcessor::s_commandValidStates = {
    {"loadmap", {"start", "maploaded"}},
    {"validatemap", {"maploaded"}},
    {"addplayer", {"mapvalidated", "playersadded"}},
    {"gamestart", {"playersadded"}},
    {"replay", {"win"}},
    {"quit", {"win"}}
};

Command* CommandProcessor::getCommand(State* state) {
    Command* command = readCommand();
    saveCommand(command);
    validate(state, command);
    return command;
}

Command* CommandProcessor::getCommand(State* state, string promptMessage) {
    cout << promptMessage << endl;
    return getCommand(state);
}

bool CommandProcessor::inputIsValid(string command, string argument) {
    // Ensure command exists
    if (!s_commandValidStates.count(command)) {
        return false;
    }

    if ((command.compare("loadmap") == 0)
        || (command.compare("addplayer") == 0)) {
        return (argument.compare("") != 0);
    } else {
        return (argument.compare("") == 0);
    }
}

void CommandProcessor::validate(State* state, Command* command) {
    if (!isValid(state, command))
    {
        command->saveEffect("Error! This command " + command->getName() + " is invalid in the current GameState " + state->getStateName() + "!");
    }
}

bool CommandProcessor::isValid(State* state, Command* command) {
    // Ensure command name exists
    bool commandExists = false;
    map<string, vector<string>>::iterator commandIterator;
    for (commandIterator = s_commandValidStates.begin(); commandIterator != s_commandValidStates.end(); commandIterator++) {
        if (commandIterator->first.compare(command->getName()) == 0) {
            commandExists = true;
            break;
        }
    }
    if (!commandExists) {
        return false;
    }

    vector<string> validPair = (*commandIterator).second;
    // Check if command matches any of the valid states
    for (vector<string>::iterator it = validPair.begin(); it != validPair.end(); it++) {
        if (it->compare(state->getStateName()) == 0) {
            return true;
        }
    }

    return false;
}

Command* CommandProcessor::readCommand() {
    string userInput;
    string cmd;
    string argument;

    do {
        cout << "Please enter a valid command:" << endl;
        getline(cin, userInput);
        int delimiterIndex = userInput.find(' ');

        cmd = userInput.substr(0, delimiterIndex);
        argument = (delimiterIndex != string::npos) ? userInput.substr(delimiterIndex + 1, userInput.length()) : "";

        cout << "Command: " << cmd << endl;
        cout << "Argument: " << ((argument.compare("") != 0) ? argument : "None") << endl;
    } while (!inputIsValid(cmd, argument));

    return new Command(cmd, argument);
}

void CommandProcessor::saveCommand(Command* command) {
    m_commandList.push_back(command);
}

//
Command::Command(string command) {
    m_command = command;
    m_argument = "";
    m_effect = "";
}

Command::Command(string command, string argument) {
    m_command = command;
    m_argument = argument;
    m_effect = "";
}

Command::~Command() {

}

string Command::getName() {
    return m_command;
}

string Command::getArgument() {
    return m_argument;
}

string Command::getEffect() {
    return m_effect;
}

void Command::saveEffect(string effect) {
    m_effect = effect;
}

//
FileCommandProcessorAdapter::FileCommandProcessorAdapter() {

}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {

}