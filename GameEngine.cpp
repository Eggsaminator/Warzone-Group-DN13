#include "GameEngine.h"
#include <iostream>
using std::cin;
using std::cout;

//State methods
State::State() : name(NULL), transitions(NULL) {

};

State::State(string stateName) : name(stateName), transitions(NULL) {};

State::State(const State &copyState) {
	name = copyState.name;
	transitions = copyState.transitions;
}

string State::getStateName() {
	return name;
}

State* State::getTransition(string transitionName) {
	if (transitions != NULL) {
		auto trans = (* transitions).find(transitionName);
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
	buildLevels();
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

void Engine::buildLevels() {
	State* state0 = new State("start");

	State* state1 = new State("map loaded");

	State* state2 = new State("map validated");

	State* state3 = new State("players added");

	State* state4 = new State("assign reinforcement");

	State* state5 = new State("issue orders");

	State* state6 = new State("execute orders");

	State* state7 = new State("win");

	State* state8 = new State("end");

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
}