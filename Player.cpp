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

//method for a player to issue an order, takes the order's name as parameter
Player::issueOrder(string name) {
	switch(name){
		case "deploy": 
			Order orderToAdd = new Deploy(5,territories[0]);
			*ordersList.orders.push_back(&orderToAdd);
		break;
		case "advance":
			Order orderToAdd = new Advande(5,territories[0],territories[1]);
			*ordersList.orders.push_back(&orderToAdd);
		break;
		case "bomb":
			Order orderToAdd = new Bome(territories[0]);
			*ordersList.orders.push_back(&orderToAdd);
		break;
		case "blockade": 
			Order orderToAdd = new Blockade(territories[0]);
			*ordersList.orders.push_back(&orderToAdd);
		break;
		case "airlift": 
			Order orderToAdd = new Airlift(5,territories[0],territories[1]);
			*ordersList.orders.push_back(&orderToAdd);
		break;
		case "negociate": 
			Order orderToAdd = new Negociate(territories[0]);
			*ordersList.orders.push_back(&orderToAdd);
		break;
	}
}

//method that prints out teritories to defend, would return them in future
Player::toDefend() {
	cout << "territories to defend : \n";
	for (int i = 0; i < territories.size; i++) {
		cout << "territory to defend number " << (i + 1) << " of player " << name << "\n";
	}
	cout << "those were all the territories to defend.\n";
}

//method that prints out teritories to attack, would return them in future
Player::toAttack() {
	vector<Territory> otherTerritories;
	for (int i = 0; i < 10; i++) {
		cout << "arbitraty territory to attack number " << (i + 1) << " of player " << Territory("Base #"  << i+1, NULL) << "\n";
	}
	cout << "those were all the territories to defend.\n";
}

Player::setHand(Hand* newHand){
	hand = newHand;
}
Player::getHand(){
	return hand;
}

Player::setName(string newName){
	name = newName;
}
Player::getName(){
	return name;
}

Player::setTerritories(vector<Territory*> newTerritories){
	territories = newTerritories;
}
Player::getTerritories(){
	return territories;
}

Player::setHand(OrderList* newOrdersList){
	ordersList = newOrdersList;
}
Player::getOrdersList(){
	return ordersList;
}