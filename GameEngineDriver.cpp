#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "CommandProcessing.h"
#include <set>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void testMainGameLoop() {
	cout << "\n\n\n-------------------- TEST FOR MAIN GAME LOOP ------------------------\n" << endl;

	Engine mainEngine = Engine();

	vector<Player*> players;
	Player* player1 = new Player("player1");
	Player* player2 = new Player("player2");
	Player* player3 = new Player("player3");

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);

	Continent* continent1 = new Continent("continent1", 10);
	Continent* continent2 = new Continent("continent2", 3);
	Continent* continent3 = new Continent("continent3", 1);

	Territory* terr1 = new Territory("terr1", continent1);
	Territory* terr2 = new Territory("terr2", continent1);
	Territory* terr2_1 = new Territory("terr2_1", continent1);
	Territory* terr3 = new Territory("terr3", continent2);
	Territory* terr4 = new Territory("terr4", continent2);
	Territory* terr4_1 = new Territory("terr4_1", continent2);
	Territory* terr4_2 = new Territory("terr4_2", continent2);
	Territory* terr4_3 = new Territory("terr4_3", continent2);
	Territory* terr4_4 = new Territory("terr4_4", continent2);
	Territory* terr4_5 = new Territory("terr4_5", continent2);
	Territory* terr4_6 = new Territory("terr4_6", continent2);
	Territory* terr4_7 = new Territory("terr4_7", continent2);
	Territory* terr4_8 = new Territory("terr4_8", continent2);
	Territory* terr4_9 = new Territory("terr4_9", continent2);
	Territory* terr4_10 = new Territory("terr4_10", continent2);
	Territory* terr4_11 = new Territory("terr4_11", continent2);
	Territory* terr5 = new Territory("terr5", continent3);
	Territory* terr6 = new Territory("terr6", continent3);

	terr1->addAdjacency(terr4_4);
	terr4_4->addAdjacency(terr1);
	terr2->addAdjacency(terr4_7);
	terr4_7->addAdjacency(terr2);

	player1->addTerritory(terr1);
	player1->addTerritory(terr2);
	player1->addTerritory(terr2_1);
	player1->addTerritory(terr3);
	player2->addTerritory(terr4);
	player2->addTerritory(terr4_1);
	player2->addTerritory(terr4_2);
	player2->addTerritory(terr4_3);
	player2->addTerritory(terr4_4);
	player2->addTerritory(terr4_5);
	player2->addTerritory(terr4_6);
	player2->addTerritory(terr4_7);
	player2->addTerritory(terr4_8);
	player2->addTerritory(terr4_9);
	player2->addTerritory(terr4_10);
	player2->addTerritory(terr4_11);
	player2->addTerritory(terr5);
	player3->addTerritory(terr6);

	Map gameMap;
	gameMap.addContinent(continent1);
	gameMap.addContinent(continent2);
	gameMap.addContinent(continent3);

	mainEngine.setMyMap(&gameMap);
	mainEngine.setMyPlayers(players);

	mainEngine.reinforcementPhase();

	

	// (1) a player receives the correct number of army units in the reinforcement phase(showing different cases)
	cout << "(1) a player receives the correct number of army units in the reinforcement phase (showing different cases)\nAt startup phase:" << endl;

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
				cout << "He owns " << nbTerritories << " territories in the "  << continentName << " continent. ";
				if (continentPtr->getTerritories().size() == nbTerritories) {
					cout << "He owns the continent (bonus of " << continentPtr->getBonusValue() << ").";
				}
			}
			cout << "\n";
		}

		cout << "He has " << players[i]->getReinforcementPool() << " armies in his reinforcement pool." <<endl;

		cout << "\n";

	}
	cout << "\n\n";


	//issue with driver line 149(?) toDefend().size() is 0 overloading randomToDefendIndex


	// (2) a player will only issue deploy orders and no other kind of orders if they still have army units in their reinforcement pool 
	cout << "(2) a player will only issue deploy orders and no other kind of orders if they still have army units in their reinforcement pool:" << endl;
	
	//set the toDefend, toAttack lists, and reinforcementLeftToDeploy of every player
	auto iterator = players.begin();
	while (iterator != players.end()) {
		(*iterator)->setReinforcementPoolLeftToDeploy((*iterator)->getReinforcementPool());

		vector<Territory*> ownedTerritories = (*iterator)->getTerritories();
		(*iterator)->setTerritoriesToDefend(ownedTerritories);

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
			if ((*territoryIteratorSet)->getOwner() != (*iterator)) {
				territoriesToAttack.push_back(*territoryIteratorSet);
			}
			++territoryIteratorSet;
		}
		(*iterator)->setTerritoriesToAttack(territoriesToAttack);

		++iterator;
	}

	cout << "Player " << player1->getName() << " has " << player1->getReinforcementPoolLeftToDeploy() << " army units in his reinforcement pool." << endl;
	cout << "Issuing an Advance order... " << endl;
	player1->issueOrder(player1, players, "Advance");
	cout << "Qantity of orders in orderslist after issuing an Advance order: " << player1->getOrdersList()->orders.size() << endl;
	cout << "Number of army units left to deploy: "<< player1->getReinforcementPoolLeftToDeploy() << endl;
	player1->issueOrder(player1, players, "Deploy");
	cout << "Qantity of orders in orderslist after issuing a Deploy order: " << player1->getOrdersList()->orders.size() << endl;
	cout << "Number of army units left to deploy: " << player1->getReinforcementPoolLeftToDeploy() << endl;
	player1->issueOrder(player1, players, "Deploy");
	cout << "Qantity of orders in orderslist after issuing a Deploy order: " << player1->getOrdersList()->orders.size() << endl;
	cout << "Number of army units left to deploy: " << player1->getReinforcementPoolLeftToDeploy() << endl;
	player1->issueOrder(player1, players, "Deploy");
	cout << "Qantity of orders in orderslist after issuing a Deploy order: " << player1->getOrdersList()->orders.size() << endl;
	cout << "Number of army units left to deploy: " << player1->getReinforcementPoolLeftToDeploy() << endl;
	player1->issueOrder(player1, players, "Deploy");
	cout << "Qantity of orders in orderslist after issuing a Deploy order: " << player1->getOrdersList()->orders.size() << endl;
	cout << "Number of army units left to deploy: " << player1->getReinforcementPoolLeftToDeploy() << endl;
	player1->issueOrder(player1, players, "Deploy");
	cout << "Qantity of orders in orderslist after issuing a Deploy order: " << player1->getOrdersList()->orders.size() << endl;
	cout << "Number of army units left to deploy: " << player1->getReinforcementPoolLeftToDeploy() << endl;
	player1->issueOrder(player1, players, "Deploy");
	cout << "Qantity of orders in orderslist after issuing a Deploy order: " << player1->getOrdersList()->orders.size() << endl;
	cout << "Number of army units left to deploy: " << player1->getReinforcementPoolLeftToDeploy() << endl;
	player1->issueOrder(player1, players, "Deploy");
	cout << "Qantity of orders in orderslist after issuing a Deploy order: " << player1->getOrdersList()->orders.size() << endl;
	cout << "Number of army units left to deploy: " << player1->getReinforcementPoolLeftToDeploy() << endl;
	player1->issueOrder(player1, players, "Advance");
	cout << "Qantity of orders in orderslist after issuing an Advance order: " << player1->getOrdersList()->orders.size() << endl;

	cout << "\n\n\n";

	// (3) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists 
	cout << "(3) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists:" << endl;

	cout << "toDefend() = ["<< player1->toDefend()[0]->getName();
	for (int i = 1; i < player1->toDefend().size();i++) {
		cout << ", " << player1->toDefend()[i]->getName();
	}
	cout << "]" << endl;

	cout << "toAttack() = [" << player1->toAttack()[0]->getName();
	for (int i = 1; i < player1->toAttack().size(); i++) {
		cout << ", " << player1->toAttack()[i]->getName();
	}
  cout << "]" << endl;

	cout << "Player " << player1->getName() << " issues an Advance order. According to the toAttack() method, he will attack: " << player1->toAttack()[0]->getName() << " territory." << endl;
	cout << "Player " << player1->getName() << " issues an Advance order. According to the toDefend() method, he will defend: " << player1->toDefend()[2]->getName() << " territory." << endl;

	cout << "\n\n\n";

	// (4) a player can play cards to issue orders 
	cout << "(4) a player can play cards to issue orders:" << endl;
	
	cout << "Adding a Bomb card to " << player1->getName() << "'s hand..." << endl;
	Card* newCard = new Card("Bomb", nullptr, nullptr);
	Deck* newDeck = new Deck();
	Hand* newHand = new Hand();
	newHand->setPlayer(player1);
	player1->setHand(newHand);
	newCard->setDeck(newDeck);
	newCard->setHand(newHand);
	player1->getHand()->add_card(newCard);
	cout << player1->getName() << " plays the Bomb card... " << endl;
	player1->getHand()->hand_content[0]->play(players);

	cout << "\n\n\n";

	// (5) a player that does not control any territory is removed from the game
	cout << "(5) a player that does not control any territory is removed from the game:" << endl;

	cout << "Player player3 has " << player3->getTerritories().size() << " territory and the game has " << players.size() << " players." << endl;
	mainEngine.gameLoopWinnerLoserCheckup();
	cout << "After running the game loop checkup, the game has " << players.size() << " players." << endl;
	player3->setTerritories(vector<Territory*>{});
	cout << "player3 has lost all his territories..." << endl;
	cout << "Player player3 has " << player3->getTerritories().size() << " territory and the game has " << players.size() << " players." << endl;
	mainEngine.gameLoopWinnerLoserCheckup();
	cout << "After running the game loop checkup, the game has " << mainEngine.getPlayers().size() << " players." << endl;

	cout << "\n\n\n";

	// (6) the game ends when a single player controls all the territories
	cout << "(6) the game ends when a single player controls all the territories:" << endl;

	cout << "The game has " << mainEngine.getPlayers().size() << " players." << endl;
	cout << "Player player2 has lost all his territories..." << endl;
	player2->setTerritories(vector<Territory*>{});
	cout << "Player player2 has " << player2->getTerritories().size() << " territories and the game has " << mainEngine.getPlayers().size() << " players." << endl;
	
	player1->addTerritory(terr4);
	player1->addTerritory(terr4_1);
	player1->addTerritory(terr4_2);
	player1->addTerritory(terr4_3);
	player1->addTerritory(terr4_4);
	player1->addTerritory(terr4_5);
	player1->addTerritory(terr4_6);
	player1->addTerritory(terr4_7);
	player1->addTerritory(terr4_8);
	player1->addTerritory(terr4_9);
	player1->addTerritory(terr4_10);
	player1->addTerritory(terr4_11);
	player1->addTerritory(terr5);
	player1->addTerritory(terr6);
	mainEngine.gameLoopWinnerLoserCheckup();
}

void testStartupPhase()
{
	cout<<"Demonstration of the start up phase"<<endl;

	Engine* mEngine = new Engine();
	CommandProcessor* mCommandProcessor = new CommandProcessor(mEngine);
	mEngine->startupPhase(mCommandProcessor);
	vector<Player*> myListPlayer=mEngine->getPlayers();
	Hand * myHand;
	vector<Territory*> myTerr;
	for (int i = 0; i < size(myListPlayer); i++)
	{
		cout << "Player " << i << " :" << myListPlayer[i]->getName() << endl;
		myHand = myListPlayer[i]->getHand();
		myHand->display();
		myTerr = myListPlayer[i]->getTerritories();
		cout << "number of owned territories :" << myTerr.size() << endl;
		cout << "The reinforcement pool of the player contains : " << myListPlayer[i]->getReinforcementPool() << " army." << endl;
	}
}