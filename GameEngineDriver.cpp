#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


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

void testMainGameLoop() {
	cout << "-------------------- TEST FOR MAIN GAME LOOP ------------------------" << endl;

	Engine mainEngine = Engine();

	// (1) a player receives the correct number of army units in the reinforcement phase(showing different cases)
	cout << "(1) a player receives the correct number of army units in the reinforcement phase(showing different cases)" << endl;

	vector<Player*> players;
	Player* player1 = new Player("player1");
	Player* player2 = new Player("player2");
	Player* player3 = new Player("player3");

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);

	Continent* continent1 = new Continent("continent1", 1);
	Continent* continent2 = new Continent("continent2", 0);
	Continent* continent3 = new Continent("continent2", 0);

	Territory* terr1 = new Territory("terr1", continent1);
	Territory* terr2 = new Territory("terr2", continent1);
	Territory* terr3 = new Territory("terr3", continent2);
	Territory* terr4 = new Territory("terr4", continent2);
	Territory* terr5 = new Territory("terr5", continent3);
	Territory* terr6 = new Territory("terr6", continent3);


	continent1->addTerritory(terr1);
	continent1->addTerritory(terr2);
	continent2->addTerritory(terr3);
	continent2->addTerritory(terr4);
	continent3->addTerritory(terr5);
	continent3->addTerritory(terr6);

	player1->addTerritory(terr1);
	player1->addTerritory(terr2);
	player1->addTerritory(terr3);
	player2->addTerritory(terr4);
	player2->addTerritory(terr5);
	player3->addTerritory(terr6);

	Map gameMap;
	gameMap.addContinent(continent1);
	gameMap.addContinent(continent2);
	gameMap.addContinent(continent3);

	mainEngine.setMyMap(&gameMap);
	mainEngine.setMyPlayers(players);

	mainEngine.reinforcementPhase();

	for (int i = 0; i < players.size(); i++) {
		cout << "Player " << players[i]->getName() << " has " << players[i]->getTerritories().size() << " territories." << endl;

		//create a map of qty of territories owned by continents
		map<string, int> qtyTerritoriesOwnedByContinents;
		for (Territory* territoryPtr : players[i]->getTerritories()) {
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
			Continent* continentPtr = gameMap.getContinentByName(continentName);
			if (continentPtr != nullptr) {
				if (continentPtr->getTerritories().size() == nbTerritories) {
					cout << "He owns the " << continentPtr->getName() << "(" << continentPtr->getBonusValue() << " bonus) continent.";
				}
			}
		}

		cout << "\n\n";

	}
	cout << "\n\n\n\n";


	//issue with driver line 149(?) toDefend().size() is 0 overloading randomToDefendIndex


	// (2) a player will only issue deploy orders and no other kind of orders if they still have army units in their reinforcement pool 
	cout << "(2) a player will only issue deploy orders and no other kind of orders if they still have army units in their reinforcement pool:" << endl;
	
	cout << "Player " << player1->getName() << " has " << player1->getReinforcementPoolLeftToDeploy() << " army units in his reinforcement pool." << endl;
	cout << "Issuing an Advance order... " << endl;
	player1->issueOrder(player1, "Advance");
	cout << "Qantity of orders in orderslist after issuing an Advance order: " << player1->getOrdersList()->orders.size() << endl;
	player1->issueOrder(player1, "Deploy");
	cout << "Qantity of orders in orderslist after issuing a Deploy order with all army units: " << player1->getOrdersList()->orders.size() << endl;
	player1->issueOrder(player1, "Advance");
	cout << "Qantity of orders in orderslist after issuing an Advance order: " << player1->getOrdersList()->orders.size() << endl;

	cout << "\n\n\n\n";

	// (3) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists 
	cout << "(3) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists:" << endl;

	cout << "Player " << player1->getName() << " issues an Advance order. According to the toAttack() method, he will attack the " << player1->toAttack()[0]->getName() << " territory." << endl;
	cout << "Player " << player1->getName() << " issues an Advance order. According to the toDefend() method, he will defend: " << player1->toDefend()[0]->getName() << " territory." << endl;

	cout << "\n\n\n\n";

	// (4) a player can play cards to issue orders 
	cout << "(4) a player can play cards to issue orders:" << endl;
	
	cout << "Adding a Bomb card to " << player1->getName() << "..." << endl;
	player1->getHand()->add_card(new Card("Bomb", nullptr, nullptr));
	cout << player1->getName() << " plays the Bomb card... " << endl;
	player1->getHand()->hand_content[0]->play();

	cout << "\n\n\n\n";

	// (5) a player that does not control any territory is removed from the game
	cout << "(5) a player that does not control any territory is removed from the game:" << endl;

	cout << "Player player3 has " << player3->getTerritories().size() << " territory and the game has XXX players." << endl;
	mainEngine.gameLoopWinnerLoserCheckup();
	cout << "After running the game loop checkup, the game has XXX players." << endl;
	player3->setTerritories(vector<Territory*>{});
	cout << "player3 gets his territory removed...";
	cout << "Player player3 has " << player3->getTerritories().size() << " territory and the game has XXX players." << endl;
	mainEngine.gameLoopWinnerLoserCheckup();
	cout << "After running the game loop checkup, the game has XXX players." << endl;

	cout << "\n\n\n\n";

	// (6) the game ends when a single player controls all the territories
	cout << "(6) the game ends when a single player controls all the territories:" << endl;

	cout << "Player player2 gets his territory removed...";
	cout << "Player player2 has " << player2->getTerritories().size() << " territory and the game has XXX players." << endl;
	mainEngine.gameLoopWinnerLoserCheckup();
	cout << "After running the game loop checkup, the game has XXX players." << endl;
	cout << "The winner is player " << players[0]->getName() << "!" << endl;
}