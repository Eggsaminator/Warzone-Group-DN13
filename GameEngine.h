#pragma once
#include <string>
#include <map>
#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Player.h"
#include "Orders.h"
#include "CommandProcessing.h"
#include "LoggingObesrver.h"
using std::ostream;
using std::string;
using std::map;
using std::vector;

class Player;
class Map;

class CommandProcessor;
class Deck;
class Player;
class Map;

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

class Engine: public ILoggable, public Subject  {
public:
	Engine();
	Engine(const Engine& copyEngine); //copy constructor
	Engine& operator=(const Engine& copyState); //assignment operator
	State* launchTransitionCommand(string command);
	string stringToLog();
	State* getCurrentState();
	Deck* getDeck();
	Map* getMap();
	vector<Player*> getPlayers();
	void setCurrentState(State* newState);
	void mainGameLoop(CommandProcessor* cmdProcessor);
	bool gameLoopWinnerLoserCheckup();
	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	void buildLevels();
	void setMyMap(Map* map);
	void setMyPlayers(vector <Player*> players);
	void startupPhase(CommandProcessor* mCommandProcess);
	void mainTournamentLoop(CommandProcessor* cmdProcessor);
	void replay_game(CommandProcessor* cmdProcess);
	friend ostream& operator << (ostream& o, Engine& currentEngine); //stream insertion operator


private:
	State* currentState;
	Map* myMap;
	Deck* myDeck;
	vector <Player*> myPlayers;
};

void testStartupPhase();
void testMainGameLoop();
