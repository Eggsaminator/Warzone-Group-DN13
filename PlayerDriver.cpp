#include "Player.h"
#include <iostream>
using namespace std;


void testPlayers(){
//  cout << "now testing player implementations : \n";

// 	vector<Player> players;
// 	players.push_back(new Player("idaten"));
// 	players.push_back(new Player("benten"));
// 	players.push_back(new Player("idaten"));
// 	players.push_back(new Player("natasha"));
// 	players.push_back(new Player("vrash"));
// 	players.push_back(new Player("izana"));


// 	cout << "now entering to defend methods.\n";
// 	for(int i = 0; i<players.size;i++){
// 		players[i].toDefend();
// 	}
// 	cout << "now exiting to defend methods.\n";

// 	cout << "-------------------------------------------------------------------------------------------------------------------------\n";

// 	cout << "now entering to attack method.\n";
// 	for(int i = 0; i<players.size;i++){
// 		players[i].toAttack();
// 	}
// 	cout << "now exiting to attack method.\n";

}

int main() {
	 cout << "now testing player implementations : \n";

	// vector<Player> players;
	// players.push_back(Player("idaten"));
	// players.push_back(Player("benten"));
	// players.push_back(Player("idaten"));
	// players.push_back(Player("natasha"));
	// players.push_back(Player("vrash"));
	// players.push_back(Player("izana"));
	Player test = Player("benten");

	// test.addTerritory(new Territory("TestTerritory of " + test.getName(), NULL));
	cout << "now entering to defend methods.\n";

	// vector<Territory*> todefend = test.toDefend();
	// for(int i = 0; i<players.size();i++){
	// 	todefend = players.at(i).toDefend();
	// }
	cout << "now exiting to defend methods.\n";

	cout << "-------------------------------------------------------------------------------------------------------------------------\n";

	cout << "now entering to attack method.\n";
	// vector<Territory*> toattack = test.toAttack();

	// for(int i = 0; i<players.size();i++){
	// 	toattack = players.at(i).toAttack();
	// }
	cout << "now exiting to attack method.\n";

}

