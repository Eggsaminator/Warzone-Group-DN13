#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>
#include <cmath>
#include "Cards.h"
#include "Player.h"
#include "Map.h"
#include "CommandProcessing.h"
#include "PlayerStrategies.h"

using std::ostream;
using std::cin;
using std::cout;
//using std::floor;
using std::map;
using std::set;

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
	new LogObserver(this);
};

//copy constructor
Engine::Engine(const Engine& copyEngine) {
	currentState = copyEngine.currentState;
	new LogObserver(this);
}

//assignment operator
Engine& Engine::operator=(const Engine& copyEngine) {
	currentState = copyEngine.currentState;
	new LogObserver(this);//I think this is necessary here, since you can't copy the _observers
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
		notify(this);
		return newState;
	}
	else
	{
		return nullptr;
	}
}

string Engine::stringToLog(){
	string temp = ("Game Engine new state: " + this->getCurrentState()->getStateName() + "\n");
	return temp;
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
	return myMap;
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

	State* state1 = new State("maploaded");

	State* state2 = new State("mapvalidated");

	State* state3 = new State("playersadded");

	State* state4 = new State("assignreinforcement");

	State* state5 = new State("issueorders");

	State* state6 = new State("executeorders");

	State* state7 = new State("win");

	State* state8 = new State("end");

	//create maps of possible transitions
	map<string, State*>* state0Transitions = new map<string, State*>{
		{string("startup"),state0},
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
	cout<<"startupPhase"<<endl;
	State* currentState = this->getCurrentState();
	
	while(this->getCurrentState()->getStateName()!="assignreinforcement") {
		// we get a new command
		cout<< "state before read is:"<<this->getCurrentState()->getStateName()<<endl;

		Command* mCommand= mCommandProcess->getCommand();
		cout<< "state after read is:"<<this->getCurrentState()->getStateName()<<endl;

		string mCommand_name;
		if(mCommandProcess->validate(getCurrentState(), mCommand) || mCommand->getName()=="gamestart")
			mCommand_name=mCommand->getName();
		// if the command is valid in the current state of the Game Engine then we can apply its effect
		

		if(mCommand_name=="loadmap")
		{
			mCommand_name.pop_back();
			cout <<"loadmap ok\n";
			
			MapLoader* mMapLoader =new MapLoader();
			myMap=new Map(mMapLoader->loadMap(mCommand->getArgument()));
			mCommandProcess->current_map=mCommand->getArgument();
			mCommandProcess->current_map.pop_back();
			mCommandProcess->current_map.pop_back();

			mCommandProcess->current_map.pop_back();
			mCommandProcess->current_map.pop_back();



		// transition to state map loaded
			this->setCurrentState(this->launchTransitionCommand("loadmap"));

		}
		if(mCommand_name=="validatemap")
		{
			cout<<"validatemap\n";
			if(myMap->validate()){
			//TODO this.launchTransitionCommand("validatemap")
			this->setCurrentState(this->launchTransitionCommand("validatemap"));
			}
		}

		if(mCommand_name=="addplayer")
		{
			cout<<"new player !\n";
			mCommand_name.pop_back();
			if(this->getCurrentState()->getStateName()!="playersadded")
			{
				this->setCurrentState(this->launchTransitionCommand("addplayer"));

			}
			
			myPlayers.push_back(new Player(mCommand->getArgument())); // need to get the name from the command ?
			

		}

		if (mCommand_name == "gamestart")
		{
			cout << "let's start\n";
			// have to make somehow the transition to that

			// Game Start
			//fair distribution
			// random order of play
			// 50 army/person
			//2 cards /player

			myDeck = new Deck(50);

			// we get the list of territories

			vector <Territory*> list_of_territories = myMap->getTerritories();

			std::random_shuffle(list_of_territories.begin(), list_of_territories.end());

			// fair distribution of the territories

			for (int j = 0; j < size(list_of_territories); j++)
			{
				list_of_territories[j]->setOwner(myPlayers[j % size(myPlayers)]);
				myPlayers[j % size(myPlayers)]->addTerritory(list_of_territories[j]);

			}

			// shuffle order of the player

			std::random_shuffle(myPlayers.begin(), myPlayers.end());

			//add the player_strategy
			for(int i=0;i<myPlayers.size();i++)
			{
				//HumanPlayerStrategy(Player* p, vector<Player*> allPls, Map* map);
				//AggressivePlayerStrategy(Player* player);
				//BenevolentPlayerStrategy(Player* player);
				//NeutralPlayerStrategy(Player* player);
				//CheaterPlayerStrategy(Player* player);




				string mStrat=myPlayers[i]->getName();
				if(mStrat=="Human")
				{
					PlayerStrategy* mStrategy=new HumanPlayerStrategy(myPlayers[i],myPlayers,this->getMap(), mCommandProcess);
					myPlayers[i]->setPlayerStrategy(mStrategy);
					cout<<"added human"<<endl;

				}
				if(mStrat=="Aggressive")
				{
					PlayerStrategy* mStrategy=new AggressivePlayerStrategy(myPlayers[i]);
					myPlayers[i]->setPlayerStrategy(mStrategy);
					cout<<"added aggressive"<<endl;

				}
				if(mStrat=="Benevolent")
				{
					PlayerStrategy* mStrategy=new BenevolentPlayerStrategy(myPlayers[i]);
					myPlayers[i]->setPlayerStrategy(mStrategy);
					cout<<"added benevolent"<<endl;
					
				}
				if(mStrat=="Neutral")
				{
					PlayerStrategy* mStrategy=new NeutralPlayerStrategy(myPlayers[i]);
					myPlayers[i]->setPlayerStrategy(mStrategy);
					cout<<"added neutral"<<endl;
					
				}
				if(mStrat=="Cheater")
				{
					PlayerStrategy* mStrategy=new CheaterPlayerStrategy(myPlayers[i]);
					myPlayers[i]->setPlayerStrategy(mStrategy);
					cout<<"added cheater"<<endl;
					
				}








			}


			// 50 army in the reinforcement pool of the player


			// each player shall draw 2 cards

			for (int i = 0; i < size(myPlayers); i++)
			{
				Hand* h_p = new Hand();
				h_p->setPlayer(myPlayers[i]);
				myPlayers[i]->setHand(h_p);
				myPlayers[i]->addArmy(50);
				myDeck->draw(h_p);
				myDeck->draw(h_p);

			}

			//this->setCurrentState(this->launchTransitionCommand("gamestart"));
			//cout<<"finished !"<<endl;

			//ADD the main gameLoop function
			
		}

	}
	//cout<<"next step"<<"start main loop"<<endl;
	//cout<<mCommandProcess->getTournament()<<endl;
	bool tour=mCommandProcess->getTournament();
	//cout <<"start main loop";
	//this->mainTournamentLoop(mCommandProcess);
	
	if(tour)
			{
				cout << "entering main loop"<<endl;
				
				this->mainTournamentLoop(mCommandProcess);

			}
			else
			{
				
				this->mainGameLoop(mCommandProcess);
			}
	
	cout<<"exiting startup phase"<<endl;
			
			
}

void Engine::mainTournamentLoop(CommandProcessor* cmdProcessor)
{
	
	int max_D;

	

	ifstream stream;
    stream.open("tournament_report.txt");
	if(stream.is_open()){
    
        string tp;
        getline(stream, tp); //read data from file object and put it into string.
        getline(stream, tp);
        getline(stream, tp);
        getline(stream, tp);
		getline(stream, tp);
        max_D=stoi(tp.substr(tp.length()-3,tp.length()));
	
	}
	else
	{
		cout<<"non existing tournament"<<endl;
	}
	stream.close();

    





	ofstream strm;
	// we open the file at the end of it
	strm.open("tournament_report.txt",ios::app);
	bool isGameOver = false;
	int round_played=0;
	strm<<"Result of this game with map "<<cmdProcessor->current_map<<" :"<<endl;
	while (!isGameOver && round_played<max_D) {
		//run game loop
		//reinforcementPhase();
		//issueOrdersPhase();
		//executeOrdersPhase();
		round_played++;

		isGameOver = gameLoopWinnerLoserCheckup();
	}
	if(isGameOver)
	{
		strm << "THE WINNER IS " << myPlayers.at(0)->getName() << "!!" << endl;
	}
	else
	{
		strm << "It is a drawn !"<<endl;
	}

	//this->setCurrentState(this->launchTransitionCommand("issueorder"));
	//this->setCurrentState(this->launchTransitionCommand("endissueorders"));
	//this->setCurrentState(this->launchTransitionCommand("endexecorders"));
	//this->setCurrentState(this->launchTransitionCommand("win"));
	//cout<<this->getCurrentState()->getStateName();
	
	launchTransitionCommand("issueorder");
	launchTransitionCommand("endissueorders");
	//launchTransitionCommand("executeorders");
	//launchTransitionCommand("endexecorders");

	launchTransitionCommand("win");

	//launchTransitionCommand("play");

	
	
	
	//cout << "Do you want to [quit] or [replay]?" << endl;
	//Command* mCommand = cmdProcessor->getCommand();
	//cout<<"my last command: "<<mCommand->getName()<<endl;
	/*

	bool isCommandValid = false;
	if(mCommand->getName()!="quit")
	{
		launchTransitionCommand("play");
	}

	else
	{
		launchTransitionCommand("quit");
	}
	/*
	while (!isCommandValid) {
		string mCommand_name;
		if (cmdProcessor->validate(getCurrentState(), mCommand)) {
			mCommand_name = mCommand->getName();
		}

		if (mCommand_name == "play") {
			launchTransitionCommand("play");
			//return startupPhase(cmdProcessor);
		}
		else if (mCommand_name == "quit") {
			launchTransitionCommand("end");
			//return;
		}
	}*/

strm.close();
cout <<"exiting main loop "<<endl;

}

void Engine::replay_game(CommandProcessor* cmdProcess)
{
	launchTransitionCommand("play");

}


void Engine::mainGameLoop(CommandProcessor* cmdProcessor) {
	bool isGameOver = false;
	while (!isGameOver) {
		//run game loop
		reinforcementPhase();
		issueOrdersPhase();
		executeOrdersPhase();

		isGameOver = gameLoopWinnerLoserCheckup();
	}
	cout << "THE WINNER IS " << myPlayers.at(0)->getName() << "!!" << endl;
	launchTransitionCommand("win");
	cout << "Do you want to [quit] or [replay]?" << endl;
	Command* mCommand = cmdProcessor->getCommand();

	bool isCommandValid = false;
	while (!isCommandValid) {
		string mCommand_name;
		if (cmdProcessor->validate(getCurrentState(), mCommand)) {
			mCommand_name = mCommand->getName();
		}

		if (mCommand_name == "replay") {
			return startupPhase(cmdProcessor);
		}
		else if (mCommand_name == "quit") {
			return;
		}
	}
}

bool Engine::gameLoopWinnerLoserCheckup() {
	//check if a player has no territories owned, then eliminate him
	auto iterator = myPlayers.begin();
	while (iterator != myPlayers.end()) {
		if ((*iterator)->getTerritories().size() < 1) {
			iterator = myPlayers.erase(iterator);
			continue;
		}
		++iterator;
	}

	//check if a player owns all the territories
	if (myPlayers.size() == 1) {
		int numberTerritoriesOwned = myPlayers.at(0)->getTerritories().size();
		auto allContinents = myMap->getContinents();

		int totalNbTerritories = 0;
		for (int i = 0; i < allContinents.size(); i++) {
			totalNbTerritories += allContinents[i]->getTerritories().size();
		}

		if (totalNbTerritories == numberTerritoriesOwned) {
			return true;
		}
	}

	return false;
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
		++iterator;
	}


	while (!activePlayersIndexes.empty()) {
		iterator = activePlayersIndexes.begin();
		while (iterator != activePlayersIndexes.end()) {
			//int currentReinforcementPool = myPlayers.at(*iterator)->getReinforcementPoolLeftToDeploy();
			OrderList* issuedOrders = myPlayers.at(*iterator)->issueOrder();

			if (issuedOrders == nullptr) {
				iterator = activePlayersIndexes.erase(iterator);
				continue;
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



