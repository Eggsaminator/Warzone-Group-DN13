#pragma once
#include <string>
#include <map>
using std::ostream;
using std::string;
using std::map;

class State {
public:
	State();
	State(string stateName);
	State(const State& copyState); //copy constructor
	State& operator=(const State& copyState); //assignment operator
	string getStateName();
	State* getTransition(string transitionName);
	map<string, State*> getTransitions();
	void setTransitions(map<string, State*>* transitionsMap);
	friend ostream& operator << (ostream& o, State& currentState); //stream insertion operator
private:
	string name;
	map<string, State*>* transitions;
};

class Engine {
public:
	Engine();
	Engine(const Engine& copyEngine); //copy constructor
	Engine& operator=(const Engine& copyState); //assignment operator
	State* launchTransitionCommand(string command);
	State* getCurrentState();
	void setCurrentState(State* newState);
	void mainGameLoop();
	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	void buildLevels();
	friend ostream& operator << (ostream& o, Engine& currentEngine); //stream insertion operator
private:
	State* currentState;
};

void testGameStates();
void testMainGameLoop();