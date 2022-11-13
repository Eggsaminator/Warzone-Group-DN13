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
	ordersList = new OrderList(name);
}

void Player::addTerritory(Territory* newTerritory){
	territories.push_back(newTerritory);
}

//method for a player to issue an order, takes the order's name and related value (nb army troops)as parameter
void Player::issueOrder(Player* nameP, string name) {
	if (reinforcementPoolLeftToDeploy > 0 && name != "Deploy") {
		return;
	}

	if (name == "Deploy") {
		int numberArmyUnits = (rand() % reinforcementPoolLeftToDeploy) + 1;
		reinforcementPoolLeftToDeploy -= numberArmyUnits;

		int randomToDefendIndex = rand() % toDefend().size();
		Territory* destinationTerritory = toDefend().at(randomToDefendIndex);

		Orders* orderToAdd = new Deploy(nameP, numberArmyUnits, destinationTerritory);
		(*ordersList).addOrder(orderToAdd);
	}
	else if (name == "Advance") {
		Territory* destinationTerritory = nullptr;

		int randomSourceIndex = rand() % territories.size();
		Territory* sourceTerritory = territories.at(randomSourceIndex);

		string advanceTypes[] = { "Attack", "Defend" };
		string advanceType = advanceTypes[rand() % 2];

		if (advanceType == "Attack") {
			int randomToAttackIndex = rand() % toAttack().size();
			destinationTerritory = toAttack().at(randomToAttackIndex);
		}
		else
		{
			int randomToDefendIndex = rand() % toDefend().size();
			destinationTerritory = toDefend().at(randomToDefendIndex);
		}

		int numberArmyUnits = rand() % (sourceTerritory->getArmies() + 1);

		Orders* orderToAdd = new Advance(nameP, numberArmyUnits, sourceTerritory, destinationTerritory);
		(*ordersList).addOrder(orderToAdd);
	}
	else if (name == "Bomb") {
		int randomToAttackIndex = rand() % toAttack().size();
		Territory* destinationTerritory = toAttack().at(randomToAttackIndex);

		Orders* orderToAdd = new Bomb(nameP, destinationTerritory);
		(*ordersList).addOrder(orderToAdd);
	}
	else if (name == "Reinforcement") {
		//WHAT DO WE DO WITH REINFORCEMENT CARDS?
	}
	else if (name == "Airlift") {
		int randomSourceIndex = rand() % territories.size();
		Territory* sourceTerritory = territories.at(randomSourceIndex);

		int randomNbArmyUnits = rand() % (sourceTerritory->getArmies() + 1);

		int randomToDefendIndex = rand() % toDefend().size();
		Territory* destinationTerritory = toDefend().at(randomToDefendIndex);

		Orders* orderToAdd = new Airlift(nameP, randomNbArmyUnits, sourceTerritory, destinationTerritory);
		(*ordersList).addOrder(orderToAdd);
	}
	else if (name == "Negotiate") {
		//TODO: how am I supposed to access all the players??
		/*Orders* orderToAdd = new Negotiate(pick a randomPlayer);
		(*ordersList).addOrder(orderToAdd);*/
	}
	else if (name == "Blockade") {
		int randomTargetIndex = rand() % territories.size();
		Territory* targetTerritory = territories.at(randomTargetIndex);

		Orders* orderToAdd = new Blockade(nameP, targetTerritory);
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

int Player::getReinforcementPoolLeftToDeploy() {
	return reinforcementPoolLeftToDeploy;
}

void Player::setReinforcementPoolLeftToDeploy(int armyUnits) {
	reinforcementPoolLeftToDeploy = armyUnits;
}

void Player::setTruce(Player* tp) {
	nameT = tp->getName();
}

string Player::getTruce() {
	return nameT;
}

