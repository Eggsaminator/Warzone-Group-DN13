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
//method for a player to issue an order, takes the order's name and related value (nb army troops)as parameter
void Player::issueOrder(string name, int numberArmyUnits, int sourceTerritoryIndex, int targetTerritoryIndex, string advanceType) {
	if (name != "Deploy" && reinforcementPool > 0) {
		//INVALID BC STILL HAS ARMY UNITS TO DEPLOY
		return;
	}

	if(name == "Deploy"){
		if (numberArmyUnits <= reinforcementPool) {
			reinforcementPool -= numberArmyUnits;
			Orders* orderToAdd = new Deploy(numberArmyUnits, toDefend().at(0));
			territoriesToDefend.erase(territoriesToDefend.begin());
			(*ordersList).addOrder(orderToAdd);
		}
	}else if(name == "Advance"){
		Territory* destinationTerritory = nullptr;
		
		if (advanceType == "Attack") {
			destinationTerritory = toAttack().at(0);
			territoriesToAttack.erase(territoriesToAttack.begin());
		}
		else
		{
			destinationTerritory = toDefend().at(0);
			territoriesToDefend.erase(territoriesToDefend.begin());
		}

		Orders* orderToAdd = new Advance(numberArmyUnits,territories[sourceTerritoryIndex], destinationTerritory);
		(*ordersList).addOrder(orderToAdd);
	}
	else 
	{
		vector<Card*> cardsInHand = getHand()->hand_content;
		auto iterator = cardsInHand.begin();
		while (iterator != cardsInHand.end()) {

			Card* cardPtr = *iterator;
			if (name == cardPtr->card_type) {
				cardPtr->play(numberArmyUnits, sourceTerritoryIndex, targetTerritoryIndex);
			}
		}
	}
}

//method that prints out teritories to defend, would return them in future
vector<Territory*> Player::toDefend() {
	return territoriesToDefend;
}

//method that prints out teritories to attack, would return them in future
vector<Territory*> Player::toAttack() {
	return territoriesToAttack;
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

void Player::setTerritoriesToAttack(vector<Territory*> territoriesList) {
	territoriesToAttack = territoriesList;
}

void Player::setTerritoriesToDefend(vector<Territory*> territoriesList) {
	territoriesToDefend = territoriesList;
}

OrderList* Player::getOrdersList(){
	return ordersList;
}

int Player::getReinforcementPool() {
	return reinforcementPool;
}

void Player::setReinforcementPool(int armyUnits) {
	reinforcementPool = armyUnits;
}