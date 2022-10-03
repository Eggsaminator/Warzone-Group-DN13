#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
using namespace std;

/*
class Player {
public:
	Player();
	Player(string username);
	toDefend();
	toAttack();
	void issueOrder();

private:
	string name;
	Hand* hand;
	vector<Territory*> territories;

};
*/
//dont know if we will need/keep this
Player::Player() {

}

//player constructor
Player::Player(string username) {
	name = username;
	territories.push_back(new Territory("TestTerritory of " + username, NULL));
}

Player::issueOrder() {

}

Player::toDefend() {
	for (int i = 0; i < territories.size; i++) {
		cout << "territory to defend number " << (i + 1) << " of player " << name << "\n";
	}
	cout << "those were all the territories to defend.\n"
}

Player::toAttack() {

}
Player::getNum() {

}

Player::setNum() {

}
