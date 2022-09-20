#pragma once
#include <string>
#include <map>
using std::string;
using std::map;

class State {
public:
	State();
	State(string * stateName);
	State(const State& copyState);
	string getStateName();
	State * getTransition(string transitionName);
	map<string, State*> getTransitions();
	void setTransitions(map<string, State*>* transitionsMap);
private:
	string* name;
	map<string, State*>* transitions;
};

class Engine {
public:
	Engine();
	Engine(const Engine& copyEngine);
	State* launchTransitionCommand(string command);
	State* getCurrentState();
	void setCurrentState(State * newState);
private:
	State* currentState;
};