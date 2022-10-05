#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include <vector>
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
name = "nameless player";
territories.push_back(new Territory("TestTerritory of " + username, NULL));
}

//player constructor
Player::Player(string username) {
	name = username;
	territories.push_back(new Territory("TestTerritory of " + username, NULL));
}

Player::issueOrder(string name) {
Order orderToAdd = new Order(name);
*ordersList.orders.push_back(&orderToAdd);
}

Player::toDefend() {
	cout << "territories to defend : \n";
	for (int i = 0; i < territories.size; i++) {
		cout << "territory to defend number " << (i + 1) << " of player " << name << "\n";
	}
	cout << "those were all the territories to defend.\n";
}

Player::toAttack() {
	vector<Territory> otherTerritories;
	for (int i = 0; i < 10; i++) {
		cout << "arbitraty territory to attack number " << (i + 1) << " of player " << Territory("Base #"  << i+1, NULL) << "\n";
	}
	cout << "those were all the territories to defend.\n";
}
