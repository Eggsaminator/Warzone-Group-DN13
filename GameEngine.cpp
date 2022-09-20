#include "GameEngine.h"
#include <iostream>
using std::cin;
using std::cout;

//State methods
State::State() : name(NULL), transitions(NULL) {

};

State::State(string * stateName) : name(stateName), transitions(NULL) {};

State::State(const State &copyState) {
	name = copyState.name;
	transitions = copyState.transitions;
}

string State::getStateName() {
	return *name;
}

State * State::getTransition(string transitionName) {
	if (transitions != NULL) {
		auto trans = transitions->find(transitionName);
		if (trans == (*transitions).end()) {
			return nullptr;
		}
		else {
			return trans->second;
		}
	}
	else 
	{
		return nullptr;
	}
}

map<string, State*> State::getTransitions() {
	return *transitions;
}

void State::setTransitions(map<string, State*>* transitionsMap) {
	transitions = transitionsMap;
}


//Engine methods
Engine::Engine() {

	string* state0Title = new string("start");
	State* state0 = new State(state0Title);

	string* state1Title = new string("map loaded");
	State* state1 = new State(state1Title);

	string* state2Title = new string("map validated");
	State* state2 = new State(state2Title);

	string* state3Title = new string("players added");
	State* state3 = new State(state3Title);

	string* state4Title = new string("assign reinforcement");
	State* state4 = new State(state4Title);

	string* state5Title = new string("issue orders");
	State* state5 = new State(state5Title);

	string* state6Title = new string("execute orders");
	State* state6 = new State(state6Title);

	string* state7Title = new string("win");
	State* state7 = new State(state7Title);

	string* state8Title = new string("end");
	State* state8 = new State(state8Title);
	
	map<string, State*>* state0Transitions = new map<string, State*>{
		{string("loadmap"), state1}
	};
	state0->setTransitions(state0Transitions);
	
	map<string, State*>* state1Transitions = new map<string, State*>{
		{string("loadmap"), state1},
		{string("validatemap"), state2}
	};
	state1->setTransitions(state1Transitions);

	map<string, State*>* state2Transitions = new map<string, State*>{
		{string("addplayer"), state3}
	};
	state2->setTransitions(state2Transitions);
	
	map<string, State*>* state3Transitions = new map<string, State*>{
		{string("addplayer"), state3},
		{string("assigncountries"), state4}
	};
	state3->setTransitions(state3Transitions);

	map<string, State*>* state4Transitions = new map<string, State*>{
		{string("issueorder"), state5}
	};
	state4->setTransitions(state4Transitions);
	
	map<string, State*>* state5Transitions = new map<string, State*>{
		{string("issueorder"), state5},
		{string("endissueorders"), state6}
	};
	state5->setTransitions(state5Transitions);
	
	map<string, State*>* state6Transitions = new map<string, State*>{
		{string("execorder"), state6},
		{string("endexecorders"), state4},
		{string("win"), state7}
	};
	state6->setTransitions(state6Transitions);
	
	map<string, State*>* state7Transitions = new map<string, State*>{
		{string("play"), state0},
		{string("end"), state8}
	};
	state7->setTransitions(state7Transitions);

	currentState = state0;
};

Engine::Engine(const Engine& copyEngine) {
	currentState = copyEngine.currentState;
}

State* Engine::launchTransitionCommand(string command) {
	State* newState = getCurrentState()->getTransition(command);
	if (newState) {
		currentState = newState;
		return newState;
	}
	else
	{
		return nullptr;
	}
}

State* Engine::getCurrentState() {
	return currentState;
}

void Engine::setCurrentState(State* newState) {
	currentState = newState;
}