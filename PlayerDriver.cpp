#include "Player.h"
#include <iostream>
using namespace std;


void testPlayers(){
	 cout << "now testing player implementations : \n";

	vector<Player*> players;
	players.push_back(new Player("idaten"));
	players.push_back(new Player("benten"));
	players.push_back(new Player("idaten"));
	players.push_back(new Player("natasha"));
	// players.push_back(new Player("vrash"));
	// players.push_back(new Player("izana"));
	
	// Player test = Player("benten");

	Continent* tempCont = new Continent("lol", 0);
	for(int i = 0; i<players.size();i++){
		players.at(i)->addTerritory(new Territory("TestTerritory of " + players.at(i)->getName(), tempCont));
		players.at(i)->addTerritory(new Territory("second teritorry of " + players.at(i)->getName(), tempCont));
	}

	for(int i = 0; i<players.size();i++){
		cout << "the territories of the player " << players.at(i)->getName() << "are : \n";
		Player* testPlayer = players.at(i);

		for(int i = 0; i < testPlayer->getTerritories().size() ;i++ ){
			
			cout << testPlayer->getName() << "'s territory #" << i+1 << "is named : " << testPlayer->getTerritories().at(i)->getName();

		}
	
	}
	
	cout << "now entering to defend methods.\n";
	
	for(int i = 0; i<players.size();i++){
		vector<Territory*> todefend = players.at(i)->toDefend();
	
		cout << "territories to defend : \n";
		for (int j = 0; j < todefend.size(); j++) {
			cout << "territory to defend number " << (j + 1) << " of player " << players.at(i)->getName() << " is named :" << todefend.at(j)->getName() << ". \n";
		}
	cout << "those were all the territories to defend. for player" << players.at(i)->getName() << "\n";
	
	}
	
	cout << "now exiting to defend methods.\n";
	
	cout << "-------------------------------------------------------------------------------------------------------------------------\n";
	
	cout << "now entering to attack method.\n";
	for(int i = 0; i<players.size();i++){
		vector<Territory*> toattack = players.at(i)->toAttack();
	
		cout << "territories to defend : \n";
		for (int j = 0; j < toattack.size(); j++) {
			cout << "territory to attack number " << (j + 1) << " of player " << players.at(i)->getName() << " is named :" << toattack.at(j)->getName() << ". \n";
		}
	cout << "those were all the territories to attack. for player" << players.at(i)->getName() << "\n";
	
	}
	cout << "now exiting to attack method.\n";

	for (int i = 0; i < players.size(); i++) {
		delete(players.at(i));
	}
	delete(tempCont);
	players.clear();
	
}