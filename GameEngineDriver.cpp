#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "CommandProcessing.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;


void testGameStates() {
	Engine mainEngine = Engine();
	State* currentState = mainEngine.getCurrentState();

	while (currentState->getStateName() != "end") {
		cout << "Current state: " << currentState->getStateName() << endl;

		//build string listing all possible commands from the current state
		map<string, State*>::iterator itr;
		string possibleCommandsString = "";
		map<string, State*> transitions = currentState->getTransitions();
		for (itr = transitions.begin(); itr != transitions.end(); itr++) {
			possibleCommandsString.append(itr->first);
			possibleCommandsString += ", ";
		}
		if (possibleCommandsString != "") {
			possibleCommandsString = possibleCommandsString.substr(0, possibleCommandsString.size() - 2);
			cout << "Enter a command [" + possibleCommandsString + "]: ";
		}

		//accept next command
		string newCommand;
		cin >> newCommand;

		//trigger state transition from new command
		State* newState = mainEngine.launchTransitionCommand(newCommand);
		if (!newState) {
			cout << endl << "Unknown command entered, please try again." << endl;
		}
		else
		{
			currentState = newState;
		}

		cout << endl;
	}
}

void testStartupPhase()
{
	cout<<"Demonstration of the start up phase"<<endl;

	// really not sure on that part ^^' 
	static CommandProcessor* mCommandProcessor;
	mCommandProcessor=CommandProcessor.instance();
	Engine mEngine;
	mEngine.startupPhase(mCommandProcessor);
	vector<Player*> myListPlayer=mEngine.getPlayers();
	Hand * myHand;
	vector<Territory*> myTerr;
	for(int i=0;i<size(myListPlayer);i++)
	{
		cout <<"Player "<<i<<" :"<<myListPlayer[i]->getName()<<endl;
		myHand=myListPlayer[i]->getHand();
		myHand->display();
		myTerr=myListPlayer[i]->getTerritories();
		cout<<"number of owned territories :"<<myTerr.size()<<endl;
		cout<<"The reinforcement pool of the player contains : "<<myListPlayer[i]->getReinforcementPool()<< " army."<<endl;

	}
	
	
}

int main()
{
	//testGameStates();
	testStartupPhase();
}