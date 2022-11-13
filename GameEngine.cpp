#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "Cards.h"
#include "Player.h"
#include "Map.h"
#include "set";
using std::ostream;
using std::cin;
using std::cout;
using std::floor;
using std::map;
using std::set;

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

vector<Player*> Engine::getPlayers() {
	return myPlayers;
}

void Engine::setCurrentState(State* newState) {
	currentState = newState;
}

void Engine::setMyMap(Map* map) {
	myMap = map;
}
void Engine::setMyPlayers(vector <Player*> players) {
	myPlayers = players;
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

void Engine::mainGameLoop() {
	int i = 0;
	while (i < 1) {
		//run game loop
		reinforcementPhase();
		issueOrdersPhase();
		executeOrdersPhase();

		gameLoopWinnerLoserCheckup();
	}
}

void Engine::gameLoopWinnerLoserCheckup() {
	//check if a player has no territories owned, then eliminate him
	auto iterator = myPlayers.begin();
	while (iterator != myPlayers.end()) {
		if ((*iterator)->getTerritories().empty()) {
			iterator = myPlayers.erase(iterator);
		}
	}

	//check if a player owns all the territories
	if (myPlayers.size() == 1) {
	}
}

void Engine::reinforcementPhase() {
	for (int index = 0; index < myPlayers.size(); index++) {
		vector<Territory*> ownedTerritories = myPlayers.at(index)->getTerritories();
		int qtyArmyUnits = floor(ownedTerritories.size() / 3);

		//create a map of qty of territories owned by continent 
		map<string, int> qtyTerritoriesOwnedByContinents;
		for (Territory* territoryPtr : ownedTerritories) {
			string continentName = territoryPtr->getContinent()->getName();
			if (qtyTerritoriesOwnedByContinents.find(continentName) == qtyTerritoriesOwnedByContinents.end()) {
				qtyTerritoriesOwnedByContinents[continentName] = 1;
			}
			else {
				int nbTerritoriesInContinent = qtyTerritoriesOwnedByContinents[continentName];
				qtyTerritoriesOwnedByContinents[continentName] = nbTerritoriesInContinent + 1;
			}
		}

		//check if nb of territories owned by continent = max nb territories in continent
		for (map<string, int>::iterator iter = qtyTerritoriesOwnedByContinents.begin(); iter != qtyTerritoriesOwnedByContinents.end(); ++iter)
		{
			string continentName = iter->first;
			int nbTerritories = iter->second;
			Continent* continentPtr = myMap->getContinentByName(continentName);
			if (continentPtr != nullptr) {
				if (continentPtr->getTerritories().size() == nbTerritories) {
					qtyArmyUnits += continentPtr->getBonusValue();
				}
			}
		}

		//minimum nb reinforcement army per turn is 3
		if (qtyArmyUnits < 3) {
			qtyArmyUnits = 3;
		}

		myPlayers.at(index)->setReinforcementPool(myPlayers.at(index)->getReinforcementPool() + qtyArmyUnits);
	}
}

void Engine::issueOrdersPhase() {
	//create list of players index who still want to issue orders
	vector<int> activePlayersIndexes;
	for (int i = 0; i < myPlayers.size(); i++) {
		activePlayersIndexes.push_back(i);
	}

	//set the toDefend, toAttack lists, and reinforcementLeftToDeploy of every player
	auto iterator = activePlayersIndexes.begin();
	while (iterator != activePlayersIndexes.end()) {
		myPlayers.at(*iterator)->setReinforcementPoolLeftToDeploy(myPlayers.at(*iterator)->getReinforcementPool());

		vector<Territory*> ownedTerritories = myPlayers.at(*iterator)->getTerritories();
		myPlayers.at(*iterator)->setTerritoriesToDefend(ownedTerritories);

		set<Territory*> territoriesToAttackSet;
		auto territoryIterator = ownedTerritories.begin();
		while (territoryIterator != ownedTerritories.end()) {
			vector<Territory*> adjacentTerr = (*territoryIterator)->getAdjacencyList();
			for (int i = 0; i < adjacentTerr.size(); i++) {
				territoriesToAttackSet.insert(adjacentTerr[i]);
			}
			++territoryIterator;
		}
		vector<Territory*> territoriesToAttack;
		auto territoryIteratorSet = territoriesToAttackSet.begin();
		while (territoryIteratorSet != territoriesToAttackSet.end()) {
			if ((*territoryIteratorSet)->getOwner() != myPlayers.at(*iterator)) {
				territoriesToAttack.push_back(*territoryIteratorSet);
			}
			++territoryIteratorSet;
		}
		myPlayers.at(*iterator)->setTerritoriesToAttack(territoriesToAttack);

		++iterator;
	}

	while (!activePlayersIndexes.empty()) {
		iterator = activePlayersIndexes.begin();
		while (iterator != activePlayersIndexes.end()) {
			//TODO: get parameters from console
			string randomOrderList[] = { "End", "Deploy", "Advance", "PickCard" };
			string order = randomOrderList[rand() % 4];

			int currentReinforcmentPool = myPlayers.at(*iterator)->getReinforcementPoolLeftToDeploy();

			if (order == "End" && currentReinforcmentPool < 1) {
				//Can only stop issuing orders if all army units have been deployed
				iterator = activePlayersIndexes.erase(iterator);
				continue;
			}
			else if (order == "Advance" || order == "Deploy") {
				myPlayers.at(*iterator)->issueOrder(order);
			}
			else if (order == "PickCard") {
				if (myPlayers.at(*iterator)->getHand()->hand_content.size() > 0) {
					vector<Card*> cardsInHand = myPlayers.at(*iterator)->getHand()->hand_content;
					int randomCardIndex = rand() % cardsInHand.size();
					Card* cardPtr = cardsInHand.at(randomCardIndex);
					cardPtr->play();
				}
			}

			++iterator;
		}
	}
}

void Engine::executeOrdersPhase() {
	//create list of players index who still want to execute order
	vector<int> activePlayersIndexes;
	for (int i = 0; i < myPlayers.size(); i++) {
		activePlayersIndexes.push_back(i);
	}

	//re-run loop until no more active players
	while (!activePlayersIndexes.empty()) {
		auto iterator = activePlayersIndexes.begin();
		//iterate through all active players
		while (iterator != activePlayersIndexes.end()) {
			if (!myPlayers.at(*iterator)->getOrdersList()->orders.empty()) {
				int indexOfDeployOrder = -1;
				int currentIndex = 0;
				for (Orders* orderPtr : myPlayers.at(*iterator)->getOrdersList()->orders) {
					//check if order is a Deploy order
					if (dynamic_cast<Deploy*>(orderPtr) != nullptr) {
						indexOfDeployOrder = currentIndex;
						break;
					}
					else
					{
						currentIndex++;
					}
				}

				//if Deploy order exists in orderList, run it first. Else, run orders in order.
				if (indexOfDeployOrder != -1) {
					myPlayers.at(*iterator)->getOrdersList()->orders.at(indexOfDeployOrder)->execute();
					myPlayers.at(*iterator)->getOrdersList()->remove(indexOfDeployOrder);
				}
				else
				{
					myPlayers.at(*iterator)->getOrdersList()->orders.at(0)->execute();
					myPlayers.at(*iterator)->getOrdersList()->remove(0);
				}
				
				++iterator;
			}
			else 
			{
				iterator = activePlayersIndexes.erase(iterator);
			}
		}
	}
}