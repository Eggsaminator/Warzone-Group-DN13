#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include <vector>
using namespace std;

//dont know if we will need/keep this
Player::Player() {
name = "nameless player";
territories.push_back(new Territory("TestTerritory of " + name, NULL));
}

//player constructor
Player::Player(string username) {
	name = username;
	// vector<Territory*> firstTerritories;
	// firstTerritories.push_back(new Territory("TestTerritory of " + username, NULL));
	// territories = firstTerritories;
}

void Player::addTerritory(Territory* newTerritory){
	territories.push_back(newTerritory);
}
//method for a player to issue an order, takes the order's name as parameter
void Player::issueOrder(string name) {
	
	if(name == "deploy"){
		Orders* orderToAdd = new Deploy(5,territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}else if(name == "advance"){
		Orders* orderToAdd = new Advance(5,territories[0],territories[1]);
		(*ordersList).addOrder(orderToAdd);
	}else if(name == "bomb"){
		Orders* orderToAdd = new Bomb(territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}else if(name == "blockade"){
		Orders* orderToAdd = new Blockade(territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}else if(name == "airlift"){
		Orders* orderToAdd = new Blockade(territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}else if(name == "negociate"){
		Orders* orderToAdd = new Negotiate(territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}
}

//method that prints out teritories to defend, would return them in future
vector<Territory*> Player::toDefend() {
	cout << "territories to defend : \n";
	for (int i = 0; i < territories.size(); i++) {
		cout << "territory to defend number " << (i + 1) << " of player " << name << "\n";
	}
	cout << "those were all the territories to defend.\n";
	return territories;
}

//method that prints out teritories to attack, would return them in future
vector<Territory*> Player::toAttack() {
	vector<Territory*> otherTerritories;
	Territory* tempPointer;
	for (int i = 0; i < 10; i++) {
	tempPointer = new Territory("Base #" + to_string(i+1), nullptr);
	otherTerritories.push_back(tempPointer);
		cout << "arbitraty territory to attack number " << (i + 1) << " of player : Base #" << i+1 << "\n"; 
	}
	cout << "those were all the territories to defend.\n";
	return otherTerritories;
}

void Player::setHand(Hand* newHand){
	hand = newHand;
}
Hand* Player::getHand(){
	return hand;
}

void Player::setName(string newName){
	name = newName;
}
string Player::getName(){
	return name;
}

void Player::setTerritories(vector<Territory*> newTerritories){
	territories = newTerritories;
}
vector<Territory*> Player::getTerritories(){
	return territories;
}

void Player::setOrdersList(OrderList* newOrdersList){
	ordersList = newOrdersList;
}
OrderList* Player::getOrdersList(){
	return ordersList;
}