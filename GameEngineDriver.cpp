#include <iostream>
#include <string>
#include "GameEngine.h"
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

int main()
{
	testGameStates();
}