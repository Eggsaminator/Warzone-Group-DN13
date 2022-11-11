#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "Cards.h"
#include "Player.h"
#include "Map.h"
#include "CommandProcessing.h"

using std::ostream;
using std::cin;
using std::cout;

//#include "CommandProcessing.h"

class Deck;
class Player;
class Map;

//State methods

State::State() : name(""), transitions(NULL) {

};

State::State(string stateName) : name(stateName), transitions(NULL) {};

//copy constructor
State::State(const State &copyState) {
	name = copyState.name;
	transitions = copyState.transitions;
}

//assignment operator
State& State::operator=(const State& copyState) {
	name = copyState.name;
	transitions = copyState.transitions;
	return *this;
}

//stream insertion operator
ostream& operator << (ostream& o, State& currentState)
{
	//build string listing possible commands from this state
	map<string, State*>::iterator itr;
	string possibleCommandsString = "";
	map<string, State*> transitions = currentState.getTransitions();
	for (itr = transitions.begin(); itr != transitions.end(); itr++) {
		possibleCommandsString.append(itr->first);
		possibleCommandsString += ", ";
	}

	if (possibleCommandsString != "") {
		possibleCommandsString = possibleCommandsString.substr(0, possibleCommandsString.size() - 2);
		o << "State: " << currentState.getStateName() << ". Possible commands: " << possibleCommandsString << ".";
	}
	else 
	{
		o << "State: " << currentState.getStateName() << " (No possible commands)";
	}

	return o;
}

string State::getStateName() {
	return name;
}

State* State::getTransition(string transitionName) {
	if (transitions != NULL) {
		//search for new state given a transition command
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

//copy constructor
Engine::Engine(const Engine& copyEngine) {
	currentState = copyEngine.currentState;
}

//assignment operator
Engine& Engine::operator=(const Engine& copyEngine) {
	currentState = copyEngine.currentState;
	return *this;
}

//stream insertion operator
ostream& operator << (ostream& o, Engine& currentEngine)
{
	o << "Engine's current state: " << currentEngine.getCurrentState()->getStateName();
	return o;
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

Deck* Engine::getDeck(){
	return myDeck;
}

vector<Player*> Engine::getPlayers(){
	return myPlayers;
}

Map* Engine::getMap(){
	return mMap;
}


void Engine::setCurrentState(State* newState) {
	currentState = newState;
}

void Engine::buildLevels() {
	//declare all possible states
	State* state0 = new State("start");

	State* state1 = new State("map loaded");

	State* state2 = new State("map validated");

	State* state3 = new State("players added");

	State* state4 = new State("assign reinforcement");

	State* state5 = new State("issue orders");

	State* state6 = new State("execute orders");

	State* state7 = new State("win");

	State* state8 = new State("end");

	//create maps of possible transitions
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
		{string("gamestart"), state4} //CHANGE!!!!!!!!!! assigncountries
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

void Engine::startupPhase(CommandProcessor* mCommandProcess)
{
State* currentState = this->getCurrentState();
while(this->getCurrentState()->getStateName()!="assign reinforcement")
{
	// we get a new command
	Command mCommand=mCommandProcess->getCommand();

	
	if(
		mCommand.validate()
		)
		string mCommand_name=mCommand.getName();
	// if the command is valid in the current state of the Game Engine then we can apply its effect
	{

	if(mCommand_name.substr(0,7)=="loadmap")
	{
		mCommand_name.pop_back();
		cout <<"loadmap ok\n";
		
		MapLoader* mMapLoader =new MapLoader();
		mMap=new Map(mMapLoader->loadMap(mCommand_name.substr(8,mCommand_name.size()))); //need to get that from the command !
// transition to state map loaded
		this->setCurrentState(this->launchTransitionCommand("loadmap"));

	}
	if(mCommand_name=="validatemap")
	{
		cout<<"validatemap\n";
		if(mMap->validate()){
		//TODO this.launchTransitionCommand("validatemap")
		this->setCurrentState(this->launchTransitionCommand("validatemap"));
		}
	}

	if(mCommand_name.substr(0,9)=="addplayer")
	{
		cout<<"new player !\n";
		mCommand_name.pop_back();
		if(this->getCurrentState()->getStateName()!="players added")
		{
			this->setCurrentState(this->launchTransitionCommand("addplayer"));

		}
		
		myPlayers.push_back(new Player(mCommand_name.substr(10,mCommand_name.size()))); // need to get the name from the command ?

	}

	if(mCommand_name=="gamestart")
	{
		cout<<"let's start\n";
		// have to make somehow the transition to that

		// Game Start
	//fair distribution
	// random order of play
	// 50 army/person
	//2 cards /player

	myDeck=new Deck(50);

	// we get the list of territories
	
	vector <Territory*> list_of_territories=mMap->getTerritories();

	 std::random_shuffle(list_of_territories.begin(), list_of_territories.end());

	// fair distribution of the territories

	for(int j=0;j<size(list_of_territories);j++)
	{
		list_of_territories[j]->setOwner(myPlayers[j%size(myPlayers)]);
		myPlayers[j%size(myPlayers)]->addTerritory(list_of_territories[j]);

	}

	// shuffle order of the player

	 std::random_shuffle(myPlayers.begin(), myPlayers.end());


	 // 50 army in the reinforcement pool of the player


	 // each player shall draw 2 cards

	for(int i=0;i<size(myPlayers);i++)
	{
		Hand* h_p=new Hand();
		h_p->setPlayer(myPlayers[i]);
		myPlayers[i]->setHand(h_p);
		myPlayers[i]->addArmy(50);
		myDeck->draw(h_p);
		myDeck->draw(h_p);

	}

	
this->setCurrentState(this->launchTransitionCommand("gamestart"));

	}
}




}


}

