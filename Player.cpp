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
	vector<Territory*> firstTerritories;
	Continent* tempCont = new Continent("dummy", 0);
	firstTerritories.push_back(new Territory("TestTerritory of " + username, tempCont));
	territories = firstTerritories;
	ordersList = new OrderList(username);
}

void Player::addTerritory(Territory* newTerritory){
	territories.push_back(newTerritory);
}
//method for a player to issue an order, takes the order's name as parameter
void Player::issueOrder(string n) {
	
	if(n == "Deploy"){
		Orders* orderToAdd = new Deploy(name, 5,territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}else if(n == "Advance"){
		Orders* orderToAdd = new Advance(name, 5,territories[0],territories[1]);
		(*ordersList).addOrder(orderToAdd);
	}else if(n == "Bomb"){
		Orders* orderToAdd = new Bomb(name, territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}else if(n == "Blockade"){
		Orders* orderToAdd = new Blockade(name, territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}else if(n == "Airlift"){
		Orders* orderToAdd = new Blockade(name, territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}else if(n == "Negotiate"){
		Orders* orderToAdd = new Negotiate(name, territories[0]);
		(*ordersList).addOrder(orderToAdd);
	}
}

//method that prints out teritories to defend, would return them in future
vector<Territory*> Player::toDefend() {

	return territories;
}

//method that prints out teritories to attack, would return them in future
vector<Territory*> Player::toAttack() {
	vector<Territory*> otherTerritories;
	Continent* tempCont = new Continent("dummy", 0);
	for (int i = 0; i < 10; i++) {
		otherTerritories.push_back(new Territory("Base #" + to_string(i + 1), tempCont));
	}
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

